#pragma once
#include <vector>
#include <string>
#include "Company.h"

struct NewsEvent {
    std::string hintNews;
    std::string positiveResult;
    std::string negativeResult;
    int successChance;
    bool isActive;
    std::string targetCompany;
};

class News {
private:
    std::vector<Company> companies;
    std::vector<NewsEvent> activeNews;

public:
    News();
    void initializeCompanies();
    void generateHintNews();
    void applyResultNews();
    void showCompanyStatus() const;
    std::vector<Company>& getCompanies();
};