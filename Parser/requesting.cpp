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

QByteArray Requesting::olxPhoneText(QUrl pageUrl, QString id, QString token)
{
    if(id == "" || token == "") return "";
    QUrl url("https://olx.uz/ajax/misc/contact/phone/"+id+"/?pt="+token);
    QNetworkRequest request(url);
    request.setRawHeader(QString("Referer").toUtf8(), pageUrl.toEncoded());
    QNetworkReply *reply = manager->get(request);
    connect(reply,SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    reply->deleteLater();
    return reply->readAll();
}

QByteArray Requesting::uyBorAdList(int page)
{
    QUrl post("https://uybor.uz/api/listing/search");
    QUrlQuery postData;
    postData.addQueryItem("page", QString(page));
    postData.addQueryItem("operation_type_code","sale");
    postData.addQueryItem("category_id", "23");
    postData.addQueryItem("region_id", "13");
    QNetworkRequest request(post);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QNetworkReply *reply = manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    reply->deleteLater();
    return reply->readAll();
}
