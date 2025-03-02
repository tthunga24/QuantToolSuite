#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "test.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    test newtest;
    engine.rootContext() -> setContextProperty("testObj",&newtest);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("QuantToolSuite", "Main");

    return app.exec();
}
