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
    OlxListingsPage();
    QList<QUrl> olxListing(const QByteArray &html) const;



};

#endif // OLXLISTINGSPAGE_H
