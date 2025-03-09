#include "yfinance.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

YFinance::YFinance(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &YFinance::handleResponse);
}

void YFinance::fetchQuote(const QString &symbol) {
    qDebug() << "Fetching stock history for:" << symbol;

    // Correct Yahoo Finance URL for historical stock data
    QUrl url(QString("https://finance.yahoo.com/quote/%1/history/").arg(symbol));
    QNetworkRequest request(url);

    // Mimic `curl -s -H` to bypass bot protection
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64)");
    request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Language", "en-US,en;q=0.5");
    request.setRawHeader("Connection", "keep-alive");

    // Send the request
    manager->get(request);
}

void YFinance::handleResponse(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        QString errorMsg = "Error fetching data: " + reply->errorString();
        qDebug() << errorMsg;
        emit quoteReceived(errorMsg);  // Emit error message
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    QString responseString = QString::fromUtf8(data);  // Convert response to string

    // Log full response in console
    qDebug() << "Full Response:";
    qDebug().noquote() << responseString;

    // Extract only the first 100 characters
    QString shortResponse = responseString.left(100);

    // Emit the first 100 characters as a string to QML
    emit quoteReceived(shortResponse);

    reply->deleteLater();
}
