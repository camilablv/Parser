#ifndef PARSER_H
#define PARSER_H

#include <QList>
#include <QMap>
#include <memory>
#include "listing.h"

class Parser
{
public:
    explicit Parser();
    virtual void parse() = 0;
    virtual QList<Listing*> readListinsList(const QByteArray arr) = 0;
    virtual QList<QMap<int, QString>> parseListings(QList<Listing*>) = 0;
    virtual void write(QList<QMap<int, QString>>) = 0;


    virtual ~Parser();
};

#endif // PARSER_H
