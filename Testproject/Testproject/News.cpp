#include "News.h"
#include <cstdlib>
#include <iostream>

News::News() {
    initializeCompanies();
}

void News::initializeCompanies() {
    companies.push_back(Company("CompanyA", 100.0));
    companies.push_back(Company("CompanyB", 200.0));
}

void News::generateHintNews() {
    NewsEvent event;
    event.hintNews = "A new product launch is expected.";
    event.successChance = 70;
    event.targetCompany = "CompanyA";
    activeNews.push_back(event);
}

void News::applyResultNews() {
    for (auto& event : activeNews) {
        if (event.isActive) {
            int randChance = rand() % 100;
            if (randChance < event.successChance) {
                for (auto& company : companies) {
                    if (company.getName() == event.targetCompany) {
                        company.setPrice(company.getPrice() * 1.1);
                    }
                }
            }
            event.isActive = false;
        }
    }
}

void News::showCompanyStatus() const {
    for (const auto& company : companies) {
        std::cout << company.getName() << ": " << company.getPrice() << "\n";
    }
}

std::vector<Company>& News::getCompanies() {
    return companies;
}