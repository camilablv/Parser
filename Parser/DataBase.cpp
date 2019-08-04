#include "DataBase.h"

DataBase::DataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("ad_storage.sqlite");
    if(!db.open())
        qDebug() << "Cannot open database:" << db.lastError();
}

void DataBase::createTables() const
{
    QSqlQuery query;
    if(query.exec("CREATE TABLE IF NOT EXISTS listings"
                  "id               NUMERIC NOT NULL PRIMARY KEY,"
                  "source           TEXT NOT NULL,"
                  "real_estate_type TEXT,"
                  "deal_type        TEXT,"
                  "title            TEXT,"
                  "date             NUMERIC NOT NULL,"
                  "from             VARCHAR NOT NULL,"
                  "address          TEXT,"
                  "rooms            INTEGER,"
                  "floor            INTEGER,"
                  "number_of_floors INTEGER,"
                  "square           INTEGER,"
                  "planning         TEXT,"
                  "wall_material    TEXT,"
                  "condition        TEXT,"
                  "price            TEXT,"
                  "description      TEXT,"
                  "additionally     TEXT,"
                  "name             TEXT,"
                  "phone1           TEXT,"
                  "phone2           TEXT,"
                  "phone3           TEXT)"))
    {
        qDebug() << "DataBase: error of create TABLE listings" ;
        qDebug() << query.lastError().text();
    }
}

DataBase& DataBase::instance()
{
    static DataBase singleton;
    return singleton;
}

void DataBase::insert(const QMap<QString, QString>& data) const
{
//    QSqlQuery query;
//    auto keys = QStringList(data.keys());
//    auto values = QStringList(data.values());
//    for(auto str : values)
//        ":" + str;
//    query.prepare("INSERT INTO listings (" + keys.join(", ") + ") VALUES (" + values.join(", ") +");");
    QSqlRecord record;
    QMapIterator<QString, QString> mapIterator(data);
    while(mapIterator.hasNext())
    {
        mapIterator.next();
        QSqlField field(mapIterator.key(), getFieldType(mapIterator.key()));
        field.setValue(mapIterator.value());
        record.append(field);
//        query.bindValue(":" + mapIterator.key(), mapIterator.value());
//        query.exec();
    }
    QSqlTableModel model;
    model.setTable("listings");
    model.insertRecord(-1, record);
}

QVariant::Type DataBase::getFieldType(const QString fieldName) const
{
    //http://qaru.site/questions/2065903/qtsql-get-column-type-and-name-from-table-without-record
    QSqlDriver* driver = db.driver();
    QSqlRecord record = driver->record("listings");
    auto field = record.field(fieldName);
    return field.type();
}


