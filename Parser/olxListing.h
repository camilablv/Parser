#ifndef OLXLISTING_H
#define OLXLISTING_H

#include <QUrl>
#include <QByteArray>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>
#include <QMap>
#include <QMapIterator>
#include <QVariant>
#include "requesting.h"
#include "listing.h"

class OlxListing : public Listing
{
public:
    OlxListing(const QUrl address);
    QMap<int, QString> parsePage() const override;
    ~OlxListing() override;
private:
    const QUrl url;
    QString Token(QByteArray arr) const;
    QString phoneId(QByteArray arr) const;
    QMap<int, QString> descriptionElements{{4, "Объявление от"}, {16, "Тип строения"}, {9, "Количество комнат"}, {12, "Общая площадь"}, {10, "Этаж"}, {11, "Этажность дома"}, {15, "Планировка"}, {17, "Ремонт"}};
};

#endif // OLXLISTING_H
