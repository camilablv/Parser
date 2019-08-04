#ifndef UYBOR_H
#define UYBOR_H

#include "Site.h"
#include <Document.h>
#include <Requesting.h>
#include <JsonReader.h>
#include <QUrl>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>
#include <QRegExp>
#include "UyBorListing.h"
#include "UyBorQueryBuilder.h"

class UyBor : public Site
{
public:
    explicit UyBor(UyBorQueryBuilder QBuilder);
    ~UyBor();
    QList<std::shared_ptr<Listing> > readListingsList();

private:
    QList<QUrl> listingsList(const QByteArray arr);
    JsonReader *jsonReader;
    UyBorQueryBuilder queryBuilder;
    Requesting* request;
};

#endif // UYBOR_H
