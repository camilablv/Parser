#include "zor.h"
#include <QList>

Zor::Zor(QObject *parent) : QObject(parent)
{
    request = new Requesting;
    write = new Write;
}
Zor::~Zor()
{
    delete request;
    delete write;
}

void Zor::Start()
{
    QUrl url("https://zor.uz/cat/kvartira/page/2");
    parseZor(request->pageText(url));
//    QMap<int, QString> data = parseZorPage(request->pageText(url));
//    write->writeToExcel(data, 1);
}

void Zor::parseZor(QByteArray arr)
{
    QGumboDocument doc = QGumboDocument::parse(arr);
    QGumboNode root = doc.rootNode();
    QGumboNodes divTags = root.getElementsByTagName(HtmlTag::DIV);
    for(uint i = 0; i < divTags.size(); i++)
    {
        QString attr = divTags.at(i).getAttribute("class");
        if(attr == "offerlist")
        {
            QGumboNode ad = divTags.at(i);
            QGumboNodes aTag = ad.getElementsByTagName(HtmlTag::A);
            if(aTag.size() == 0) continue;
            QGumboAttributes attrA = aTag.at(0).allAttributes();

        }
    }
}


QMap<int, QString> Zor::parseZorPage(QByteArray arr)
{
    QMap<int, QString> data;
    QRegExp tab("\\s+");
    QString description;
    QGumboDocument doc = QGumboDocument::parse(arr);
    QGumboNode root = doc.rootNode();
    QGumboNodes body = root.getElementsByTagName(HtmlTag::BODY);
    if(body.size() == 0) return data;
    QGumboNodes contentDiv = body.at(0).getElementsByTagName(HtmlTag::DIV);
    for(uint i = 0; i < contentDiv.size(); i++)
    {
        QString attr = contentDiv.at(i).getAttribute("class");
        if(attr == "offer_title")
        {
            QGumboNode title = contentDiv.at(i);
            QGumboNodes h1 = title.getElementsByTagName(HtmlTag::H1);
            data.insert(6, h1.at(0).innerText());
        }
        if(attr == "properties wpic")
        {
            QGumboNode properties = contentDiv.at(i);
            QGumboNodes trTag = properties.getElementsByTagName(HtmlTag::TR);
            for(uint j = 0; j < trTag.size(); j++)
            {
                QGumboNodes trChildren = trTag.at(j).children();
                QGumboNodes thTag;
                if(trChildren.size() > 0) thTag = trChildren.at(0).getElementsByTagName(HtmlTag::TH);
                if(thTag.at(0).innerText() == "Регион:")
                {
                    QGumboNodes bTag = trChildren.at(1).getElementsByTagName(HtmlTag::B);
                    if(bTag.size() == 0) continue;
                    if(bTag.at(0).innerText() != "Ташкент")
                    {
                        data.clear();
                        return data;
                    }
                }
                else if(thTag.at(0).innerText() == "Район:")
                {
                    data.insert(2, trChildren.at(1).innerText());
                }
                else if(thTag.at(0).innerText() == "Улица:")
                {
                    data.insert(8, trChildren.at(1).innerText());
                }
                else if(thTag.at(0).innerText() == "Количество комнат:")
                {
                    data.insert(9, trChildren.at(1).innerText());
                }
                else if(thTag.at(0).innerText() == "Этаж квартиры:")
                {
                    data.insert(10, trChildren.at(1).innerText());
                }
                else if(thTag.at(0).innerText() == "Этажность дома:")
                {
                    data.insert(11, trChildren.at(1).innerText());
                }
                else if(thTag.at(0).innerText() == "Общая площадь:")
                {
                    data.insert(12, trChildren.at(1).innerText());
                }
                else if(thTag.at(0).innerText() == "Материал стен:")
                {
                    data.insert(16, trChildren.at(1).innerText());
                }
                else if(thTag.at(0).innerText() == "Ремонт:")
                {
                    data.insert(17, trChildren.at(1).innerText());
                }
                else if(thTag.at(0).innerText() == "Дополнительно:")
                {
                    description.append(trChildren.at(1).innerText().replace(tab, " "));

                }
            }
        }
        if(attr == "theprice")
        {
            QGumboNodes bTag = contentDiv.at(i).getElementsByTagName(HtmlTag::B);
            if(bTag.size() == 0) continue;
            data.insert(33, bTag.at(0).innerText());
        }
        if(attr == "description")
        {
            QGumboNodes pTag = contentDiv.at(i).children();
            description.append("\n" + pTag.at(0).innerText());
            if(pTag.size() == 0) continue;
            data.insert(29, description);
        }
        if(attr == "offer_contacts")
        {
            QGumboNodes divTag = contentDiv.at(i).getElementsByTagName(HtmlTag::DIV);
            QGumboNodes trTags;
            if(divTag.size() > 0) trTags = divTag.at(0).getElementsByTagName(HtmlTag::TR);
            for(uint i = 0; i < trTags.size(); i++)
            {
                QGumboNodes trChildren = trTags.at(i).children();
                if(trChildren.size() == 0) continue;
                if(trChildren.at(0).innerText() == "Телефон:") //надо переделать с учетом того, что номеров может быть несколько
                {
                    QGumboNodes spanTag = trChildren.at(1).getElementsByTagName(HtmlTag::SPAN);
                    if(spanTag.size() == 0) continue;
                    data.insert(22, spanTag.at(0).innerText());
                }
                else if(trChildren.at(0).innerText() == "Автор:")
                {
                    QGumboNodes spanTag = trChildren.at(1).getElementsByTagName(HtmlTag::A);
                    if(spanTag.size() == 0) continue;
                    data.insert(25, spanTag.at(0).innerText());
                }
            }
        }
        if(attr == "offer_stats")
        {
            QGumboNodes iTag = contentDiv.at(i).getElementsByTagName(HtmlTag::I);
            if(iTag.size() == 0) continue;
            data.insert(45, iTag.at(2).innerText());
            data.insert(34, iTag.at(1).innerText());
        }
    }

    return data;
}
