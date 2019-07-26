#ifndef TESTUYBORQUERYBUILDER_H
#define TESTUYBORQUERYBUILDER_H

#include <QObject>
#include <UyBorQueryBuilder.h>
#include <AutoTest.h>

class TestUyBorQueryBuilder : public QObject
{
    Q_OBJECT
public:
    explicit TestUyBorQueryBuilder(QObject *parent = nullptr);

private slots:
    void toUrl();
};
DECLARE_TEST(TestUyBorQueryBuilder);
#endif // TESTUYBORQUERYBUILDER_H
