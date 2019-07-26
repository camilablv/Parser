#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include "Olx.h"
#include <UyBor.h>
#include <Zor.h>
#include "OlxQueryBuilder.h"
#include "UyBorQueryBuilder.h"
#include "ZorQueryBuilder.h"
#include "Parser.h"
#include "Site.h"
#include "Document.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    Q_INVOKABLE void start();
signals:

public slots:

private:
    QQmlApplicationEngine engine;
    QObject *root;
    Document doc;
};

#endif // CONTROLLER_H
