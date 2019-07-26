#include "TestUyBorQueryBuilder.h"

TestUyBorQueryBuilder::TestUyBorQueryBuilder(QObject *parent) : QObject(parent)
{

}

void TestUyBorQueryBuilder::toUrl()
{
    UyBorQueryBuilder QBuilder("kvartiry-v-tashkente", "prodazha-kvartir");
    QCOMPARE(QBuilder.toUrl(2), QUrl("https://uybor.uz/ru/prodazha-kvartir/kvartiry-v-tashkente?page=2"));
}
