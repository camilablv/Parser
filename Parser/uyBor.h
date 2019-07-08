#ifndef UYBOR_H
#define UYBOR_H

#include "parser.h"
#include <write.h>
#include <requesting.h>
#include <jsonReader.h>
#include <QUrl>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>
#include <QRegExp>
#include "uyBorListing.h"
#include "uyBorHtmlParsing.h"

class UyBor : public Parser
{
public:
    explicit UyBor();
    ~UyBor();
    void parse();
    QList<Listing*> readListinsList(const QByteArray arr);
    QList<QMap<int, QString>> parseListings(QList<Listing*>);
    void write(QList<QMap<int, QString>> listData);

private:
    QList<QUrl> listinsList(const QByteArray arr);
    void ParseUyBor();
    QMap<int, QString> ParseUyBorPage(QByteArray arr, QStringList phone);

    Requesting *request;
    Write *writing;
    JsonReader *jsonReader;
};

#endif // UYBOR_H
