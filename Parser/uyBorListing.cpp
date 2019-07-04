#include "uyBorListing.h"

uyBorListing::uyBorListing(const QUrl address) : Listing(address)
{
    request = new Requesting;
    parsing = new UyBorHtmlParsing;
}

uyBorListing::~uyBorListing()
{
    delete request;
    delete parsing;
}

QMap<int, QString> uyBorListing::parsePage() const
{
    QMap<int, QString> data;
    QByteArray page = request->pageText(address);
    QString id = parsing->getId(page);
    QString token = parsing->getToken(page);
    data = parsing->listingData(page, parsing->phoneList(request->uyBorPhoneText(id, token, address)));
    return data;
}


