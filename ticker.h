#ifndef TICKER_H
#define TICKER_H
#include <QObject>
#include "polygon.h"
#include "alphavantage.h"

class Ticker : public QObject
{
    Q_OBJECT
public:
    explicit Ticker(QString symbol);
    const std::vector<double>& GetPrices(int interval, int max_entries);
    void UpdatePrices();
    double GetCurrentPrice();

public slots:
    void fetchPrices();

private:
    QString symbol;
    std::vector<double> price_history;
    Polygon* polygon_client;
    AlphaVantage* alpha_client;
    std::vector<QString> date_history;
    std::map<int, std::vector<double>> captured_intervals;
    double current_price;
    void FallbackOnAlpha();
};

#endif // TICKER_H
