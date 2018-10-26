#include "requesting.h"

Requesting::Requesting(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
}

Requesting::~Requesting()
{
    delete manager;
}

QByteArray Requesting::pageText(QUrl pageUrl)
{
    QNetworkRequest request(pageUrl);
    QNetworkReply *reply = manager->get(request);
    connect(reply,SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    reply->deleteLater();
    return reply->readAll();
}

QByteArray Requesting::phoneText(QUrl pageUrl, QString id, QString token)
{
    if(id == "" && token == "") return "";
    QUrl url("https://olx.uz/ajax/misc/contact/phone/"+id+"/?pt="+token);
    QNetworkRequest request(url);
    request.setRawHeader(QString("Referer").toUtf8(), pageUrl.toEncoded());
    QNetworkReply *reply = manager->get(request);
    connect(reply,SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    reply->deleteLater();
    return reply->readAll();
}
