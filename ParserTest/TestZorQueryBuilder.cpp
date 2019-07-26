#include "TestZorQueryBuilder.h"

TestZorQueryBuilder::TestZorQueryBuilder(QObject *parent) : QObject(parent)
{

}

void TestZorQueryBuilder::toUrl()
{
    ZorQueryBuilder QBuilder("kvartira");
    QCOMPARE(QBuilder.toUrl(2), QUrl("https://zor.uz/cat/kvartira/page/2"));
}
