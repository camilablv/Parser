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
            //if(listings.at(i).isUndefined()) continue;
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
//    QFile file("phones.txt");
//    if(file.open(QIODevice::WriteOnly))
//    {
//        file.write(arr);
//        file.close();
//    }
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

QMap<int, QString> JsonReader::listingData(const QString& data) const
{
    QMap<int, QString> listingData;
    QJsonDocument doc = QJsonDocument::fromJson(data.toLatin1());
    QJsonObject root = doc.object();

    listingData.insert(2, root.value("created_at").toString());
    QJsonValue owner = root.value("owner");
    listingData.insert(3, owner.toObject().value("role").toString());
    listingData.insert(4, root.value("fullAddress").toString());
    listingData.insert(5, QString::number(root.value("room").toInt()));
    listingData.insert(6, QString::number(root.value("floor").toInt()));
    listingData.insert(7, QString::number(root.value("floor_total").toInt()));
    listingData.insert(8, root.value("square").toString());
    listingData.insert(10, root.value("foundation").toString());
    listingData.insert(11, root.value("repair").toString());
    QJsonValue price = root.value("price");
    listingData.insert(12, price.toObject().value("actual_formatted").toString());
    listingData.insert(13, root.value("description").toString());
    //auto test = root.value("facilities");
    listingData.insert(14, getFacilities(root.value("facilities").toArray()));
    listingData.insert(15, owner.toObject().value("name").toString());
    listingData.insert(19, QString::number(root.value("id").toInt()));
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
    //auto test = QString::number(root.value("id").toInt());
    return QString::number(root.value("id").toInt());
}
