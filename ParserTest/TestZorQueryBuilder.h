#ifndef TESTZORQUERYBUILDER_H
#define TESTZORQUERYBUILDER_H

#include <QObject>
#include <ZorQueryBuilder.h>
#include "AutoTest.h"

class TestZorQueryBuilder : public QObject
{
    Q_OBJECT
public:
    explicit TestZorQueryBuilder(QObject *parent = nullptr);

private slots:
    void toUrl();
};
DECLARE_TEST(TestZorQueryBuilder);
#endif // TESTZORQUERYBUILDER_H
