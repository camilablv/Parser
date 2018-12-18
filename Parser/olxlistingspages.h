#ifndef OLXLISTINGSPAGES_H
#define OLXLISTINGSPAGES_H

#include <QUrl>
#include <QByteArray>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>

class OlxListingsPages
{
public:
    OlxListingsPages();
    QUrl nextListingPage(const QByteArray &html) const;
};

#endif // OLXLISTINGSPAGES_H
