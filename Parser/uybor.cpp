#include "uybor.h"


UyBor::UyBor(QObject *parent) : QObject(parent)
{
    request = new Requesting;
    write = new Write;
    jsonReader = new JsonReader;
}

UyBor::~UyBor()
{
    delete request;
    delete write;
    delete jsonReader;
}

void UyBor::Start()
{
    ParseUyBor();
}


void UyBor::ParseUyBor()
{
    int row = 1;
    int pages = jsonReader->lastPage(request->uyBorAdList(1));
    for(int i = 1; i <= pages; i++)
    {
        QStringList list = jsonReader->adList(request->uyBorAdList(i));
        for(int j = 0; j < list.count(); j++)
        {
            if(list.at(j).isEmpty()) continue;
            QMap<int, QString> adList = ParseUyBorPage(request->pageText(list.at(j)));
            write->writeToExcel(adList, row);
            row++;
        }
    }

}


QMap<int, QString> UyBor::ParseUyBorPage(QByteArray arr)
{
    QRegExp spaces("\\s+");
    QMap<int, QString> data;
    QGumboNodes nodesDiv;
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode(); //передаем тег <html> в root
    QGumboNodes contentDiv = root.getElementById("content");
    if(0 < contentDiv.size()) nodesDiv = contentDiv.at(0).getElementsByTagName(HtmlTag::DIV);
    for(uint i = 0; i < nodesDiv.size(); i++)
    {
        QGumboAttributes attr = nodesDiv.at(i).allAttributes();
        for(uint j = 0; j < attr.size(); j++)
        {
            if(attr.at(j).value() == "listing__author-name") //ИМЯ
            {
                QGumboNodes tagA = nodesDiv.at(i).getElementsByTagName(HtmlTag::A);
                if(0 < tagA.size())
                {
                    data.insert(25, tagA.at(0).innerText().replace(spaces, " "));
                }
            } else if(attr.at(j).value() == "listing__author-occupation doPrint") //СТАТУС
            {
                data.insert(4, nodesDiv.at(i).innerText().replace(spaces, " "));
            }
            else if(attr.at(j).value() == "listing__price") //ЦЕНА
            {
                data.insert(33, nodesDiv.at(i).innerText().replace(spaces, " "));
            }
        }
    }
    QGumboNodes nodesSection;
    if(0 < contentDiv.size()) nodesSection = contentDiv.at(0).getElementsByTagName(HtmlTag::SECTION);
    for(uint i = 0; i < nodesSection.size(); i++)
    {
        QGumboAttributes attrSection = nodesSection.at(i).allAttributes();
        for(uint j = 0; j < attrSection.size(); j++)
        {
            if(attrSection.at(j).value() == "view-description") //ОПИСАНИЕ
            {
                data.insert(29, nodesSection.at(i).innerText().replace(spaces, " "));
            }
            else if(attrSection.at(j).value() == "view-map") //РАСПОЛОЖЕНИЕ
            {
                QGumboNodes divTags = nodesSection.at(i).children();
                for(uint k = 0; k < divTags.size(); k++)
                {
                    QGumboAttributes attr = divTags.at(k).allAttributes();
                    if(attr.at(0).value() == "row")
                    {
                        QGumboNode div = divTags.at(k);
                        QGumboNodes divChild = div.children();
                        for(uint l = 0; l < divChild.size(); l++)
                        {
                            QGumboAttributes attrCh = divChild.at(l).allAttributes();
                            if(attrCh.size() == 0) continue;
                            if(attrCh.at(0).value() == "col align-self-center")
                            {
                                data.insert(6, divChild.at(l).innerText().replace(spaces, " "));
                            }
                        }
                    }
                }
            }
            else if(attrSection.at(j).value() == "view-overview")
            {
                QGumboNode listingSection = nodesSection.at(i);
                QGumboNodes nodesTr = listingSection.getElementsByTagName(HtmlTag::TR);
                for(uint m = 0; m < nodesTr.size(); m++)
                {
                    QGumboNodes nodesTd = nodesTr.at(m).children();
                    if(nodesTd.size() == 0) continue;
                    if(nodesTd.at(0).innerText().replace(spaces, "") == "Комнат:")
                    {
                        data.insert(9, nodesTd.at(1).innerText());
                    }
                    if(nodesTd.at(0).innerText().replace(spaces, "") == "Этаж:")
                    {
                        data.insert(10, nodesTd.at(1).innerText());
                    }
                    if(nodesTd.at(0).innerText().replace(spaces, "") == "Этажность:")
                    {
                        data.insert(11, nodesTd.at(1).innerText());
                    }
                    if(nodesTd.at(0).innerText().replace(spaces, "") == "Площадь:")
                    {
                        data.insert(12, nodesTd.at(1).innerText());
                    }
                    if(nodesTd.at(0).innerText().replace(spaces, "") == "Состояние:")
                    {
                        data.insert(17, nodesTd.at(1).innerText());
                    }
                    if(nodesTd.at(0).innerText().replace(spaces, " ") == " Материал здания: ")
                    {
                        data.insert(16, nodesTd.at(1).innerText());
                    }
                }
            }
        }
        QGumboNodes dateAndIDNode = nodesSection.at(i).children();
        if(dateAndIDNode.size() == 0) continue;
        if(!dateAndIDNode.at(0).isElement()) continue;
        QGumboAttributes attr = dateAndIDNode.at(0).allAttributes();
        if(attr.size() == 0) continue;
        if(attr.at(0).value() == "listing__data")
        {
            QGumboNodes nodesTr = dateAndIDNode.at(0).getElementsByTagName(HtmlTag::TR);
            for(uint m = 0; m < nodesTr.size(); m++)
            {
                QGumboNodes nodesTd = nodesTr.at(m).children();
                if(nodesTd.at(0).innerText() == "Номер объявления (ID):")
                    data.insert(45, nodesTd.at(1).innerText());
                if(nodesTd.at(0).innerText() == "Обновлено:")
                    data.insert(34, nodesTd.at(1).innerText());
            }
        }

    }
    data.insert(38, "uyBor");
    return data;
}



