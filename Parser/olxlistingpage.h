#ifndef PARSEOLXPAGE_H
#define PARSEOLXPAGE_H

#include <QUrl>
#include <QByteArray>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>
#include <QMap>
#include <QMapIterator>
#include <QVariant>
#include "requesting.h"

class ParseOlxPage
{
public:
    ParseOlxPage(const QByteArray html, const QUrl address);
    QMap<int, QString> parseListingData() const;

private:
    const QByteArray arr;
    const QUrl url;
    QString Token() const;
    QString phoneId() const;
    QMap<int, QString> descriptionElements{{4, "Объявление от"}, {16, "Тип строения"}, {9, "Количество комнат"}, {12, "Общая площадь"}, {10, "Этаж"}, {11, "Этажность дома"}, {15, "Планировка"}, {17, "Ремонт"}};
};

#endif // PARSEOLXPAGE_H
