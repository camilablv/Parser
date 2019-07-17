#ifndef UYBORLISTING_H
#define UYBORLISTING_H

#include "listing.h"
#include "requesting.h"
#include "jsonReader.h"
#include <QRegularExpression>

class uyBorListing: public Listing
{
public:
    uyBorListing(const QUrl address);
    QMap<int, QString> parsePage() const override;
    ~uyBorListing() override;
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
