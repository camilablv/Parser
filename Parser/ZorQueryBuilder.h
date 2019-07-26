#ifndef ZORQUERYBUILDER_H
#define ZORQUERYBUILDER_H

#include <QString>
#include <QUrl>

class ZorQueryBuilder
{
public:
    ZorQueryBuilder(QString realEstateType);
    inline QUrl toUrl(int page = 1)
    {
        QStringList list = {BASE_URL, realEstate, PAGE, QString::number(page)};
        return QUrl(list.join("/")).toString();
    }
private:
    QString realEstate;
    QString deal;
    const QString BASE_URL = "https://zor.uz/cat";
    const QString PAGE = "page";
};

#endif // ZORQUERYBUILDER_H
