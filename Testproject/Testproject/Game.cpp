#include "Game.h"
#include <iostream>
#include <cstdlib>

#ifdef _WIN32
void clearScreen() {
    system("cls");
}
#else
void clearScreen() {
    system("clear");
}
#endif


Game::Game(int goalAssets) : player(5), news(), bank(), round(0), year(1), goalAssets(goalAssets) {}

void Game::start() {
    while (round < maxRound && !checkEndCondition()) {
        playRound();
    }

    clearScreen();

    std::cout << "게임 종료! 최종 자산: " << player.getFunds() << " 원\n";

    // 엔딩 메시지
    if (player.getFunds() >= goalAssets) {
        std::cout << "[엔딩] 목표 자산 달성! 성공적인 투자자입니다!\n";
    }
    else if (year > 10) {
        std::cout << "[엔딩] 10년이 지나 투자 기회가 사라졌습니다.\n";
        std::cout << "최종 자산으로 삶을 꾸려가야 합니다.\n";
    }
    else {
        std::cout << "[엔딩] 기타 종료 조건에 의해 게임이 끝났습니다.\n";
    }

    // 포트폴리오 및 상태 출력
    std::cout << "\n===== 최종 포트폴리오 상태 =====\n";
    player.showStatus(news.getCompanies(), bank);
}

void Game::playRound() {
    clearScreen();
    std::cout << "\nRound " << round + 1 << " 시작!\n";


    // 뉴스 힌트 출력
    news.nextRound();

    bool roundContinues = true;
    while (roundContinues) {
        std::cout << "\n--- 선택하세요 ---\n";
        std::cout << "1. 주식 매수\n";
        std::cout << "2. 주식 매도\n";
        std::cout << "3. 포트폴리오 확인\n";
        std::cout << "4. 대출 신청\n";
        std::cout << "5. 다음 라운드\n";
        std::cout << "선택 입력: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            const auto& companies = news.getCompanies();

            std::cout << "\n[주식 목록 및 현재 가격]\n";
            for (size_t i = 0; i < companies.size(); ++i) {
                std::cout << i + 1 << ". " << companies[i].getName() << " - 가격: " << companies[i].getPrice() << " 원\n";
            }

            std::cout << "보유 자금: " << player.getFunds() << " 원\n";

            int selection;
            std::cout << "매수할 회사 번호 입력: ";
            std::cin >> selection;

            if (selection < 1 || selection > companies.size()) {
                std::cout << "잘못된 번호입니다.\n";
                break;
            }

            int quantity;
            std::cout << "매수할 수량 입력: ";
            std::cin >> quantity;

            if (quantity <= 0) {
                std::cout << "잘못된 수량입니다.\n";
                break;
            }

            Company& selectedCompany = news.getCompanies()[selection - 1];
            double totalCost = selectedCompany.getPrice() * quantity;

            if (player.getFunds() < totalCost) {
                std::cout << "자금이 부족합니다.\n";
                break;
            }

            for (int i = 0; i < quantity; ++i) {
                player.buyStock(selectedCompany.getName(), news.getCompanies());
            }

            std::cout << selectedCompany.getName() << " 주식 " << quantity << "개를 매수했습니다.\n";
            break;
        }
        case 2: {
            std::cout << "\n[보유 주식 목록]\n";
            const auto& companies = news.getCompanies();
            bool hasHoldings = false;

            for (size_t i = 0; i < companies.size(); ++i) {
                const std::string& companyName = companies[i].getName();
                int quantity = player.getHoldingQuantity(companyName);
                if (quantity > 0) {
                    hasHoldings = true;
                    std::cout << i + 1 << ". " << companyName
                        << " - 보유 수량: " << quantity
                        << ", 현재가: " << companies[i].getPrice() << " 원\n";
                }
            }

            if (!hasHoldings) {
                std::cout << "보유한 주식이 없습니다.\n";
                break;
            }

            std::cout << "보유 자금: " << player.getFunds() << " 원\n";

            int selection;
            std::cout << "매도할 회사 번호 입력: ";
            std::cin >> selection;

            if (selection < 1 || selection > companies.size()) {
                std::cout << "잘못된 번호입니다.\n";
                break;
            }

            const std::string& sellCompany = companies[selection - 1].getName();
            int owned = player.getHoldingQuantity(sellCompany);

            if (owned <= 0) {
                std::cout << "해당 회사 주식을 보유하고 있지 않습니다.\n";
                break;
            }

            int quantity;
            std::cout << "매도할 수량 입력 (보유: " << owned << "): ";
            std::cin >> quantity;

            if (quantity <= 0 || quantity > owned) {
                std::cout << "잘못된 수량입니다.\n";
                break;
            }

            for (int i = 0; i < quantity; ++i) {
                player.sellStock(sellCompany, news.getCompanies());
            }

            std::cout << sellCompany << " 주식 " << quantity << "개를 매도했습니다.\n";
            break;
        }
        case 3: {
            std::cout << "\n[포트폴리오 상태]\n";
            player.showStatus(news.getCompanies(), bank);
            break;
        }
        case 4: {
            double amount;
            std::cout << "대출할 금액 입력: ";
            std::cin >> amount;
            bank.takeLoan(amount);
            break;
        }
        case 5: {
            roundContinues = false;

            // 라운드 증가
            round++;

            // 연도 증가
            if (round % 3 == 0) {
                year++;
            }

            break;
        }
        default:
            std::cout << "잘못된 입력입니다. 다시 선택하세요.\n";
        }
    }

    // 라운드 종료 후 뉴스 결과 반영 및 상태 출력
    news.showCompanyStatus();

    std::cout << "\n[플레이어 상태 요약]\n";
    player.showStatus(news.getCompanies(), bank);

    std::cout << "\n다음 라운드로 진행하려면 Enter 키를 누르세요...";
    std::cin.ignore();
    std::cin.get();

    // 3라운드마다 1년 경과 메시지 출력
    if (round > 0 && round % 3 == 0) {
        std::cout << "\n===== 1년이 지났습니다! 현재 연도: " << year << "년 =====\n";
    }
}

bool Game::checkEndCondition() const {
    return player.getFunds() >= goalAssets || year > 10;
}