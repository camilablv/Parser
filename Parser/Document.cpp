#include "Document.h"

Document::Document(){}

void Document::writeToExcel(QMap<QString, QString> list)
{
    static int row = 1;
    QMapIterator<QString, QString> iterator(list);
    while (iterator.hasNext()) {
        iterator.next();
        //docXlsx.write(row, iterator.key(), iterator.value());
    }
    row++;
    docXlsx.saveAs("olx.xlsx");
}
