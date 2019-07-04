#ifndef UYBORLISTING_H
#define UYBORLISTING_H

#include "listing.h"
#include "requesting.h"
#include "uyBorHtmlParsing.h"

class uyBorListing: public Listing
{
public:
    uyBorListing(const QUrl address);
    QMap<int, QString> parsePage() const override;
    ~uyBorListing() override;
private:
    QString phoneId(QByteArray arr) const;
    QString phoneToken(QByteArray arr) const;

    JsonReader *jsonReader;
    Requesting *request;
    UyBorHtmlParsing* parsing;
};

#endif // UYBORLISTING_H
