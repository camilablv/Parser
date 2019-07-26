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

QList<Listing *> UyBor::readListingsList()
{
    static int page = 1;
    QList<QUrl> addresses = listingsList(request->pageText(queryBuilder.toUrl(2/*++*/)));
    QList<Listing*> listings;
    for(auto x : addresses)
        listings.append(new UyBorListing(x));
    return listings;
}
