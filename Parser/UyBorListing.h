#ifndef UYBORLISTING_H
#define UYBORLISTING_H

#include "Listing.h"
#include "Requesting.h"
#include "JsonReader.h"
#include <QRegularExpression>

class UyBorListing: public Listing
{
public:
    UyBorListing(const QUrl address);
    QMap<int, QString> parsePage() const override;
    ~UyBorListing() override;
private:
    QMap<int, QString> listingData(const QByteArray& arr, const QStringList& phoneList) const;
    QString getToken(const QByteArray& arr) const;
    QString getId(const QByteArray& arr) const;
    QList<QString> phoneList(const QByteArray& arr) const;
    QString getScriptData(const QGumboNode& node) const;

    JsonReader *jsonReader;
    Requesting *request;
};

#endif // UYBORLISTING_H
