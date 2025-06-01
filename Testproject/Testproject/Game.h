#pragma once
#include "Player.h"
#include "News.h"
#include "Bank.h"

class Game {
private:
    Player player;
    News news;
    Bank bank;
    int round;
    int year; 
    const int maxRound = 60;
    const int goalAssets;

public:
    Game(int goalAssets);

    void start();

private:
    void playRound();
    bool checkEndCondition() const;
};