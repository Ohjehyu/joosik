#include "Bank.h"

double Bank::getLoanAmount() const {
    return loan;
}

double Bank::calculateInterest() const {
    return loan * interestRate;
}

void Bank::takeLoan(double money) {
    if (money <= 0) {
        std::cout << "[대출 실패] 금액이 0원 이하입니다.\n";
        return;
    }
    if (loan + money > maxLoanLimit) {
        std::cout << "[대출 실패] 최대 대출 한도(" << maxLoanLimit
            << " 원)를 초과할 수 없습니다.\n";
        return;
    }
    loan += money;
    std::cout << "[대출 완료] 현재 대출금: " << loan << " 원\n";
}

void Bank::repayLoan(double money) {
    if (money <= 0) {
        std::cout << "[상환 실패] 금액이 0원 이하입니다.\n";
        return;
    }
    if (money > loan) money = loan;
    loan -= money;
    std::cout << "[상환 완료] 남은 대출금: " << loan << " 원\n";
}

void Bank::showStatus() const {
    std::cout << "대출금: " << loan << " 원\n";
    std::cout << "이자: " << calculateInterest() << " 원\n";
}