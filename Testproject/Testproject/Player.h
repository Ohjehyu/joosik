#pragma once
#include <vector>
#include <string>
#include "Company.h"
#include "Bank.h"

class Player {
private:
    double funds;
    std::vector<int> holdings;
    std::vector<double> averageBuyPrices;

public:
    Player(int companyCount);

    double getFunds() const;
    void buyStock(const std::string& companyName, std::vector<Company>& companies);
    void sellStock(const std::string& companyName, std::vector<Company>& companies);
    void showStatus(const std::vector<Company>& companies, const Bank& bank) const;
    int getHoldingQuantity(const std::string& companyName) const;
};
