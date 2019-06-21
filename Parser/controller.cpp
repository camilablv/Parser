#include "controller.h"


Controller::Controller(QObject *parent) : QObject(parent)
{
    engine.rootContext()->setContextProperty("controller", this);
    QQmlComponent component(&engine, QUrl::fromLocalFile(":/main.qml"));
    root = component.create();
}

Controller::~Controller()
{
    delete root;
}

void Controller::start()
{
    olx.parse();
    //uyBor.Start();
    //zor.Start();
}
