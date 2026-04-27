#pragma once

#include "Blackjack.h"
#include "CasinoData.h"
#include "CasinoRepository.h"
#include "Player.h"
#include "PseudoRoulette.h"

#include <string>
#include <vector>

class Casino
{
public:
    Casino(const CasinoData &data, CasinoRepository repository);
    ~Casino();

    double getBudget() const;
    double operator-(double amount);
    double operator+(double amount);

    void addGame(const std::string &gameName);
    void showGames() const;
    void run();

private:
    double budget_;
    Player player_;
    PseudoRoulette rouletteGame_;
    Blackjack blackjackGame_;
    CasinoRepository repository_;
    std::vector<std::string> games_;

    CasinoData toData() const;
    void saveData() const;
    void handleDeposit();
    void handleGameSelection();
    void runRouletteMenu();
    void runBlackjackMenu();
    void clearInput() const;
    void clearConsole() const;
};