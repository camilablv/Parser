#ifndef UYBOR_H
#define UYBOR_H

#include <QObject>
#include <write.h>
#include <requesting.h>
#include <jsonreader.h>
#include <QUrl>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>
#include <QRegExp>

class UyBor : public QObject
{
    Q_OBJECT
public:
    explicit UyBor(QObject *parent = nullptr);
    ~UyBor();
    void Start();

    //ПЕРЕМЕННЫЕ
    int row = 1;
    QRegExp spaces;

signals:

public slots:

private:
    void ParseUyBor();
    QMap<int, QString> ParseUyBorPage(QByteArray arr, QStringList phone);
    QString phoneId(QByteArray arr);
    QString phoneToken(QByteArray arr);
    QNetworkAccessManager *manager;
    Requesting *request;
    Write *write;
    JsonReader *jsonReader;
};

#endif // UYBOR_H
