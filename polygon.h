#ifndef POLYGON_H
#define POLYGON_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>

class Polygon : public QObject {
    Q_OBJECT

public:
    explicit Polygon(const QString& apiKey, QObject* parent = nullptr);

public slots:
    void fetchAggregatesData(const QString& symbol, const QString& fromDate, const QString& toDate,
                             const QString& timespan = "day", int multiplier = 1, bool adjusted = true, const QString& sort = "asc");

signals:
    void dataReceived(const QByteArray& data);
    void errorOccurred(const QString& error);

private slots:
    void onReplyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager networkManager;
    QString apiKey;
};

#endif // POLYGON_H
