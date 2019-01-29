#ifndef OLX_H
#define OLX_H

#include <QObject>
#include <QUrl>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>
#include <QRegExp>
#include <QMap>
#include <requesting.h>
#include <write.h>
#include <QEventLoop>
#include <QTimer>
#include "olxListingsPage.h"
#include "olxListingPage.h"
#include <QList>
#include <QListIterator>
#include "iterable.h"
template class Iterable<QList<QUrl>>;
class Olx : public QObject
{
    Q_OBJECT
public:
    explicit Olx(QObject *parent = nullptr);
    ~Olx();
    void parseListing(QByteArray html);
    void Start();

    //ПЕРЕМЕННЫЕ
    int row = 1;

signals:

public slots:

private:
    void parsePage(const QUrl& url);
    //ПЕРЕМЕННЫЕ
    Requesting *request;
    Write *write;
};

#endif // OLX_H
