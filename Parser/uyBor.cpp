#include "uyBor.h"


UyBor::UyBor()
{
    request = new Requesting;
    writing = new Write;
    parsing = new UyBorHtmlParsing;
}

UyBor::~UyBor()
{
    delete request;
    delete writing;
}

void UyBor::parse()
{
    auto listings = readListinsList(request->uyBorAdList(1));
    QList<QMap<int, QString>> listingsData = parseListings(listings);
    write(listingsData);
    qDeleteAll(listings);
}

QList<Listing *> UyBor::readListinsList(const QByteArray arr)
{
    QList<Listing *> listings;
    QList<QUrl> urls = parsing->listinsList(arr);
    for(auto x : urls)
        listings.append(new uyBorListing(x));
    return listings;
}

QList<QMap<int, QString>> UyBor::parseListings(QList<Listing*> listings)
{
    QList<QMap<int, QString>> listingsData;
    for(auto x : listings)
        listingsData.append(x->parsePage());
    return listingsData;
}

void UyBor::write(QList<QMap<int, QString>> listData)
{
    for(auto x: listData)
        writing->writeToExcel(x);
}



