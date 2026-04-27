#include "PseudoRoulette.h"

#include "PseudoRouletteException.h"
#include "RandomGenerator.h"
#include "Score.h"

#include <iostream>
#include <string>

PseudoRoulette::PseudoRoulette()
    : Game("Roulette"), finalOutcome_(0), color_('r'), evenNumber_(false), historyIndex_(0)
{
    selectedNumbers_.fill(false);
    history_.fill("");
}

void PseudoRoulette::generateOutcome()
{
    finalOutcome_ = RandomGenerator::instance().nextInt(0, 36);
    generateColor();
    updateParity();

    history_[historyIndex_] = "Outcome: " + std::to_string(finalOutcome_) + " (" + (evenNumber_ ? "Even" : "Odd") + ", Color: " + std::string(1, color_) + ")";
    historyIndex_ = (historyIndex_ + 1) % static_cast<int>(history_.size());
}

int PseudoRoulette::getFinalOutcome() const
{
    return finalOutcome_;
}

char PseudoRoulette::getColor() const
{
    return color_;
}

bool PseudoRoulette::getParity() const
{
    return evenNumber_;
}

void PseudoRoulette::displayOutcome() const
{
    std::cout << "Outcome: " << finalOutcome_ << " (" << (evenNumber_ ? "Even" : "Odd") << ", Color: " << color_ << ")" << std::endl;
}

void PseudoRoulette::displayHistory() const
{
    std::cout << "History of the last 10 outcomes:" << std::endl;
    for (const std::string &outcome : history_)
    {
        if (!outcome.empty())
        {
            std::cout << outcome << std::endl;
        }
    }
}

bool PseudoRoulette::checkBet(char betType, int betNumber, bool betParity, char betColor) const
{
    if (betType == 'c')
    {
        return betColor == color_;
    }

    if (betType == 'p')
    {
        return betParity == evenNumber_;
    }

    if (betType == 'n')
    {
        return betNumber >= 0 && betNumber < static_cast<int>(selectedNumbers_.size()) && selectedNumbers_[betNumber];
    }

    return false;
}

void PseudoRoulette::startGame(Player &player)
{
    if (player.getBalance() < 10)
    {
        throw PseudoRouletteException("You don't have enough balance to play games (balance < 10).");
    }

    std::cout << "Starting the roulette game..." << std::endl;
    std::cout << "Enter the amount you want to bet: ";

    double betAmount = 0.0;
    std::cin >> betAmount;

    if (!std::cin || betAmount <= 0)
    {
        throw PseudoRouletteException("Invalid bet amount. Please enter a positive value.");
    }

    if (betAmount > player.getBalance())
    {
        throw PseudoRouletteException("You don't have enough balance to place this bet.");
    }

    std::cout << "Choose your bet type (c for color, p for parity, n for number): ";
    char betType = ' ';
    std::cin >> betType;

    if (betType == 'c')
    {
        playColorBet(player, betAmount);
    }
    else if (betType == 'p')
    {
        playParityBet(player, betAmount);
    }
    else if (betType == 'n')
    {
        playNumberBet(player, betAmount);
    }
    else
    {
        throw PseudoRouletteException("Invalid bet type. Please enter 'c', 'p' or 'n'.");
    }
}

PseudoRoulette &PseudoRoulette::operator+=(int number)
{
    if (number >= 0 && number < static_cast<int>(selectedNumbers_.size()))
    {
        selectedNumbers_[number] = true;
    }
    return *this;
}

PseudoRoulette &PseudoRoulette::operator*=(char color)
{
    if (color == 'r' || color == 'b' || color == 'g')
    {
        color_ = color;
    }
    return *this;
}

PseudoRoulette &PseudoRoulette::operator/=(bool isEven)
{
    evenNumber_ = isEven;
    return *this;
}

void PseudoRoulette::clearSelectedNumbers()
{
    selectedNumbers_.fill(false);
}

void PseudoRoulette::generateColor()
{
    if (finalOutcome_ == 0)
    {
        color_ = 'g';
    }
    else if ((finalOutcome_ >= 1 && finalOutcome_ <= 10) || (finalOutcome_ >= 19 && finalOutcome_ <= 28))
    {
        color_ = finalOutcome_ % 2 == 0 ? 'b' : 'r';
    }
    else
    {
        color_ = finalOutcome_ % 2 == 0 ? 'r' : 'b';
    }
}

void PseudoRoulette::updateParity()
{
    evenNumber_ = finalOutcome_ % 2 == 0;
}

void PseudoRoulette::playColorBet(Player &player, double betAmount)
{
    std::cout << "Enter your color bet (r for red, b for black, g for green): ";
    char betColor = ' ';
    std::cin >> betColor;

    if (betColor != 'r' && betColor != 'b' && betColor != 'g')
    {
        throw PseudoRouletteException("Invalid bet color. Please enter 'r', 'b' or 'g'.");
    }

    generateOutcome();
    displayOutcome();
    settleBet(player, checkBet('c', -1, true, betColor), betAmount, betAmount);
}

void PseudoRoulette::playParityBet(Player &player, double betAmount)
{
    std::cout << "Enter the parity you want to bet on (1 for even, 0 for odd): ";
    int parityChoice = -1;
    std::cin >> parityChoice;

    if (!std::cin || (parityChoice != 0 && parityChoice != 1))
    {
        throw PseudoRouletteException("Invalid bet parity. Please enter '1' for even or '0' for odd.");
    }

    bool betParity = parityChoice == 1;
    generateOutcome();
    displayOutcome();
    settleBet(player, checkBet('p', -1, betParity), betAmount, betAmount);
}

void PseudoRoulette::playNumberBet(Player &player, double betAmount)
{
    clearSelectedNumbers();

    std::cout << "On how many numbers would you like to bet: ";
    int numberOfBets = 0;
    std::cin >> numberOfBets;

    if (!std::cin || numberOfBets <= 0 || numberOfBets > static_cast<int>(selectedNumbers_.size()))
    {
        throw PseudoRouletteException("Invalid number of bets. Please enter a value between 1 and 37.");
    }

    const double totalRisk = betAmount * numberOfBets;
    if (totalRisk > player.getBalance())
    {
        throw PseudoRouletteException("You don't have enough balance to cover all number bets.");
    }

    for (int i = 0; i < numberOfBets; ++i)
    {
        std::cout << "Enter the number you want to bet on (0-36): ";
        int betNumber = -1;
        std::cin >> betNumber;

        if (!std::cin || betNumber < 0 || betNumber > 36)
        {
            throw PseudoRouletteException("Invalid bet number. Please enter a number between 0 and 36.");
        }

        *this += betNumber;
    }

    generateOutcome();
    displayOutcome();
    settleBet(player, checkBet('n', finalOutcome_), betAmount * 35, totalRisk);
}

void PseudoRoulette::settleBet(Player &player, bool won, double payout, double loss)
{
    if (won)
    {
        std::cout << "You win the bet!" << std::endl;
        adjustPlayerBalance(player, payout);
        addScore(Score(player, payout));
    }
    else
    {
        std::cout << "You lose the bet." << std::endl;
        adjustPlayerBalance(player, -loss);
        addScore(Score(player, -loss));
    }
}