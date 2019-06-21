#include "write.h"

Write::Write(QObject *parent) : QObject(parent)
{

}

void Write::writeToExcel(QMap<int, QString> list)
{
    static int row = 1;
    QMapIterator<int, QString> iterator(list);
    while (iterator.hasNext()) {
        iterator.next();
        docXlsx.write(row, iterator.key(), iterator.value());
    }
    row++;
    docXlsx.saveAs("olx.xlsx");
}
