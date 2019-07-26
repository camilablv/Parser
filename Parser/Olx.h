#ifndef OLX_H
#define OLX_H

#include "Site.h"
#include <QUrl>
#include <QRegExp>
#include <QMap>
#include <Requesting.h>
#include <QTimer>
#include "OlxListing.h"
#include <QList>
#include <QListIterator>
#include "OlxListing.h"
#include"OlxQueryBuilder.h"



class Olx : public Site
{
public:
    explicit Olx(OlxQueryBuilder QBuilder);
    QList<Listing*> readListingsList();
    ~Olx();

private:
    QList<QUrl> listingsList(const QByteArray arr);
    OlxQueryBuilder queryBuilder;
    Requesting* request;

};

#endif // OLX_H
