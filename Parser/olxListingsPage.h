#ifndef OLXLISTINGSPAGE_H
#define OLXLISTINGSPAGE_H

#include <QList>
#include <QByteArray>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>

class OlxListingsPage
{
public:
    OlxListingsPage(const QByteArray &html);
    QList<QUrl> listingAddresses() const;
    QUrl nextListingPageUrl() const;
    QString Token() const;
    QString phoneId() const;

private:
    const QByteArray arr;
};

#endif // OLXLISTINGSPAGE_H
