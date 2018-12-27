#include "olxlistingpage.h"

OlxListingPage::OlxListingPage(const QByteArray html, const QUrl address) : arr(html), url(address){}

QMap<int, QString> OlxListingPage::parseListingData() const
{
    Requesting request;
    QVariant phone = request.olxPhoneText(url, phoneId(), Token());
    QMap<int, QString> data;
    data.insert(22, phone.toString());
    QRegExp spaces("\\s+");
    QGumboNode section;
    QGumboNodes contentDivChildren;
    QGumboNodes contactDivChildren;
    QGumboDocument document = QGumboDocument::parse(arr);
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
                        QGumboNodes nodesTr = tagTable.getElementsByTagName(HtmlTag::TR);
                        for(uint r = 0; r < nodesTr.size(); r++)
                        {
                            QGumboNodes trChildren = nodesTr.at(r).childNodes();
                            if(trChildren.size() == 0) continue;
                            QGumboNodes node = nodesTr.at(r).getElementsByTagName(HtmlTag::A);
                            if(node.size() == 0) node = nodesTr.at(r).getElementsByTagName(HtmlTag::STRONG);
                            if(node.size() == 0) continue;
                            QMapIterator<int, QString> descr(descriptionElements);
                            while(descr.hasNext())
                            {
                                descr.next();
                                if(trChildren.at(1).innerText() == descr.value())
                                    data.insert(descr.key(), node.at(0).innerText().replace(spaces, " "));
                            }
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

    return data;
}

QString OlxListingPage::Token() const //токен объявления
{
    QGumboNode section;
    QVariant phoneToken;
    QRegExp PhoneToken("(var phoneToken = )|(\')|(\\s+)|(\\;)");
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode(); //передаем тег <html> в root
    QGumboNodes body = root.getElementsByTagName(HtmlTag::SECTION);
    if(0 < body.size()) section =  body.at(0);
    else return "";
    QGumboNodes script;
    if(section.isElement()) script = section.getElementsByTagName(HtmlTag::SCRIPT);
    if(0 < script.size()) phoneToken = script.at(0).innerText();
    QString str = phoneToken.toString().replace(PhoneToken, "");
    return str;
}

QString OlxListingPage::phoneId() const //id объявления
{
    QGumboNode section;
    QGumboNodes tagLi;
    QRegExp idRegExp("( 'id':)|(\'+)");
    QGumboDocument document = QGumboDocument::parse(arr);
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
