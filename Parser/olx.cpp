#include "olx.h"

Olx::Olx(QObject *parent) : QObject(parent)
{
    request = new Requesting;
    write = new Write;
}

Olx::~Olx()
{
    delete request;
    delete write;
}

void Olx::Start()
{
    QUrl startPageAdsForSaleApartments("https://olx.uz/nedvizhimost/kvartiry/prodazha/");
    ParseOlx(request->pageText(startPageAdsForSaleApartments));
}

void Olx::ParseOlx(QByteArray html)
{
    QGumboNodes contentTable;
    QGumboNodes listH3;
    QGumboNodes nodesSpan;
    QGumboDocument document = QGumboDocument::parse(html);
    QGumboNode root = document.rootNode();
    QGumboNodes nodesSection = root.getElementsByTagName(HtmlTag::SECTION);
    if(0 < nodesSection.size()) contentTable = nodesSection.at(0).getElementById("offers_table");
    if(0 < contentTable.size()) listH3 = contentTable.at(0).getElementsByTagName(HtmlTag::H3);

    for(uint i = 0; i < listH3.size(); i++)
    {
        QGumboAttributes attr;
        QGumboNodes nodesA = listH3.at(i).getElementsByTagName(HtmlTag::A);

        if(0 < nodesA.size()) attr = nodesA.at(0).allAttributes();
        for(uint j = 0; j < attr.size(); j++)
        {
            if(attr.at(j).name() == "href")
            {
                QUrl pageAddress(attr.at(j).value());
                QByteArray page = request->pageText(pageAddress);
                if(page.isEmpty()) continue;
                QString id = phoneId(page);
                QString token = Token(page);
                QByteArray phone = request->phoneText(pageAddress, id, token);
                QList<QByteArray> data{page, phone};
                QMap<int, QString> listData = ParseOlxPage(data);
                write->writeToExcel(listData, row);
                row++;
            }
        }
    }

    if(0 < nodesSection.size()) nodesSpan = nodesSection.at(0).getElementsByTagName(HtmlTag::SPAN);
    for(uint i =0; i < nodesSpan.size(); i++)
    {
        QGumboAttributes attrSpan = nodesSpan.at(i).allAttributes();
        for(uint j = 0; j < attrSpan.size();j++)
        {
            if(attrSpan.at(j).value() != "fbold next abs large") continue;
            QGumboNode span = nodesSpan.at(i);
            QGumboNodes nodesA = span.getElementsByTagName(HtmlTag::A);
            if(0 < nodesA.size())
            {
                QGumboAttributes attrA;
                attrA = nodesA.at(0).allAttributes();
                for(uint k = 0; k < attrA.size(); k++)
                {
                    if(attrA.at(k).name() != "href") continue;
                    QUrl nextPageWithListUrl(attrA.at(k).value());
                    QByteArray nextPageWithList = request->pageText(nextPageWithListUrl);
                    ParseOlx(nextPageWithList);
                }
            }else break;
        }
    }
}

QMap<int, QString> Olx::ParseOlxPage(QList<QByteArray> list)
{
    QMap<int, QString> data;
    QRegExp spaces("\\s+");
    QGumboNode section;
    QGumboNodes contentDivChildren;
    QGumboNodes contactDivChildren;
    QGumboDocument document = QGumboDocument::parse(list.at(0));
    QGumboNode root = document.rootNode(); //передаем тег <html> в root
    QGumboNodes body = root.getElementsByTagName(HtmlTag::SECTION);
    if(0 < body.size()) section =  body.at(0);
    QGumboNodes contentDiv = section.getElementById("offerdescription");
    QGumboNodes ContactDiv = section.getElementById("offeractions");
    if(0 < contentDiv.size()) contentDivChildren = contentDiv.at(0).childNodes();
    for(uint i = 0; i < contentDivChildren.size(); i++)
    {
        QGumboNode node = contentDivChildren.at(i);
        if(!node.isElement()) continue;
        QGumboAttributes attr = node.allAttributes();
        for(uint j = 0; j < attr.size(); j++)
        {
            if(attr.at(j).value() == "offer-titlebox")
            {
                QGumboNodes nodesStrong = node.getElementsByTagName(HtmlTag::STRONG);
                QGumboNodes nodesEm = node.getElementsByTagName(HtmlTag::EM);
                QGumboNodes nodesSmall = node.getElementsByTagName(HtmlTag::SMALL);
                QGumboNodes nodesH1 = node.getElementsByTagName(HtmlTag::H1);
                if(0 < nodesStrong.size()) data.insert(2, nodesStrong.at(0).innerText().replace(spaces, " "));
                if(0 < nodesEm.size()) data.insert(1, nodesEm.at(0).innerText().replace(spaces, " "));
                if(0 < nodesSmall.size()) data.insert(45, nodesSmall.at(0).innerText().replace(spaces, " "));
                if(0 < nodesH1.size()) data.insert(6, nodesH1.at(0).innerText().replace(spaces, " "));
            }
            else if(attr.at(j).value() == "clr descriptioncontent marginbott20")
            {
                QGumboNodes text;
                QGumboNodes nodes = node.children();
                QGumboNodes nodesText = node.getElementById("textContent");
                if(0 < nodesText.size()) text = nodesText.at(0).getElementsByTagName(HtmlTag::P);
                if(0 < text.size()) data.insert(29, text.at(0).innerText().replace(spaces, " ")); //ОПИСАНИЕ

                for(uint k = 0; k < nodes.size(); k++)
                {
                    QGumboNode node = nodes.at(k);
                    if(node.tagName() != "table") continue;
                    QGumboNodes nodesTable = node.getElementsByClassName("item");
                    for(uint l = 0; l < nodesTable.size(); l++)
                    {
                        QGumboNode tagTable = nodesTable.at(l);
                        QGumboNodes nodesTh = tagTable.getElementsByTagName(HtmlTag::TH);
                        if(0 == nodesTh.size()) continue;
                        if(nodesTh.at(0).innerText() == "Объявление от")
                        {
                            QGumboNodes nodesA = tagTable.getElementsByTagName(HtmlTag::A);
                            if(0 == nodesA.size()) continue;
                            data.insert(4, nodesA.at(0).innerText().replace(spaces, " "));
                        }
                        else if(nodesTh.at(0).innerText() == "Тип строения")
                        {
                            QGumboNodes nodesA = tagTable.getElementsByTagName(HtmlTag::A);
                            if(0 == nodesA.size()) continue;
                            data.insert(16, nodesA.at(0).innerText().replace(spaces, " "));
                        }
                        else if(nodesTh.at(0).innerText() == "Количество комнат")
                        {
                            QGumboNodes nodesA = tagTable.getElementsByTagName(HtmlTag::STRONG);
                            if(0 == nodesA.size()) continue;
                            data.insert(9, nodesA.at(0).innerText().replace(spaces, " "));
                        }
                        else if(nodesTh.at(0).innerText() == "Общая площадь")
                        {
                            QGumboNodes nodesA = tagTable.getElementsByTagName(HtmlTag::STRONG);
                            if(0 == nodesA.size()) continue;
                            data.insert(12, nodesA.at(0).innerText().replace(spaces, " "));
                        }
                        else if(nodesTh.at(0).innerText() == "Этаж")
                        {
                            QGumboNodes nodesA = tagTable.getElementsByTagName(HtmlTag::STRONG);
                            if(0 == nodesA.size()) continue;
                            data.insert(10, nodesA.at(0).innerText().replace(spaces, " "));
                        }
                        else if(nodesTh.at(0).innerText() == "Этажность дома")
                        {
                            QGumboNodes nodesA = tagTable.getElementsByTagName(HtmlTag::STRONG);
                            if(0 == nodesA.size()) continue;
                            data.insert(11, nodesA.at(0).innerText().replace(spaces, " "));
                        }
                        else if(nodesTh.at(0).innerText() == "Планировка")
                        {
                            QGumboNodes nodesA = tagTable.getElementsByTagName(HtmlTag::A);
                            if(0 == nodesA.size()) continue;
                            data.insert(15, nodesA.at(0).innerText().replace(spaces, " "));
                        }
                        else if(nodesTh.at(0).innerText() == "Ремонт")
                        {
                            QGumboNodes nodesA = tagTable.getElementsByTagName(HtmlTag::A);
                            if(0 == nodesA.size()) continue;
                            data.insert(17, nodesA.at(0).innerText().replace(spaces, " "));
                        }
                    }
                }
            }
        }
    }

    if(0 < ContactDiv.size()) contactDivChildren = ContactDiv.at(0).children();
    for(uint i = 0; i < contactDivChildren .size(); i++)
    {
        QGumboNode node = contactDivChildren.at(i);
        if(!node.isElement()) continue;
        QGumboAttributes attr = node.allAttributes();
        for(uint j = 0; j < attr.size(); j ++)
        {
            if(attr.at(j).value() == "price-label") // записывает цену
            {
                QGumboNodes cost = node.getElementsByTagName(HtmlTag::STRONG);
                if(0 < cost.size()) data.insert(33, cost.at(0).innerText().replace(spaces, " "));
            }else if(attr.at(j).value() == "offer-sidebar__box ") //записывает имя частного лица
            {
                QGumboNodes name;
                QGumboNodes nodesH4 = node.getElementsByTagName(HtmlTag::H4);
                if(0 < nodesH4.size()) name = nodesH4.at(0).getElementsByTagName(HtmlTag::A);
                if(0 < name.size()) data.insert(25, name.at(0).innerText().replace(spaces, " "));
            }else if(attr.at(j).value() == "offer-sidebar__box offer-sidebar__box--business-info") //записывает имя агентства
            {
                QGumboNodes name;
                QGumboNodes nodesH4 = node.getElementsByTagName(HtmlTag::H4);
                if(0 < nodesH4.size()) name = nodesH4.at(0).getElementsByTagName(HtmlTag::A);
                if(0 < name.size()) data.insert(25, name.at(0).innerText().replace(spaces, " "));
            }
        }
    }
    data.insert(38, "olx");
    QVariant phone = list.at(1);
    data.insert(22, phone.toString());
    return data;
}

QString Olx::Token(QByteArray array) //токен объявления
{
    QGumboNode section;
    QVariant phoneToken;
    QRegExp PhoneToken("(var phoneToken = )|(\')|(\\s+)|(\\;)");
    QGumboDocument document = QGumboDocument::parse(array);
    QGumboNode root = document.rootNode(); //передаем тег <html> в root
    QGumboNodes body = root.getElementsByTagName(HtmlTag::SECTION);
    if(0 < body.size()) section =  body.at(0);
    QGumboNodes script;
    if(section.isElement()) script = section.getElementsByTagName(HtmlTag::SCRIPT);
    if(0 < script.size()) phoneToken = script.at(0).innerText();
    QString str = phoneToken.toString().replace(PhoneToken, "");
    return str;
}

QString Olx::phoneId(QByteArray array) //id объявления
{
    QGumboNode section;
    QGumboNodes tagLi;
    QRegExp idRegExp("( 'id':)|(\'+)");
    QGumboDocument document = QGumboDocument::parse(array);
    QGumboNode root = document.rootNode(); //передаем тег <html> в root
    QGumboNodes body = root.getElementsByTagName(HtmlTag::SECTION);
    if(0 < body.size()) section =  body.at(0);
    QGumboNodes tagUl;
    if(section.isElement()) tagUl = section.getElementById("contact_methods");
    if(0 < tagUl.size()) tagLi = tagUl.at(0).getElementsByTagName(HtmlTag::LI);
    for(uint i = 0; i < tagLi.size(); i++)
    {
        QGumboNodes nodeDiv = tagLi.at(i).getElementsByTagName(HtmlTag::DIV);
        for(uint j = 0; j < nodeDiv.size(); j++)
        {
            QGumboAttributes attr = nodeDiv.at(j).allAttributes();
            for(uint k = 0; k < attr.size(); k++)
            {
                if(attr.at(k).name() == "class")
                {
                    QString Id;
                    QString tmp = attr.at(k).value();
                    QStringList list = tmp.split(",");
                    if(0 < list.size()) Id = list.at(1);
                    return Id.replace(idRegExp, "");
                }
            }
        }
    }
    return "";
}
