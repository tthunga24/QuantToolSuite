#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCoreApplication>
#include "finnhub.h"
#include "yfinance.h"
#include "alphavantage.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Finnhub client;
    AlphaVantage clientapi("V0LIITCBJRMWNRO8");
    engine.rootContext() -> setContextProperty("finnhubClient", &client);
    engine.rootContext() -> setContextProperty("alphavantage", &clientapi);
    YFinance yfclient;
    engine.rootContext()->setContextProperty("yfinanceClient", &yfclient);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("QuantToolSuite", "Main");

    return app.exec();
}
