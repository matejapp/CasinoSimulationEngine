#pragma once

#include "Player.h"
#include "Score.h"

#include <iosfwd>
#include <string>
#include <vector>

class Game
{
public:
    explicit Game(std::string name);
    virtual ~Game() = default;

    const std::string &getName() const;
    const std::vector<Score> &getScores() const;

    void addScore(const Score &score);
    Game &operator+=(const Score &score);
    const Score *operator-(double value) const;

    virtual void sortScoresAscending();
    virtual void sortScoresDescending();
    virtual void startGame(Player &player) = 0;

protected:
    void adjustPlayerBalance(Player &player, double amount) const;

private:
    std::string name_;
    std::vector<Score> scores_;
};

std::ostream &operator<<(std::ostream &out, const Game &game);