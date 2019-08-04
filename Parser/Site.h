#ifndef SITE_H
#define SITE_H

#include <QString>
#include <QUrl>
#include "Listing.h"
#include <memory>

class Site
{
public:
    explicit Site();
    virtual ~Site();
    virtual QList<std::shared_ptr<Listing>> readListingsList() = 0;

private:
    virtual QList<QUrl> listingsList(const QByteArray arr) = 0;
};

#endif // SITE_H
