#include "Blackjack.h"

#include "BlackjackException.h"
#include "RandomGenerator.h"
#include "Score.h"

#include <algorithm>
#include <iostream>

Blackjack::Blackjack()
    : Game("Blackjack"), dealerScore_(0), dealerScoreGenerated_(false), nextCardIndex_(0)
{
    resetGame();
}

void Blackjack::resetGame()
{
    buildDeck();
    std::shuffle(deck_.begin(), deck_.end(), RandomGenerator::instance().engine());
    hand_.clear();
    dealerScore_ = 0;
    dealerScoreGenerated_ = false;
    nextCardIndex_ = 0;
}

void Blackjack::startGame(Player &player)
{
    if (player.getBalance() < 10)
    {
        throw BlackjackException("You dont have enough balance to play games (balance < 10).");
    }

    std::cout << "Starting blackjack. Drawing 2 cards..." << std::endl;
    drawCard();
    drawCard();

    while (true)
    {
        std::cout << "Hit or stand ('h'/'s'): ";
        char hitOrStand = ' ';
        std::cin >> hitOrStand;

        if (hitOrStand != 'h' && hitOrStand != 's')
        {
            throw BlackjackException("Invalid input. Please enter 'h' or 's'.");
        }

        if (hitOrStand == 's')
        {
            break;
        }

        drawCard();

        if (isBust())
        {
            break;
        }
    }

    if (checkWinner())
    {
        printHand();
        std::cout << "Dealer's hand: " << getDealerHand() << std::endl;
        std::cout << "You win!" << std::endl;
        adjustPlayerBalance(player, 3);
        addScore(Score(player, 3));
    }
    else if (isBust())
    {
        std::cout << "You bust!" << std::endl;
        adjustPlayerBalance(player, -3);
        addScore(Score(player, -3));
    }
    else
    {
        printHand();
        std::cout << "Dealer's hand: " << getDealerHand() << std::endl;
        std::cout << "You lose!" << std::endl;
        adjustPlayerBalance(player, -3);
        addScore(Score(player, -3));
    }

    resetGame();
}

int Blackjack::drawCard()
{
    if (nextCardIndex_ >= deck_.size())
    {
        throw BlackjackException("Deck is empty! No more cards to draw.");
    }

    int card = deck_[nextCardIndex_++];
    hand_.push_back(card);
    printHand();
    return calculateScore();
}

int Blackjack::calculateScore() const
{
    int score = 0;
    int aceCount = 0;

    for (int card : hand_)
    {
        if (card >= 2 && card <= 10)
        {
            score += card;
        }
        else if (card >= 11 && card <= 13)
        {
            score += 10;
        }
        else if (card == 1)
        {
            ++aceCount;
        }
    }

    for (int i = 0; i < aceCount; ++i)
    {
        score += score + 11 <= 21 ? 11 : 1;
    }

    return score;
}

int Blackjack::getDealerHand()
{
    if (!dealerScoreGenerated_)
    {
        dealerScore_ = RandomGenerator::instance().nextInt(15, 25);
        dealerScoreGenerated_ = true;
    }
    return dealerScore_;
}

bool Blackjack::isBust() const
{
    return calculateScore() > 21;
}

bool Blackjack::checkWinner()
{
    int dealer = getDealerHand();
    int player = calculateScore();
    return dealer > 21 || (player <= 21 && player >= dealer);
}

void Blackjack::printHand() const
{
    std::cout << "Current hand: ";
    for (int card : hand_)
    {
        std::cout << card << " ";
    }
    std::cout << "| Score: " << calculateScore() << std::endl;
}

void Blackjack::buildDeck()
{
    deck_.clear();
    deck_.reserve(52);

    for (int card = 1; card <= 13; ++card)
    {
        for (int suit = 0; suit < 4; ++suit)
        {
            deck_.push_back(card);
        }
    }
}