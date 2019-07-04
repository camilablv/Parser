#include "olxListing.h"

OlxListing::OlxListing(const QUrl address) : Listing(address)
{
    parsing = new OlxHtmlParsing;
    request = new Requesting;
};

OlxListing::~OlxListing()
{
    delete parsing;
    delete request;
};

QMap<int, QString> OlxListing::parsePage() const
{
    QMap<int, QString> data;
    QByteArray page = request->pageText(address);
    QString id = parsing->getId(page);
    QString token = parsing->getToken(page);
    data = parsing->listingData(page, request->olxPhoneText(address, id, token));
    return data;
}


