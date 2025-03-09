#include "alphavantage.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

AlphaVantage::AlphaVantage(const QString& apiKey, QObject* parent)
    : QObject(parent), apiKey(apiKey) {}

void AlphaVantage::fetchTimeSeriesData(const QString& symbol, const QString& interval) {
    QUrl url("https://www.alphavantage.co/query");
    QUrlQuery query;
    query.addQueryItem("function", "TIME_SERIES_INTRADAY");
    query.addQueryItem("symbol", symbol);
    query.addQueryItem("interval", interval);
    query.addQueryItem("apikey", apiKey);
    query.addQueryItem("extended_hours", "false");
    url.setQuery(query);

    QNetworkRequest request(url);
    QNetworkReply* reply = networkManager.get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        this->onReplyFinished(reply);
    });
}

void AlphaVantage::onReplyFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        emit dataReceived(reply->readAll());
        qDebug() << "successful";
    } else {
        emit errorOccurred(reply->errorString());\
            qDebug() << "Error";
    }
    reply->deleteLater();
}
