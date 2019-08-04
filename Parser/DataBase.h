#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSqlQuery>
#include <QMap>

class DataBase
{
public:
    static DataBase& instance();
    void insert(const QMap<QString, QString>& data) const;
private:
    explicit DataBase();
    DataBase& operator=(const DataBase&);
    void createTables() const;
    QVariant::Type getFieldType(const QString field) const;
    QSqlDatabase db;
    static DataBase singleton;
};

#endif // DATABASE_H
