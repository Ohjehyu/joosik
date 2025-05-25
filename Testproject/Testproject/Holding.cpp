#include "Holding.h"

Holding::Holding() : quantity(0), averageBuyPrice(0.0) {}

void Holding::buy(int q, double price) {
    averageBuyPrice = ((averageBuyPrice * quantity) + (price * q)) / (quantity + q);
    quantity += q;
}

void Holding::sell(int q) {
    quantity -= q;
}