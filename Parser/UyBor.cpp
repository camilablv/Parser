#include "UyBor.h"


UyBor::UyBor(UyBorQueryBuilder QBuilder) : queryBuilder(QBuilder)
{
    jsonReader = new JsonReader();
    request = new Requesting();
}

UyBor::~UyBor()
{
    delete request;
    delete jsonReader;
}


QList<QUrl> UyBor::listingsList(const QByteArray arr)
{
    return jsonReader->adList(arr);
}

QList<std::shared_ptr<Listing>> UyBor::readListingsList()
{
    static int page = 1;
    QList<QUrl> addresses = listingsList(request->pageText(queryBuilder.toUrl(2/*++*/)));
    QList<std::shared_ptr<Listing>> listings;
    for(auto x : addresses)
        listings.append(std::shared_ptr<UyBorListing>(new UyBorListing(x)));
    return listings;
}
