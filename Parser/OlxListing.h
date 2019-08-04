#ifndef OLXLISTING_H
#define OLXLISTING_H

#include <QUrl>
#include <QMap>
#include <QMapIterator>
#include <QVariant>
#include "Requesting.h"
#include "Listing.h"
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

class OlxListing : public Listing
{
public:
    OlxListing(const QUrl address);
    QMap<QString, QString> parsePage() const override;
    QMap<QString, QString> listingData(QByteArray arr, QByteArray phone) const;
    ~OlxListing() override;
private:
    QString innerText(const QGumboNode& node) const;
    void parseTable(QMap<QString, QString> &pairs, QGumboNode& node) const;
    QString getToken(const QByteArray& arr) const;
    QString getId(const QByteArray& arr) const;
    QList<QString> phoneList(const QByteArray& arr) const;
    //void addPhones(QMap<QString, QString>& pairs, const QStringList& phoneList) const;
    Requesting* request;
    QMap<QString, QString> descriptionElements{{"from", "Объявление от"}, {"real_estate_type", "Тип строения"},
                                           {"rooms", "Количество комнат"}, {"square", "Общая площадь"},
                                           {"floor", "Этаж"}, {"number_of_floors", "Этажность дома"},
                                           {"planning", "Планировка"}, {"condition", "Ремонт"}};
};

#endif // OLXLISTING_H
