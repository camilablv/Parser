#ifndef JSONREADER_H
#define JSONREADER_H

#include <QStringList>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QByteArray>

class JsonReader
{
public:
    JsonReader();
    QStringList adList(QByteArray arr);
    int lastPage(QByteArray arr);
};

#endif // JSONREADER_H
