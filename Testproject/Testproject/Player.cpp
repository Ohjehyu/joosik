#include "Player.h"
#include <iostream>


Player::Player(int companyCount) : funds(1000000) {
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
                std::cout << "[�ż� ����] �ڱ��� �����մϴ�.\n";
                return;
            }
            // 1�� �ż�
            funds -= price;
            // ��� ���԰� ���
            averageBuyPrices[i] = (averageBuyPrices[i] * holdings[i] + price) / (holdings[i] + 1);
            holdings[i] += 1;

            return;
        }
    }
    std::cout << "[�ż� ����] �ش� �̸��� �ֽ��� ã�� �� �����ϴ�.\n";
}

void Player::sellStock(const std::string& companyName, std::vector<Company>& companies) {
    for (size_t i = 0; i < companies.size(); ++i) {
        if (companies[i].getName() == companyName) {
            if (holdings[i] <= 0) {
                std::cout << "[�ŵ� ����] ���� ���� �ֽ��� �����ϴ�.\n";
                return;
            }
            funds += companies[i].getPrice();
            holdings[i] -= 1;
            std::cout << "[�ŵ� ����] " << companyName << " �ֽ� 1�� �ŵ� �Ϸ�\n";
            return;
        }
    }
    std::cout << "[�ŵ� ����] �ش� �̸��� �ֽ��� ã�� �� �����ϴ�.\n";
}

void Player::showStatus(const std::vector<Company>& companies, const Bank& bank) const {
    std::cout << "\n===== [��Ʈ������ ��Ȳ] =====\n";
    std::cout << "���� �ڱ�: " << funds << " ��\n";

    std::cout << "\n[���� �ֽ� ��Ȳ]\n";

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
                << ": " << holdings[i] << "��"
                << " | ��� ���԰�: " << buyPrice << " ��"
                << " | ���簡: " << currentPrice << " ��"
                << " | ���ͷ�: " << profitRate << " %"
                << " | ���� �ݾ�: " << totalProfit << " ��\n";
        }
    }

    if (!hasStock) {
        std::cout << "���� ���� �ֽ��� �����ϴ�.\n";
    }

    std::cout << "\n[���� ��Ȳ]\n";
    std::cout << "���� �ݾ�: " << bank.getLoanAmount() << " ��\n";
    std::cout << "����: " << bank.calculateInterest() << " ��\n";

    std::cout << "=============================\n";
}

int Player::getHoldingQuantity(const std::string& companyName) const {
    for (size_t i = 0; i < holdings.size(); ++i) {
        if (companyName == "CompanyA" && i == 0) return holdings[i];
        if (companyName == "CompanyB" && i == 1) return holdings[i];
        // �߰� ȸ�簡 �ִٸ� ���⿡ Ȯ��
    }
    return 0;
}