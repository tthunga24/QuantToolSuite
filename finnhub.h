#ifndef FINNHUBCLIENT_H
#define FINNHUBCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Finnhub : public QObject {
    Q_OBJECT
public:
    explicit Finnhub(QObject *parent = nullptr);
public slots:
    void fetchQuote(const QString &symbol);

private slots:
    void handleResponse(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QString apiKey;
signals:
    void quoteReceived(double price);
};
#endif // FINNHUBCLIENT_H
