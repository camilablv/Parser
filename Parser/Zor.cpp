#include "Zor.h"
#include <QList>

Zor::Zor(ZorQueryBuilder QBuilder) : queryBuilder(QBuilder)
{
    request = new Requesting();
}
Zor::~Zor()
{
    delete request;
}

QList<QUrl> Zor::listingsList(const QByteArray arr)
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

QList<std::shared_ptr<Listing>> Zor::readListingsList()
{
    static int page = 1;
    QList<QUrl> addresses = listingsList(request->pageText(queryBuilder.toUrl(page/*++*/)));
    QList<std::shared_ptr<Listing>> listings;
    for(auto x : addresses)
        listings.append(std::shared_ptr<ZorListing>(new ZorListing(x)));
    return listings;
}

