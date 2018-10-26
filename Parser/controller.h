#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include "olx.h"

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
    Olx olx;
};

#endif // CONTROLLER_H
