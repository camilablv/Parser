#include "uyBorListing.h"

uyBorListing::uyBorListing(const QUrl address) : Listing(address)
{
    request = new Requesting;
}

uyBorListing::~uyBorListing()
{
    delete request;
}

QMap<int, QString> uyBorListing::parsePage() const
{
    QMap<int, QString> data;
    QByteArray page = request->pageText(address);
    QString id = getId(page);
    QString token = getToken(page);
    data = listingData(page, phoneList(request->uyBorPhoneText(id, token, address)));
    return data;
}

QMap<int, QString> uyBorListing::listingData(const QByteArray& arr, const QStringList& phoneList) const
{
    QMap<int, QString> data;
    addPhones(data, phoneList);
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode();
    data.insert(6, innerText( getElementByTagName(root, HtmlTag::HEAD)));

    QGumboNode mainTag = getElementByClassName(root, "page__main");


//    QGumboNode description = getElementById(mainTag, "view-description");
//    data.insert(29, innerText(description));
//    QGumboNode city = getElementByClassName(mainTag, "align-self-center");
//    addPair(data, city, 2);


    return data;
}


QString uyBorListing::getToken(const QByteArray& arr) const
{
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode(); //передаем тег <html> в root
    QGumboNodes contentDiv = root.getElementById("content");
    if(contentDiv.size() == 0) return "";
    QGumboNodes test = contentDiv.at(0).childNodes();
    QGumboNodes nodesSection = contentDiv.at(0).getElementsByClassName("listing__section");
    for(uint i = 0; i < nodesSection.size(); i++)
    {
        QGumboAttributes attrSection = nodesSection.at(i).allAttributes();
        for(uint j = 0; j < attrSection.size(); j++)
        {
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
                    return nodesTd.at(1).innerText();
                }
            }
        }
    }
    return "";
}

QString uyBorListing::getId(const QByteArray& arr) const
{
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode();
    QGumboNodes head = root.getElementsByTagName(HtmlTag::HEAD);
    QGumboNodes metaTags;
    if(0 < head.size()) metaTags = head.at(0).getElementsByTagName(HtmlTag::META);
    for(uint i = 0; i < metaTags.size(); i++)
    {
        QGumboAttributes attr = metaTags.at(i).allAttributes();
        if(attr.at(0).value() == "csrf-token")
            return attr.at(1).value();
    }
    return "";
}

QList<QString> uyBorListing::phoneList(const QByteArray& arr) const
{
    return jsonReader->phoneList(arr);
}
