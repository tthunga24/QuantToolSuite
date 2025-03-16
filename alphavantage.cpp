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

void AlphaVantage::ParseData(QJsonObject& data) {
    std::vector<std::pair<double, QString>> result;
    qDebug() << data;
    QJsonObject time_series = data["Time Series (60min)"].toObject();

    for (const QString& curr : time_series.keys()) {
        QJsonObject curr_obj = time_series[curr].toObject();
        //qDebug() << curr_obj["t"];
        result.push_back({curr_obj["4. close"].toDouble(), curr});
    }

    data_vector = result;
}

void AlphaVantage::onReplyFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply -> readAll();
        QJsonObject doc = QJsonDocument::fromJson(data).object();
        ParseData(doc);
        emit dataReceived(data_vector);

    } else {
        data_vector = std::vector<std::pair<double, QString>>();
        emit dataReceived(data_vector);

            qDebug() << "Error";
    }
    reply->deleteLater();
}
