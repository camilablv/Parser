#include "controller.h"

#include <QDirIterator>

Controller::Controller(QObject *parent) : QObject(parent)
{
    engine.rootContext()->setContextProperty("controller", this);
    QQmlComponent component(&engine, QUrl("qrc:/qml/QML/main.qml"));
    QString test =  component.errorString();
    root = component.create();
}

Controller::~Controller()
{
    delete root;
}

void Controller::start()
{
    //olx.parse();
    uyBor.parse();
    //zor.parse();
}
