#pragma once

#include "Game.h"

#include <vector>

class Blackjack : public Game
{
public:
    Blackjack();

    void resetGame();
    void startGame(Player &player) override;
    int drawCard();
    int calculateScore() const;
    int getDealerHand();
    bool isBust() const;
    bool checkWinner();
    void printHand() const;

private:
    std::vector<int> deck_;
    std::vector<int> hand_;
    int dealerScore_;
    bool dealerScoreGenerated_;
    std::size_t nextCardIndex_;

    void buildDeck();
};