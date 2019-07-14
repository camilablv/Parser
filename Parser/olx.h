#ifndef OLX_H
#define OLX_H

#include "parser.h"
#include <QUrl>
#include <QRegExp>
#include <QMap>
#include <requesting.h>
#include <write.h>
#include <QTimer>
#include "olxListing.h"
#include <QList>
#include <QListIterator>
#include "iterable.h"
#include "olxListing.h"

template class Iterable<QList<Listing*>>;

class Olx : public Parser
{
public:
    explicit Olx();
    ~Olx();
    void parse();
    void parseListing(QByteArray html);
    QList<Listing*> readListinsList(const QByteArray arr);
    QList<QMap<int, QString>> parseListings(QList<Listing*> listings);
    void write(QList<QMap<int, QString>> listData);

private:
    QList<QUrl> listinsList(const QByteArray arr);
    void parsePage(const QUrl& url);
    Requesting *request;
    Write *writing;
};

#endif // OLX_H
