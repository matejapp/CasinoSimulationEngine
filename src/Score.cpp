#include "Score.h"

#include <iostream>

Score::Score(const Player &player, double score)
    : playerId_(player.getId()), playerName_(player.getName()), score_(score)
{
}

double Score::getScore() const
{
    return score_;
}

void Score::setScore(double score)
{
    score_ = score;
}

int Score::getPlayerId() const
{
    return playerId_;
}

const std::string &Score::getPlayerName() const
{
    return playerName_;
}

void Score::displayScore() const
{
    std::cout << "Player ID: " << playerId_
              << ", Name: " << playerName_
              << " Score: " << score_ << std::endl;
}