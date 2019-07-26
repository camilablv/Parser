#include "Controller.h"

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
//    OlxQueryBuilder builder("kvartiry", "prodazha");
//    Site* site = new Olx(builder);
    UyBorQueryBuilder builder("kvartiry-v-tashkente", "prodazha-kvartir");
    Site* site = new UyBor(builder);
    Parser parser(doc, site);
    parser.parse();
}
