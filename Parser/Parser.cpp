#include "Parser.h"

Parser::Parser(DataBase &document, std::shared_ptr<Site> site)
{
    db = &document;
    webSite = site;
    request = new Requesting();
}
Parser::~Parser()
{
    delete request;
};

void Parser::parse()
{
    QList<QMap<QString, QString>> listingsData = parseListings(webSite->readListingsList());
    write(listingsData);
}


QList<QMap<QString, QString>> Parser::parseListings(const QList<std::shared_ptr<Listing>> listings)
{
   QList<QMap<QString, QString>> listingsData;
   auto lambda = [&](std::shared_ptr<Listing> listing)->void{
       listingsData.append(listing->parsePage());
   };
   Iterable<QList<std::shared_ptr<Listing>>> iterator(listings);
   iterator.forEach(lambda);
   return listingsData;
}

void Parser::write(QList<QMap<QString, QString>> listData)
{
    for(auto x: listData)
        db->insert(x);
}
