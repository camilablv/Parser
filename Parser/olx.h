#ifndef OLX_H
#define OLX_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>
#include <QRegExp>
#include <QMap>
#include <requesting.h>
#include <write.h>

class Olx : public QObject
{
    Q_OBJECT
public:
    explicit Olx(QObject *parent = nullptr);
    ~Olx();
    void ParseOlx(QByteArray html);
    void Start();
    QMap<int, QString> ParseOlxPage(QList<QByteArray> list);

    //ПЕРЕМЕННЫЕ
    int row = 1;

signals:

public slots:

private:
    QString phoneId(QByteArray array);
    QString Token(QByteArray array);

    //ПЕРЕМЕННЫЕ
    Requesting *request;
    Write *write;
    QList<QUrl> urls;
    bool end = false;
};

#endif // OLX_H
