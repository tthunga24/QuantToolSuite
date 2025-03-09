#ifndef ALPHAVANTAGE_H
#define ALPHAVANTAGE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>

class AlphaVantage : public QObject {
    Q_OBJECT

public:
    explicit AlphaVantage(const QString& apiKey, QObject* parent = nullptr);
public slots:
    void fetchTimeSeriesData(const QString& symbol, const QString& interval = "60min");

signals:
    void dataReceived(const QByteArray& data);
    void errorOccurred(const QString& error);

private slots:
    void onReplyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager networkManager;
    QString apiKey;
};

#endif // ALPHAVANTAGE_H
