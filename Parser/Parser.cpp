#include "Parser.h"

Parser::Parser(Document &document, Site* site)
{
    doc = &document;
    webSite = site;
    request = new Requesting();
}
Parser::~Parser()
{
    delete doc;
    delete webSite;
    delete request;
};

void Parser::parse()
{
    QList<QMap<int, QString>> listingsData = parseListings(webSite->readListingsList());
    write(listingsData);
}


QList<QMap<int, QString>> Parser::parseListings(const QList<Listing*> listings)
{
   QList<QMap<int, QString>> listingsData;
   auto lambda = [&](Listing* listing)->void{
       listingsData.append(listing->parsePage());
   };
   Iterable<QList<Listing*>> iterator(listings);
   iterator.forEach(lambda);
   for(auto x : listings) //временное решение для чистки памяти, потом воспользуюсь смарт поинтерами
       delete x;
   return listingsData;
}

void Parser::write(QList<QMap<int, QString>> listData)
{
    for(auto x: listData)
        doc->writeToExcel(x);
}
