// News.h
#pragma once
#include <vector>
#include <string>
#include <map>
#include <set>
#include "Company.h"

struct NewsEvent {
    std::string companyName;
    std::string hintText;
    std::string successText;
    std::string failureText;
    int successChance;
    double successRate; // 성공 시 주가 상승률 (예: 0.15 = 15%)
    double failureRate; // 실패 시 주가 하락률 (예: 0.10 = 10%)
    int createdRound;
    bool resolved;
};

class News {
private:
    std::vector<Company> companies;
    std::vector<NewsEvent> pendingResults;
    std::map<std::string, std::vector<std::tuple<std::string, std::string, std::string, int, double, double>>> newsHints;
    std::set<std::string> activeHintTexts;
    int round;

public:
    News();
    void nextRound();
    void generateNews();
    void applyNewsResults();
    void showCompanyStatus() const;
    std::vector<Company>& getCompanies();
    int getCurrentRound() const;
};
