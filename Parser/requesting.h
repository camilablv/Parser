#ifndef REQUESTING_H
#define REQUESTING_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>
#include <QEventLoop>
#include <QUrlQuery>

class Requesting : public QObject
{
    Q_OBJECT
public:
    explicit Requesting(QObject *parent = nullptr);
    ~Requesting();
    QByteArray pageText(QUrl pageUrl);
    QByteArray olxPhoneText(QUrl pageUrl, QString id, QString token);
    QByteArray uyBorAdList(int page);

signals:

public slots:

private:
    QNetworkAccessManager *manager;
    QEventLoop eventLoop;
};

#endif // REQUESTING_H
