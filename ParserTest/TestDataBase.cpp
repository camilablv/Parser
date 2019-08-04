#include "TestDataBase.h"

TestDataBase::TestDataBase(QObject *parent) : QObject(parent)
{

}

void TestDataBase::addRow(QMap<QString, QString> data)
{
    DataBase db = DataBase::instance();

    QMap<QString, QString> testData{{"date", "05.05.1994"}, {"from", "olx"}, {"address", "mirabad"}, {"rooms", "3"}, {"floor", "2"}, {"number_of_floors", "6"}};
    db.insert(testData);
}
