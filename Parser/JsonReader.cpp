#include "JsonReader.h"

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
            QJsonObject ad = listings.at(i).toObject();
            if(ad.value("url").isUndefined()) continue;
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

QStringList JsonReader::phoneList(QByteArray arr)
{
    QStringList list;
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

QMap<QString, QString> JsonReader::listingData(const QString& data) const
{
    QMap<QString, QString> listingData;
    QJsonDocument doc = QJsonDocument::fromJson(data.toLatin1());
    QJsonObject root = doc.object();

    listingData.insert("date", root.value("created_at").toString());
    QJsonValue owner = root.value("owner");
    listingData.insert("from", owner.toObject().value("role").toString());
    listingData.insert("address", root.value("fullAddress").toString());
    listingData.insert("rooms", QString::number(root.value("room").toInt()));
    listingData.insert("floor", QString::number(root.value("floor").toInt()));
    listingData.insert("number_of_floors", QString::number(root.value("floor_total").toInt()));
    listingData.insert("square", root.value("square").toString());
    listingData.insert("wall_material", root.value("foundation").toString());
    listingData.insert("condition", root.value("repair").toString());
    QJsonValue price = root.value("price");
    listingData.insert("price", price.toObject().value("actual_formatted").toString());
    listingData.insert("description", root.value("description").toString());
    listingData.insert("additionally", getFacilities(root.value("facilities").toArray()));
    listingData.insert("name", owner.toObject().value("name").toString());
    listingData.insert("id", QString::number(root.value("id").toInt()));
    return listingData;
}

QString JsonReader::getFacilities(QJsonArray arr) const
{
    QString facilities;
    for(int i = 0; i < arr.count(); i++)
    {
        auto obj = arr.at(i);
        facilities.append(obj.toObject().value("name").toString() + ", ");
    }

    return facilities;
}

QString JsonReader::getUyBorID(const QString& data) const
{
    QJsonDocument doc = QJsonDocument::fromJson(data.toLatin1());
    QJsonObject root = doc.object();
    return QString::number(root.value("id").toInt());
}
