#ifndef UYBORHTMLPARSING_H
#define UYBORHTMLPARSING_H

#include <QList>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>
#include "jsonReader.h"

class UyBorHtmlParsing
{
public:
    explicit UyBorHtmlParsing();
    ~UyBorHtmlParsing();
    QList<QUrl> listinsList(const QByteArray arr);
    QMap<int, QString> listingData(QByteArray arr, QList<QString> phone);
    QString getToken(QByteArray arr);
    QString getId(QByteArray arr);
    QList<QString> phoneList(QByteArray arr);
    
private:
    JsonReader* jsonReader;
};

#endif // UYBORHTMLPARSING_H
