#include "CasinoMenus.h"

#include "Casino.h"
#include "Player.h"

#include <iomanip>
#include <iostream>

void CasinoMenus::showCasinoMenu(const Player &player, const Casino &casino)
{
    std::cout << "=======================================\n";
    std::cout << "||          CASINO ROYALE           ||\n";
    std::cout << "=======================================\n";
    std::cout << "|| Player: " << std::setw(25) << std::left << player.getName() << "||\n";
    std::cout << "|| Balance: $" << std::setw(22) << std::fixed << std::setprecision(2) << player.getBalance() << "||\n";
    std::cout << "|| Casino: $" << std::setw(23) << casino.getBudget() << "||\n";
    std::cout << "=======================================\n";
    std::cout << "||          MENU OPTIONS            ||\n";
    std::cout << "|| 1. Add Funds                     ||\n";
    std::cout << "|| 2. Select Game                   ||\n";
    std::cout << "|| 3. Quit                          ||\n";
    std::cout << "|| 4. Clear Console                 ||\n";
    std::cout << "=======================================\n";
}

void CasinoMenus::showBlackjackMenu(const Player &player, const Casino &casino)
{
    std::cout << "=======================================\n";
    std::cout << "||           BLACKJACK              ||\n";
    std::cout << "=======================================\n";
    std::cout << "|| Player: " << std::setw(25) << std::left << player.getName() << "||\n";
    std::cout << "|| Balance: $" << std::setw(22) << std::fixed << std::setprecision(2) << player.getBalance() << "||\n";
    std::cout << "|| Casino: $" << std::setw(23) << casino.getBudget() << "||\n";
    std::cout << "=======================================\n";
    std::cout << "||         GAME OPTIONS             ||\n";
    std::cout << "|| 1. Shuffle Deck                  ||\n";
    std::cout << "|| 2. Start Game                    ||\n";
    std::cout << "|| 3. Return to Main Menu           ||\n";
    std::cout << "|| 4. Clear Console                 ||\n";
    std::cout << "=======================================\n";
}

void CasinoMenus::showRouletteMenu(const Player &player, const Casino &casino)
{
    std::cout << "=======================================\n";
    std::cout << "||           ROULETTE               ||\n";
    std::cout << "=======================================\n";
    std::cout << "|| Player: " << std::setw(25) << std::left << player.getName() << "||\n";
    std::cout << "|| Balance: $" << std::setw(22) << std::fixed << std::setprecision(2) << player.getBalance() << "||\n";
    std::cout << "|| Casino: $" << std::setw(23) << casino.getBudget() << "||\n";
    std::cout << "=======================================\n";
    std::cout << "||         GAME OPTIONS             ||\n";
    std::cout << "|| 1. Place a Bet                   ||\n";
    std::cout << "|| 2. View Last 10 Numbers          ||\n";
    std::cout << "|| 3. Return to Main Menu           ||\n";
    std::cout << "|| 4. Clear Console                 ||\n";
    std::cout << "=======================================\n";
}