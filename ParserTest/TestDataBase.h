#ifndef TESTDATABASE_H
#define TESTDATABASE_H

#include <QObject>
#include "AutoTest.h"
#include "DataBase.h"

class TestDataBase : public QObject
{
    Q_OBJECT
public:
    explicit TestDataBase(QObject *parent = nullptr);

private slots:
    void addRow(QMap<QString, QString> data);
};
DECLARE_TEST(TestDataBase);
#endif // TESTDATABASE_H
