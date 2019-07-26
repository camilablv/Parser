#ifndef OLXQUERYBUILDER_H
#define OLXQUERYBUILDER_H

#include <QString>
#include <QUrl>

class OlxQueryBuilder
{
public:
    explicit OlxQueryBuilder(QString realEstateType, QString dealType);
    inline QUrl toUrl(int page = 1)
    {
        QStringList list = {BASE_URL, realEstate, deal, CITY, PAGE + QString::number(page)};
        return QUrl(list.join("/")).toString();
    }
private:
    QString realEstate;
    QString deal;
    const QString BASE_URL = "https://olx.uz/nedvizhimost";
    const QString CITY = "tashkent";
    const QString PAGE = "?page=";
};

#endif // OLXQUERYBUILDER_H
