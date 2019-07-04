#include "jsonReader.h"

JsonReader::JsonReader()
{

}

QList<QUrl> JsonReader::adList(QByteArray arr)
{
    QList<QUrl> list;
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
            if(listings.at(i).isUndefined()) continue;
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

QList<QString> JsonReader::phoneList(QByteArray arr)
{
    QList<QString> list;
    QJsonDocument doc = QJsonDocument::fromJson(arr);
    QJsonObject root = doc.object();
    QJsonValue phones = root.value("phones");
    if(phones.isArray())
    {
        QJsonArray phoneArray = phones.toArray();
        for(int i = 0; i < phoneArray.count(); i++)
        {
            QJsonObject phone = phoneArray.at(i).toObject();
            list.append(phone.value("phone_original").toString());
        }
    }
    return list;
}
