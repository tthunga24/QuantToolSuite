#ifndef TICKER_H
#define TICKER_H
#include <QObject>

class Ticker
{
public:
   explicit Ticker(QString symbol);
    std::vector<double> GetPrices(int interval, int max_entries);
    void FetchPrices();

private:
    QString symbol;
    std::vector<double> price_history;
};

#endif // TICKER_H

