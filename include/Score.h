#pragma once

#include "Player.h"

#include <string>

class Score
{
public:
    explicit Score(const Player &player, double score = 0.0);

    double getScore() const;
    void setScore(double score);
    int getPlayerId() const;
    const std::string &getPlayerName() const;

    void displayScore() const;

private:
    int playerId_;
    std::string playerName_;
    double score_;
};