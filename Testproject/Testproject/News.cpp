// News.cpp
#include "News.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>

//카카오43000,삼성56000,애플27만,구글23만,테슬라49만,아마존28만,현대건설6만3천,SK하이닉스20만
News::News() : round(0) {
    companies.emplace_back("카카오", 43000.0);
    companies.emplace_back("삼성", 56000.0);
    companies.emplace_back("Apple", 270000.0);
    companies.emplace_back("Google", 230000.0);
    companies.emplace_back("테슬라", 490000.0);
    companies.emplace_back("Amazon", 280000.0);
    companies.emplace_back("현대건설", 63000.0);
    companies.emplace_back("SK하이닉스", 200000.0);
    

    newsHints["카카오"] = {
        {"카카오가 신기술을 개발 중입니다.", "카카오가 신기술 개발에 성공했습니다!", "카카오의 신기술 개발이 무산되었습니다.", 85, 0.15, 0.10},
        {"카카오가 대규모 투자를 유치했습니다.", "카카오가 투자 유치에 성공했습니다!", "카카오가 투자 유치에 실패했습니다.", 75, 0.10, 0.05},
        {"카카오가 해외 시장에 진출하고 있습니다.", "카카오가 해외 시장 진출에 성공했습니다!", "카카오의 해외 진출 전략이 실패했습니다.", 60, 0.20, 0.15}
    };
    newsHints["삼성"] = {
        {"삼성가 소송에 휘말렸습니다.", "삼성가 소송에서 승소했습니다!", "삼성가 소송에서 패소했습니다.", 40, 0.05, 0.20},
        {"삼성가 주요 인사를 교체했습니다.", "삼성의 새 인사가 회사를 안정시켰습니다!", "삼성의 리더십 변화가 혼란을 초래했습니다.", 55, 0.08, 0.12},
        {"삼성가 새로운 제품을 발표했습니다.", "삼성의 신제품이 시장에서 호평을 받았습니다!", "삼성의 신제품이 실패작으로 평가받았습니다.", 65, 0.12, 0.08}
    };
    newsHints["Apple"] = {
        {"Apple가 생산 공장을 증설하고 있습니다.", "Apple가 공장 증설에 성공했습니다!", "Apple의 공장 증설에 문제가 발생했습니다.", 70, 0.10, 0.05},
        {"Apple가 글로벌 기업과 협력 중입니다.", "Apple의 협력이 좋은 성과로 이어졌습니다!", "Apple의 협력이 무산되었습니다.", 60, 0.18, 0.12},
        {"Apple가 막대한 손실을 보고했습니다.", "Apple의 손실 회복 전략이 성공했습니다!", "Apple는 추가 손실이 발생했습니다.", 30, 0.08, 0.25}
    };
    newsHints["Google"] = {
       {"Google가 생산 공장을 증설하고 있습니다.", "Google가 공장 증설에 성공했습니다!", "Google의 공장 증설에 문제가 발생했습니다.", 70, 0.10, 0.05},
       {"Google가 글로벌 기업과 협력 중입니다.", "Google의 협력이 좋은 성과로 이어졌습니다!", "Google의 협력이 무산되었습니다.", 60, 0.18, 0.12},
       {"Google가 막대한 손실을 보고했습니다.", "Google의 손실 회복 전략이 성공했습니다!", "Google는 추가 손실이 발생했습니다.", 30, 0.08, 0.25}
    };

    newsHints["테슬라"] = {
       {"테슬라가 생산 공장을 증설하고 있습니다.", "테슬라가 공장 증설에 성공했습니다!", "테슬라의 공장 증설에 문제가 발생했습니다.", 70, 0.10, 0.05},
       {"테슬라가 글로벌 기업과 협력 중입니다.", "테슬라의 협력이 좋은 성과로 이어졌습니다!", "테슬라의 협력이 무산되었습니다.", 60, 0.18, 0.12},
       {"테슬라가 막대한 손실을 보고했습니다.", "테슬라의 손실 회복 전략이 성공했습니다!", "테슬라는 추가 손실이 발생했습니다.", 30, 0.08, 0.25}
    };

    newsHints["Amazon"] = {
       {"Amazon가 생산 공장을 증설하고 있습니다.", "Amazon가 공장 증설에 성공했습니다!", "Amazon의 공장 증설에 문제가 발생했습니다.", 70, 0.10, 0.05},
       {"Amazon가 글로벌 기업과 협력 중입니다.", "Amazon의 협력이 좋은 성과로 이어졌습니다!", "Amazon의 협력이 무산되었습니다.", 60, 0.18, 0.12},
       {"Amazon가 막대한 손실을 보고했습니다.", "Amazon의 손실 회복 전략이 성공했습니다!", "Amazon는 추가 손실이 발생했습니다.", 30, 0.08, 0.25}
    };

    newsHints["현대건설"] = {
       {"현대건설가 생산 공장을 증설하고 있습니다.", "현대건설가 공장 증설에 성공했습니다!", "현대건설의 공장 증설에 문제가 발생했습니다.", 70, 0.10, 0.05},
       {"현대건설가 글로벌 기업과 협력 중입니다.", "현대건설의 협력이 좋은 성과로 이어졌습니다!", "현대건설의 협력이 무산되었습니다.", 60, 0.18, 0.12},
       {"현대건설가 막대한 손실을 보고했습니다.", "현대건설의 손실 회복 전략이 성공했습니다!", "현대건설는 추가 손실이 발생했습니다.", 30, 0.08, 0.25}
    };
    newsHints["SK하이닉스"] = {
       {"SK하이닉스가 생산 공장을 증설하고 있습니다.", "SK하이닉스가 공장 증설에 성공했습니다!", "SK하이닉스의 공장 증설에 문제가 발생했습니다.", 70, 0.10, 0.05},
       {"SK하이닉스가 글로벌 기업과 협력 중입니다.", "SK하이닉스의 협력이 좋은 성과로 이어졌습니다!", "SK하이닉스의 협력이 무산되었습니다.", 60, 0.18, 0.12},
       {"SK하이닉스가 막대한 손실을 보고했습니다.", "SK하이닉스의 손실 회복 전략이 성공했습니다!", "SK하이닉스는 추가 손실이 발생했습니다.", 30, 0.08, 0.25}
    };



    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void News::nextRound() {
    round++;
    generateNews();
    applyNewsResults();
}

int News::getCurrentRound() const {
    return round;
}

void News::generateNews() {
    int numNews = 1 + rand() % 3;
    std::vector<int> indices(companies.size());
    for (int i = 0; i < companies.size(); ++i) {
        indices[i] = i;
    }
    std::random_shuffle(indices.begin(), indices.end());

    std::cout << "\n[라운드 " << round << " - 뉴스 발생]\n";

    for (int i = 0; i < numNews && i < indices.size(); ++i) {
        Company& company = companies[indices[i]];
        std::string cname = company.getName();
        auto& pool = newsHints[cname];

        std::vector<std::tuple<std::string, std::string, std::string, int, double, double>> availableHints;
        for (const auto& entry : pool) {
            if (activeHintTexts.find(std::get<0>(entry)) == activeHintTexts.end()) {
                availableHints.push_back(entry);
            }
        }

        if (availableHints.empty()) continue;

        auto& entry = availableHints[rand() % availableHints.size()];

        NewsEvent event{
            cname,
            std::get<0>(entry), std::get<1>(entry), std::get<2>(entry),
            std::get<3>(entry), std::get<4>(entry), std::get<5>(entry),
            round, false
        };
        pendingResults.push_back(event);
        activeHintTexts.insert(event.hintText);

        std::cout << " - " << event.hintText << "\n";
    }
}

void News::applyNewsResults() {
    std::cout << "\n[뉴스 결과 반영]\n";
    for (auto& event : pendingResults) {
        if (!event.resolved && round - event.createdRound >= 3) {
            int roll = rand() % 100;
            for (auto& company : companies) {
                if (company.getName() == event.companyName) {
                    double rate = 0.0;
                    if (roll < event.successChance) {
                        rate = event.successRate;
                        company.setPrice(company.getPrice() * (1.0 + rate));
                        std::cout << " - (" << event.companyName << ") " << event.successText
                            << " [주가 상승: " << std::fixed << std::setprecision(0) << rate * 100 << "%]\n";
                    }
                    else {
                        rate = event.failureRate;
                        company.setPrice(company.getPrice() * (1.0 - rate));
                        std::cout << " - (" << event.companyName << ") " << event.failureText
                            << " [주가 하락: " << std::fixed << std::setprecision(0) << rate * 100 << "%]\n";
                    }
                    break;
                }
            }
            event.resolved = true;
            activeHintTexts.erase(event.hintText);
        }
    }
}

void News::showCompanyStatus() const {
    std::cout << "\n[회사 주식 가격 현황]\n";
    for (const auto& company : companies) {
        std::cout << " - " << company.getName() << ": " << company.getPrice() << " 원\n";
    }
}

std::vector<Company>& News::getCompanies() {
    return companies;
}
