#ifndef ZOR_H
#define ZOR_H

#include <QUrl>
#include <Document.h>
#include <Requesting.h>
#include <QRegExp>
#include "Site.h"
#include "ZorListing.h"
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>
#include "ZorQueryBuilder.h"

class Zor : public Site
{
public:
    explicit Zor(ZorQueryBuilder QBuilder);
    ~Zor();
    QList<std::shared_ptr<Listing>> readListingsList();

private:
    QList<QUrl> listingsList(const QByteArray arr);
    Requesting *request;
    ZorQueryBuilder queryBuilder;
};

#endif // ZOR_H
