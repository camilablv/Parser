#ifndef OLXHTMLPARSING_H
#define OLXHTMLPARSING_H

#include <QList>
#include <QUrl>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>

class OlxHtmlParsing
{
public:
    explicit OlxHtmlParsing();
    QList<QUrl> listinsList(const QByteArray arr);
    QMap<int, QString> listingData(QByteArray arr, QVariant phone);
    QString getToken(QByteArray arr);
    QString getId(QByteArray arr);
    
private:
    QMap<int, QString> descriptionElements{{4, "Объявление от"}, {16, "Тип строения"}, 
                                           {9, "Количество комнат"}, {12, "Общая площадь"}, 
                                           {10, "Этаж"}, {11, "Этажность дома"}, 
                                           {15, "Планировка"}, {17, "Ремонт"}};
};

#endif // OLXHTMLPARSING_H
