#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <xlsxdocument.h>
#include <xlsxcell.h>
#include <xlsxformat.h>

class Document
{
public:
    explicit Document();
    void writeToExcel(QMap<int, QString> list);

signals:

public slots:

private:
    QXlsx::Document docXlsx;
};

#endif // DOCUMENT_H
