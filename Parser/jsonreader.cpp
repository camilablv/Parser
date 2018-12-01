#include "jsonreader.h"

JsonReader::JsonReader()
{

}

QStringList JsonReader::adList(QByteArray arr)
{
    QStringList list;
    QJsonDocument doc = QJsonDocument::fromJson(arr);
    QJsonObject root = doc.object();
    QJsonValue valueData = root.value("data");
    QJsonObject data = valueData.toObject();
    QJsonValue valueListings = data.value("listings");
    if(valueListings.isArray())
    {
        QJsonArray listings = valueListings.toArray();
        for(int i = 0; i < listings.count(); i++)
        {
            if(listings.at(i).isUndefined()) break;
            QJsonObject ad = listings.at(i).toObject();

            list.append(ad.value("url").toString());
        }
    }
    return list;
}

int JsonReader::lastPage(QByteArray arr)
{
    QJsonDocument doc = QJsonDocument::fromJson(arr);
    QJsonObject root = doc.object();
    QJsonValue valueData = root.value("data");
    QJsonObject data = valueData.toObject();
    QJsonValue valuePagination = data.value("pagination");
    QJsonObject pagination = valuePagination.toObject();
    return pagination.value("lastPage").toInt();
}
