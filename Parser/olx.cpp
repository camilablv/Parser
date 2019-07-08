#include "olx.h"

Olx::Olx()
{
    request = new Requesting;
    writing = new Write;
}

Olx::~Olx()
{
    delete request;
    delete writing;
}

void Olx::parse()
{
    QUrl startPageAdsForSaleApartments("https://olx.uz/nedvizhimost/kvartiry/prodazha/tashkent/");
    QList<QMap<int, QString>> listingsData = parseListings(readListinsList(request->pageText(startPageAdsForSaleApartments)));
    write(listingsData);
}

QList<Listing*> Olx::readListinsList(const QByteArray arr)
{
    QList<QUrl> addresses = listinsList(arr);
    QList<Listing*> listings;
    for(auto x : addresses)
        listings.append(new OlxListing(x));
    return listings;
}

QList<QMap<int, QString>> Olx::parseListings(const QList<Listing*> listings)
{
   QList<QMap<int, QString>> listingsData;
   //listingsData.append(listings.at(0)->parsePage());
   auto lambda = [&](Listing* listing)->void{
       listingsData.append(listing->parsePage());
   };
   Iterable<QList<Listing*>> iterator(listings);
   iterator.forEach(lambda);
   return listingsData;
}

void Olx::write(QList<QMap<int, QString>> listData)
{
    for(auto x: listData)
        writing->writeToExcel(x);
}

QList<QUrl> Olx::listinsList(const QByteArray arr)
{
    QList<QUrl> listings;
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode();
    QGumboNodes aNodes = root.getElementsByClassName("detailsLink");
    for(auto a : aNodes)
        listings.append(a.getAttribute("href"));
    return listings;
}
