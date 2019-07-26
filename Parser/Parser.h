#ifndef PARSER_H
#define PARSER_H

#include <QList>
#include <QMap>
#include "Iterable.h"
#include "Listing.h"
#include <Document.h>
#include "Requesting.h"
#include "Site.h"

template class Iterable<QList<Listing*>>;

class Parser
{
public:
    explicit Parser(Document& document, Site* site);
    void parse();
    QList<Listing*> readListinsList(const QByteArray arr);
    QList<QMap<int, QString>> parseListings(QList<Listing*>);
    void write(QList<QMap<int, QString>>);
    ~Parser();
private:
    Document* doc;
    Site* webSite;
    Requesting *request;
};

#endif // PARSER_H
