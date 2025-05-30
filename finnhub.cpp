#include "finnhub.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

Finnhub::Finnhub(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
    apiKey = "cv1336pr01qhkk80eiugcv1336pr01qhkk80eiv0";
    connect(manager, &QNetworkAccessManager::finished, this, &Finnhub::handleResponse);
}

void Finnhub::fetchQuote(const QString &symbol) {
    QUrl url(QString("https://finnhub.io/api/v1/quote?symbol=%1&token=%2").arg(symbol, apiKey));
    QNetworkRequest request(url);
    manager->get(request);
}

void Finnhub::handleResponse(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    emit quoteReceived(jsonObj["c"].toDouble());

    reply->deleteLater();
}
