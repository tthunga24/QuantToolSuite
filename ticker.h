#ifndef TICKER_H
#define TICKER_H
#include <QObject>

class Ticker
{
public:
    explicit Ticker(QString symbol);
    const std::vector<double>& GetPrices(int interval, int max_entries);
    void UpdatePrices();
    double GetCurrentPrice();

private:
    QString symbol;
    std::vector<double> price_history;
    std::map<int, std::vector<double>> captured_intervals;
    double current_price;
};

#endif // TICKER_H
