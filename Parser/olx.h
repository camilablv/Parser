#ifndef OLX_H
#define OLX_H

#include "parser.h"
#include <QUrl>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>
#include <QRegExp>
#include <QMap>
#include <requesting.h>
#include <write.h>
#include <QEventLoop>
#include <QTimer>
#include "olxListingsPage.h"
#include "olxListing.h"
#include <QList>
#include <QListIterator>
#include "iterable.h"
#include "olxListing.h"
#include <memory>

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
    void Start();

    //ПЕРЕМЕННЫЕ

signals:

public slots:

private:
    void parsePage(const QUrl& url);
    //ПЕРЕМЕННЫЕ
    Requesting *request;
    Write *writing;
};

#endif // OLX_H
