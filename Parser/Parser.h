#ifndef PARSER_H
#define PARSER_H

#include <QList>
#include <QMap>
#include "Iterable.h"
#include "Listing.h"
#include "DataBase.h"
#include "Requesting.h"
#include "Site.h"

template class Iterable<QList<Listing*>>;

class Parser
{
public:
    explicit Parser(DataBase& document, std::shared_ptr<Site> site);
    void parse();
    QList<Listing*> readListinsList(const QByteArray arr);
    QList<QMap<QString, QString>> parseListings(const QList<std::shared_ptr<Listing> >);
    void write(QList<QMap<QString, QString> >);
    ~Parser();
private:
    DataBase* db;
    std::shared_ptr<Site> webSite;
    Requesting *request;
};

#endif // PARSER_H
