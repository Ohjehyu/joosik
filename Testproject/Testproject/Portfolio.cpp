#include "Portfolio.h"
#include <iostream>

Portfolio::Portfolio(double initial_balance) : balance(initial_balance) {}

void Portfolio::buyStock(const Stock& stock, int quantity) {
    balance -= stock.price * quantity;
    holdings[stock.name].buy(quantity, stock.price);
}

void Portfolio::sellStock(const Stock& stock, int quantity) {
    balance += stock.price * quantity;
    holdings[stock.name].sell(quantity);
}

void Portfolio::printStatus(const std::unordered_map<std::string, Stock>& stockList) {
    std::cout << "Balance: " << balance << "\n";
    for (const auto& holding : holdings) {
        std::cout << holding.first << ": " << holding.second.quantity << " shares at "
            << holding.second.averageBuyPrice << " each\n";
    }
}

double Portfolio::getBalance() const {
    return balance;
}

void Portfolio::printHoldings() {
    for (const auto& holding : holdings) {
        std::cout << holding.first << ": " << holding.second.quantity << " shares\n";
    }
}