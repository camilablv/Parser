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
    QRegExp fragment("#(.*)");
    QList<Listing*> listings;
    QGumboNodes contentTable;
    QGumboNodes listH3;
    QGumboDocument document = QGumboDocument::parse(arr);
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
            if(attr.at(j).name() != "href") continue;
            QUrl pageAddress(attr.at(j).value());
            listings.append(new OlxListing(pageAddress.toString().replace(fragment, "")));
        }
    }
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
