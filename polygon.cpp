#include "polygon.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>
#include <utility>

Polygon::Polygon(const QString& apiKey, QObject* parent)
    : QObject(parent), apiKey(apiKey) {}

void Polygon::fetchAggregatesData(const QString& symbol,
                                     const QString& timespan, int multiplier, bool adjusted, const QString& sort) {

    //since polygon api requires date ranges, finding the last year date range
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    std::ostringstream oss;
    oss << (now -> tm_year + 1899) << "-" << std::setfill('0') << std::setw(2) << (now -> tm_mon + 1)
        << "-" << std::setw(2) << now -> tm_mday;
    QString fromDate = QString::fromStdString(oss.str());
    oss.str("");
    oss.clear();
    oss << (now -> tm_year + 1900) << "-" << std::setfill('0') << std::setw(2) << (now -> tm_mon + 1)
        << "-" << std::setw(2) << now -> tm_mday;
    QString toDate = QString::fromStdString(oss.str());

    QUrl url(QString("https://api.polygon.io/v2/aggs/ticker/%1/range/1/hour/%2/%3")
                 .arg(symbol, fromDate, toDate));

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

void Polygon::ParseData(QJsonObject& data) {
    std::vector<std::pair<double, QString>> result;
    int count = data["count"].toInt();
    result.reserve(count);
    //qDebug() << data;
    QJsonArray results = data["results"].toArray();

    for (const QJsonValue& curr : results) {
        QJsonObject curr_obj = curr.toObject();
        //qDebug() << curr_obj["t"];
        result.push_back({curr_obj["c"].toDouble(), QString::number(curr_obj["t"].toDouble())});
    }

    data_vector = result;
}

 void Polygon::onReplyFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply -> readAll();
        QJsonObject doc = QJsonDocument::fromJson(data).object();
        ParseData(doc);
        emit dataReceived(data_vector);
    } else {
        data_vector = std::vector<std::pair<double, QString>>();
        emit dataReceived(data_vector);
        qDebug() << "Polygon API Error: " << reply->errorString();

    }
    reply->deleteLater();
}
