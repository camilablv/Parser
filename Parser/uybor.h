#ifndef UYBOR_H
#define UYBOR_H

#include <QObject>
#include <write.h>
#include <requesting.h>
#include <QUrl>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>
#include <QRegExp>

class UyBor : public QObject
{
    Q_OBJECT
public:
    explicit UyBor(QObject *parent = nullptr);
    void Start();

    //ПЕРЕМЕННЫЕ
    int row = 1;
    QRegExp spaces;

signals:

public slots:

private:
    void ParseUyBor(QByteArray html);
    void ParseUyBorPage(QByteArray arr);
    QNetworkAccessManager *manager;
    Requesting *request;
    Write *write;
};

#endif // UYBOR_H
