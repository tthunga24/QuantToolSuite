#ifndef YFINANCE_H
#define YFINANCE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class YFinance : public QObject {
    Q_OBJECT
public:
    explicit YFinance(QObject *parent = nullptr);

public slots:
    void fetchQuote(const QString &symbol);  // Fetch stock history

signals:
    void quoteReceived(const QString &responseSnippet);  // Emit first 100 characters

private slots:
    void handleResponse(QNetworkReply *reply);  // Process response

private:
    QNetworkAccessManager *manager;
};

#endif // YFINANCE_H
