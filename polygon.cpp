#include "polygon.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

Polygon::Polygon(const QString& apiKey, QObject* parent)
    : QObject(parent), apiKey(apiKey) {}

void Polygon::fetchAggregatesData(const QString& symbol, const QString& fromDate, const QString& toDate,
                                     const QString& timespan, int multiplier, bool adjusted, const QString& sort) {
    QUrl url(QString("https://api.polygon.io/v2/aggs/ticker/%1/range/%2/%3/%4/%5")
                 .arg(symbol, QString::number(multiplier), timespan, fromDate, toDate));

    QUrlQuery query;
    query.addQueryItem("adjusted", adjusted ? "true" : "false");
    query.addQueryItem("sort", sort);
    query.addQueryItem("apiKey", apiKey);
    url.setQuery(query);

    QNetworkRequest request(url);
    QNetworkReply* reply = networkManager.get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        this->onReplyFinished(reply);
    });
}

void Polygon::onReplyFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        emit dataReceived(reply->readAll());
        qDebug() << "Polygon API request successful.";
    } else {
        emit errorOccurred(reply->errorString());
        qDebug() << "Polygon API Error: " << reply->errorString();
    }
    reply->deleteLater();
}
