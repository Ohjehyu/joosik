#include "Player.h"
#include <iostream>

Player::Player(int companyCount) : funds(100000) {
    holdings.resize(companyCount, 0);
    averageBuyPrices.resize(companyCount, 0.0);
}

double Player::getFunds() const {
    return funds;
}

void Player::buyStock(const std::string& companyName, std::vector<Company>& companies) {
    for (size_t i = 0; i < companies.size(); ++i) {
        if (companies[i].getName() == companyName) {
            double price = companies[i].getPrice();
            if (funds < price) {
                std::cout << "[매수 실패] 자금이 부족합니다.\n";
                return;
            }
            // 1주 매수
            funds -= price;
            // 평균 매입가 계산
            averageBuyPrices[i] = (averageBuyPrices[i] * holdings[i] + price) / (holdings[i] + 1);
            holdings[i] += 1;
     
            return;
        }
    }
    std::cout << "[매수 실패] 해당 이름의 주식을 찾을 수 없습니다.\n";
}

void Player::sellStock(const std::string& companyName, std::vector<Company>& companies) {
    for (size_t i = 0; i < companies.size(); ++i) {
        if (companies[i].getName() == companyName) {
            if (holdings[i] <= 0) {
                std::cout << "[매도 실패] 보유 중인 주식이 없습니다.\n";
                return;
            }
            funds += companies[i].getPrice();
            holdings[i] -= 1;
            std::cout << "[매도 성공] " << companyName << " 주식 1주 매도 완료\n";
            return;
        }
    }
    std::cout << "[매도 실패] 해당 이름의 주식을 찾을 수 없습니다.\n";
}

void Player::showStatus(const std::vector<Company>& companies, const Bank& bank) const {
    std::cout << "\n===== [포트폴리오 현황] =====\n";
    std::cout << "보유 자금: " << funds << " 원\n";

    std::cout << "\n[보유 주식 현황]\n";

    bool hasStock = false;
    for (size_t i = 0; i < holdings.size(); ++i) {
        if (holdings[i] > 0) {
            hasStock = true;
            const auto& company = companies[i];
            double buyPrice = averageBuyPrices[i];
            double currentPrice = company.getPrice();
            double profitPerShare = currentPrice - buyPrice;
            double totalProfit = profitPerShare * holdings[i];
            double profitRate = (profitPerShare / buyPrice) * 100.0;

            std::cout << "- " << company.getName()
                << ": " << holdings[i] << "주"
                << " | 평균 매입가: " << buyPrice << " 원"
                << " | 현재가: " << currentPrice << " 원"
                << " | 손익률: " << profitRate << " %"
                << " | 손익 금액: " << totalProfit << " 원\n";
        }
    }

    if (!hasStock) {
        std::cout << "보유 중인 주식이 없습니다.\n";
    }

    std::cout << "\n[대출 현황]\n";
    std::cout << "대출 금액: " << bank.getLoanAmount() << " 원\n";
    std::cout << "이자: " << bank.calculateInterest() << " 원\n";

    std::cout << "=============================\n";
}

int Player::getHoldingQuantity(const std::string& companyName) const {
    for (size_t i = 0; i < holdings.size(); ++i) {
        if (companyName == "CompanyA" && i == 0) return holdings[i];
        if (companyName == "CompanyB" && i == 1) return holdings[i];
        // 추가 회사가 있다면 여기에 확장
    }
    return 0;
}
