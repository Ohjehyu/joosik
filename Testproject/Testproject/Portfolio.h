#pragma once
#include <unordered_map>
#include "Stock.h"
#include "Holding.h"

class Portfolio {
private:
    double balance;
    std::unordered_map<std::string, Holding> holdings;

public:
    Portfolio(double initial_balance);

    void buyStock(const Stock& stock, int quantity);
    void sellStock(const Stock& stock, int quantity);
    void printStatus(const std::unordered_map<std::string, Stock>& stockList);
    double getBalance() const;
    void printHoldings();
};