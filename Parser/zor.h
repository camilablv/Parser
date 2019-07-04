#ifndef ZOR_H
#define ZOR_H

#include <QUrl>
#include <write.h>
#include <requesting.h>
#include <QRegExp>
#include "parser.h"
#include "zorListing.h"
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>

class Zor : public Parser
{
public:
    explicit Zor();
    ~Zor();
    void parse();
    QList<Listing*> readListinsList(const QByteArray arr);
    QList<QMap<int, QString>> parseListings(QList<Listing*> listings);
    void write(QList<QMap<int, QString>> listData);

private:
    QList<QUrl> listinsList(const QByteArray arr);
    Requesting *request;
    Write *writing;

};

#endif // ZOR_H
