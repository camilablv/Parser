#ifndef UYBORQUERYBUILDER_H
#define UYBORQUERYBUILDER_H

#include <QString>
#include <QUrl>

class UyBorQueryBuilder
{
public:
    UyBorQueryBuilder(QString realEstateType, QString dealType);
    inline QUrl toUrl(int page = 1)
    {
        QStringList list = {BASE_URL, deal, realEstate + PAGE + QString::number(page)};
        return QUrl(list.join("/")).toString();
    }
private:
    QString realEstate;
    QString deal;
    const QString BASE_URL = "https://uybor.uz/ru";
    const QString PAGE = "?page=";
};

#endif // UYBORQUERYBUILDER_H
