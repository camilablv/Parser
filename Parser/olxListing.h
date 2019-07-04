#ifndef OLXLISTING_H
#define OLXLISTING_H

#include <QUrl>
#include <QMap>
#include <QMapIterator>
#include <QVariant>
#include "requesting.h"
#include "listing.h"
#include "olxHtmlParsing.h"

class OlxListing : public Listing
{
public:
    OlxListing(const QUrl address);
    QMap<int, QString> parsePage() const override;
    ~OlxListing() override;
private:
    OlxHtmlParsing* parsing;
    Requesting* request;
};

#endif // OLXLISTING_H
