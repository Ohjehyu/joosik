#pragma once
#include <string>

class Stock {
public:
    std::string name;
    double price;

    Stock(std::string name = "", double price = 0.0);
};