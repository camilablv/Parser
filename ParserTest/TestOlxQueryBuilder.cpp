#include "TestOlxQueryBuilder.h"

TestOlxQueryBuilder::TestOlxQueryBuilder(QObject *parent) : QObject(parent){}

void TestOlxQueryBuilder::toUrl()
{
    OlxQueryBuilder QBuilder("kvartiry", "prodazha");
    QCOMPARE(QBuilder.toUrl(), QUrl("https://olx.uz/nedvizhimost/kvartiry/prodazha/tashkent/?page=1"));
}
