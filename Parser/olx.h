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
#include "olxlistingspage.h"
#include "olxlistingpage.h"
#include <QList>
#include <QListIterator>

class Olx : public QObject
{
    Q_OBJECT
public:
    explicit Olx(QObject *parent = nullptr);
    ~Olx();
    void ParseOlx(QByteArray html);
    void Start();

    //ПЕРЕМЕННЫЕ
    int row = 1;

signals:

public slots:

private:
    //ПЕРЕМЕННЫЕ
    Requesting *request;
    Write *write;
};

#endif // OLX_H
