#include "Olx.h"

Olx::Olx(OlxQueryBuilder QBuilder) : queryBuilder(QBuilder)
{
    request = new Requesting;
}

Olx::~Olx()
{
    delete request;
}



QList<QUrl> Olx::listingsList(const QByteArray arr)
{
    QList<QUrl> listings;
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode();
    QGumboNodes aNodes = root.getElementsByClassName("detailsLink");
    for(auto a : aNodes)
        listings.append(a.getAttribute("href"));
    return listings;
}

QList<std::shared_ptr<Listing>> Olx::readListingsList()
{
    static int page = 1;
    QList<QUrl> addresses = listingsList(request->pageText(queryBuilder.toUrl(page/*++*/)));
    QList<std::shared_ptr<Listing>> listings;
    for(auto x : addresses)
        listings.append(std::shared_ptr<OlxListing>(new OlxListing(x)));
    return listings;
}

