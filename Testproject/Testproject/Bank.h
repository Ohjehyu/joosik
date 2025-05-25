#pragma once
#include <iostream>

class Bank {
private:
    double loan;
    double interestRate;

public:
    Bank(double i = 0.05) : loan(0.0), interestRate(i) {}

    double getLoanAmount() const;
    double calculateInterest() const;
    void takeLoan(double money);
    void repayLoan(double money);
    void showStatus() const;
};