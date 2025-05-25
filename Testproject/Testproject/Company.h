#pragma once
#include <string>

class Company {
private:
    std::string name;
    double stockPrice;

public:
    Company(std::string name, double price);

    std::string getName() const;
    double getPrice() const;
    void setPrice(double newPrice);
};