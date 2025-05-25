#include "Company.h"

Company::Company(std::string name, double price) : name(name), stockPrice(price) {}

std::string Company::getName() const {
    return name;
}

double Company::getPrice() const {
    return stockPrice;
}

void Company::setPrice(double newPrice) {
    stockPrice = newPrice;
}