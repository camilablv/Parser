#ifndef ZOR_H
#define ZOR_H

#include <QObject>
#include <QUrl>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>
#include <write.h>
#include <requesting.h>
#include <QRegExp>

class Zor : public QObject
{
    Q_OBJECT
public:
    explicit Zor(QObject *parent = nullptr);
    ~Zor();
    void Start();

signals:

public slots:

private:
    void parseZor(QByteArray arr);
    QMap<int, QString> parseZorPage(QByteArray arr);
    Requesting *request;
    Write *write;
};

#endif // ZOR_H
