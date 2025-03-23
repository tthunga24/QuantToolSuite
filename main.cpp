#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCoreApplication>
#include "finnhub.h"
#include "yfinance.h"
#include "alphavantage.h"
#include "polygon.h"
#include "ticker.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Finnhub client;
    AlphaVantage clientapi("V0LIITCBJRMWNRO8");
    Ticker aapl("AAPL");
    engine.rootContext() -> setContextProperty("aapl", &aapl);
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

    // engine.loadFromModule("QuantToolSuite", "Main");
    engine.loadFromModule("QuantToolSuite", "App");
    // engine.load(QUrl(QStringLiteral("qrc:/testingui_2/TestingUI_2Content/App.qml")));


    return app.exec();
}
