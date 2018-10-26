#include "write.h"

Write::Write(QObject *parent) : QObject(parent)
{

}

void Write::writeToExcel(QMap<int, QString> list, int row)
{
    QMapIterator<int, QString> iterator(list);
    while (iterator.hasNext()) {
        iterator.next();
        docXlsx.write(row, iterator.key(), iterator.value());
    }
    docXlsx.saveAs("olx.xlsx");
}
