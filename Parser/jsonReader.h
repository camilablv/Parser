#ifndef JSONREADER_H
#define JSONREADER_H

#include <QStringList>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QByteArray>
#include <QList>

class JsonReader
{
public:
    JsonReader();
    QList<QUrl> adList(QByteArray arr);
    int lastPage(QByteArray arr);
    QStringList phoneList(QByteArray arr);
};

#endif // JSONREADER_H
