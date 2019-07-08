#ifndef OLXLISTING_H
#define OLXLISTING_H

#include <QUrl>
#include <QMap>
#include <QMapIterator>
#include <QVariant>
#include "requesting.h"
#include "listing.h"
#include "olxHtmlParsing.h"
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

class OlxListing : public Listing
{
public:
    OlxListing(const QUrl address);
    QMap<int, QString> parsePage() const override;
    QMap<int, QString> listingData(QByteArray arr, QByteArray phone) const;
    ~OlxListing() override;
private:
    QString innerText(const QGumboNode& node) const;
    void parseTable(QMap<int, QString>& pairs, QGumboNode& node) const;
    QString getToken(const QByteArray& arr) const;
    QString getId(const QByteArray& arr) const;
    QList<QString> phoneList(const QByteArray& arr) const;
    void addPhones(QMap<int, QString>& pairs, const QStringList& phoneList) const;
    OlxHtmlParsing* parsing;
    Requesting* request;
    QMap<int, QString> descriptionElements{{4, "Объявление от"}, {16, "Тип строения"},
                                           {9, "Количество комнат"}, {12, "Общая площадь"},
                                           {10, "Этаж"}, {11, "Этажность дома"},
                                           {15, "Планировка"}, {17, "Ремонт"}};
};

#endif // OLXLISTING_H
