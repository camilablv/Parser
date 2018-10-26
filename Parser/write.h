#ifndef WRITE_H
#define WRITE_H

#include <QObject>
#include <xlsxdocument.h>
#include <xlsxcell.h>
#include <xlsxformat.h>

class Write : public QObject
{
    Q_OBJECT
public:
    explicit Write(QObject *parent = nullptr);
    void writeToExcel(QMap<int, QString> list, int row);

signals:

public slots:

private:
    QXlsx::Document docXlsx;
};

#endif // WRITE_H
