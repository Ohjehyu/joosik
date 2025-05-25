#pragma once

class Holding {
public:
    int quantity;
    double averageBuyPrice;

    Holding();

    void buy(int q, double price);
    void sell(int q);
};