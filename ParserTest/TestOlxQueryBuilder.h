#ifndef OLXQUERYBUILDERTEST_H
#define OLXQUERYBUILDERTEST_H

#include <QObject>
#include "AutoTest.h"
#include <OlxQueryBuilder.h>

class TestOlxQueryBuilder : public QObject
{
    Q_OBJECT
public:
    explicit TestOlxQueryBuilder(QObject *parent = nullptr);

private slots:
    void toUrl();

};
DECLARE_TEST(TestOlxQueryBuilder);

#endif // OLXQUERYBUILDERTEST_H
