#include "zor.h"
#include <QList>

Zor::Zor()
{
    request = new Requesting;
    writing = new Write;
}
Zor::~Zor()
{
    delete request;
    delete writing;
}

void Zor::parse()
{
    QUrl url("https://zor.uz/cat/kvartira/page/2");
    QList<Listing *> listings = readListinsList(request->pageText(url));
    write(parseListings(listings));
    qDeleteAll(listings);
}

QList<Listing*> Zor::readListinsList(const QByteArray arr)
{
    QList<Listing *> listings;
    QList<QUrl> urls = listinsList(arr);
    for(auto x : urls)
        listings.append(new ZorListing(x));
    return listings;
}

QList<QMap<int, QString>> Zor::parseListings(QList<Listing*> listings)
{
    QList<QMap<int, QString>> listingsData;
    for(auto x : listings)
        listingsData.append(x->parsePage());
    return listingsData;
}

void Zor::write(QList<QMap<int, QString>> listData)
{
    for(auto x: listData)
        writing->writeToExcel(x);
}

QList<QUrl> Zor::listinsList(const QByteArray arr)
{
    QList<QUrl> listings;
    QGumboDocument doc = QGumboDocument::parse(arr);
    QGumboNode root = doc.rootNode();
    QGumboNodes ofr = root.getElementsByClassName("ofr");
    for(auto node : ofr)
    {
        QGumboNodes a = node.getElementsByTagName(HtmlTag::A);
        QString address = a.at(0).getAttribute("href").chopped(1); //chopped(1) удаляет слэш в конце
        listings.append(QUrl("https://zor.uz"+address));
    }
    return listings;
}


