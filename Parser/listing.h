#ifndef LISTING_H
#define LISTING_H

#include <QUrl>
#include <QMap>
#include <QString>

class Listing
{
public:
    explicit Listing(const QUrl url);
    virtual QMap<int, QString> parsePage() const = 0;
    virtual ~Listing();
protected:
    QUrl address;
};

#endif // LISTING_H
