#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <controller.h>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Controller c;

    return app.exec();
}
