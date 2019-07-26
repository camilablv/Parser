#ifndef SITE_H
#define SITE_H

#include <QString>
#include <QUrl>
#include "Listing.h"

class Site
{
public:
    explicit Site();
    virtual ~Site();
    virtual QList<Listing*> readListingsList() = 0;

private:
    virtual QList<QUrl> listingsList(const QByteArray arr) = 0;
};

#endif // SITE_H
