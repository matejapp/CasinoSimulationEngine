#include "Game.h"

#include "GameException.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>

Game::Game(std::string name)
    : name_(std::move(name))
{
    if (name_.length() > 30)
    {
        throw GameException("Name length exceeds 30 characters.");
    }
}

const std::string &Game::getName() const
{
    return name_;
}

const std::vector<Score> &Game::getScores() const
{
    return scores_;
}

void Game::addScore(const Score &score)
{
    scores_.push_back(score);
}

Game &Game::operator+=(const Score &score)
{
    addScore(score);
    return *this;
}

const Score *Game::operator-(double value) const
{
    for (const Score &score : scores_)
    {
        if (score.getScore() == value)
        {
            return &score;
        }
    }
    return nullptr;
}

void Game::sortScoresAscending()
{
    std::sort(scores_.begin(), scores_.end(), [](const Score &left, const Score &right) {
        return left.getScore() < right.getScore();
    });
}

void Game::sortScoresDescending()
{
    std::sort(scores_.begin(), scores_.end(), [](const Score &left, const Score &right) {
        return left.getScore() > right.getScore();
    });
}

void Game::adjustPlayerBalance(Player &player, double amount) const
{
    player.adjustBalance(amount);
    std::cout << "New balance for " << player.getName() << ": " << player.getBalance() << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Game &game)
{
    out << "Scores for game \"" << game.getName() << "\":" << std::endl;
    out << std::setw(15) << "Player" << std::setw(10) << "ID" << std::setw(10) << "Score" << std::endl;
    out << std::string(40, '-') << std::endl;

    for (const Score &score : game.getScores())
    {
        out << std::setw(15) << score.getPlayerName()
            << std::setw(10) << score.getPlayerId()
            << std::setw(10) << score.getScore() << std::endl;
    }

    return out;
}