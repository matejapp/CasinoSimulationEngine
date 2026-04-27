#pragma once

#include "Game.h"

#include <array>
#include <string>

class PseudoRoulette : public Game
{
public:
    PseudoRoulette();

    void generateOutcome();
    int getFinalOutcome() const;
    char getColor() const;
    bool getParity() const;
    void displayOutcome() const;
    void displayHistory() const;
    bool checkBet(char betType, int betNumber = -1, bool betParity = true, char betColor = ' ') const;
    void startGame(Player &player) override;

    PseudoRoulette &operator+=(int number);
    PseudoRoulette &operator*=(char color);
    PseudoRoulette &operator/=(bool isEven);

private:
    int finalOutcome_;
    std::array<bool, 37> selectedNumbers_;
    char color_;
    bool evenNumber_;
    std::array<std::string, 10> history_;
    int historyIndex_;

    void clearSelectedNumbers();
    void generateColor();
    void updateParity();
    void playColorBet(Player &player, double betAmount);
    void playParityBet(Player &player, double betAmount);
    void playNumberBet(Player &player, double betAmount);
    void settleBet(Player &player, bool won, double payout, double loss);
};