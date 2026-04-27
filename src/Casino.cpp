#include "Casino.h"

#include "BaseException.h"
#include "CasinoMenus.h"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <utility>

Casino::Casino(const CasinoData &data, CasinoRepository repository)
    : budget_(data.budget),
      player_(data.playerName, data.playerBalance),
      repository_(std::move(repository))
{
}

Casino::~Casino()
{
    saveData();
}

double Casino::getBudget() const
{
    return budget_;
}

double Casino::operator-(double amount)
{
    budget_ -= amount;
    return budget_;
}

double Casino::operator+(double amount)
{
    budget_ += amount;
    return budget_;
}

void Casino::addGame(const std::string &gameName)
{
    games_.push_back(gameName);
    std::cout << "Game \"" << gameName << "\" added to the casino." << std::endl;
}

void Casino::showGames() const
{
    if (games_.empty())
    {
        std::cout << "No games available." << std::endl;
        return;
    }

    std::cout << "Available games:" << std::endl;
    for (std::size_t i = 0; i < games_.size(); ++i)
    {
        std::cout << i + 1 << ". " << games_[i] << std::endl;
    }
}

void Casino::run()
{
    while (true)
    {
        CasinoMenus::showCasinoMenu(player_, *this);
        std::cout << "Enter your choice: ";

        int choice = 0;
        std::cin >> choice;

        if (!std::cin)
        {
            clearInput();
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
            continue;
        }

        try
        {
            switch (choice)
            {
            case 1:
                handleDeposit();
                break;

            case 2:
                handleGameSelection();
                break;

            case 3:
                std::cout << "Quitting game..." << std::endl;
                return;

            case 4:
                clearConsole();
                break;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
        catch (const BaseException &exception)
        {
            clearInput();
            std::cout << exception.what() << std::endl;
        }
    }
}

CasinoData Casino::toData() const
{
    CasinoData data;
    data.budget = budget_;
    data.playerName = player_.getName();
    data.playerBalance = player_.getBalance();
    return data;
}

void Casino::saveData() const
{
    if (repository_.save(toData()))
    {
        std::cout << "Game data saved successfuly." << std::endl;
    }
    else
    {
        std::cout << "Failed to save game data." << std::endl;
    }
}

void Casino::handleDeposit()
{
    std::cout << "Enter the amount you would like to deposit: ";
    double deposit = 0.0;
    std::cin >> deposit;

    if (!std::cin)
    {
        clearInput();
        std::cout << "Invalid input. Please enter a valid number." << std::endl;
        return;
    }

    player_.deposit(deposit);
}

void Casino::handleGameSelection()
{
    showGames();

    int gameChoice = 0;
    std::cin >> gameChoice;

    if (!std::cin)
    {
        clearInput();
        std::cout << "Invalid input. Please enter a valid number." << std::endl;
        return;
    }

    if (gameChoice == 1)
    {
        runRouletteMenu();
    }
    else if (gameChoice == 2)
    {
        runBlackjackMenu();
    }
    else
    {
        std::cout << "Invalid game choice. Please try again." << std::endl;
    }
}

void Casino::runRouletteMenu()
{
    bool inMenu = true;
    while (inMenu)
    {
        CasinoMenus::showRouletteMenu(player_, *this);
        std::cout << "Enter your choice: ";

        int rouletteChoice = 0;
        std::cin >> rouletteChoice;

        if (!std::cin)
        {
            clearInput();
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
            continue;
        }

        try
        {
            switch (rouletteChoice)
            {
            case 1:
                rouletteGame_.startGame(player_);
                break;

            case 2:
                rouletteGame_.displayHistory();
                break;

            case 3:
                inMenu = false;
                break;

            case 4:
                clearConsole();
                break;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
        catch (const BaseException &exception)
        {
            clearInput();
            std::cout << exception.what() << std::endl;
        }
    }
}

void Casino::runBlackjackMenu()
{
    bool inMenu = true;
    while (inMenu)
    {
        CasinoMenus::showBlackjackMenu(player_, *this);
        std::cout << "Enter your choice: ";

        int blackjackChoice = 0;
        std::cin >> blackjackChoice;

        if (!std::cin)
        {
            clearInput();
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
            continue;
        }

        try
        {
            switch (blackjackChoice)
            {
            case 1:
                std::cout << "Shuffling deck..." << std::endl;
                blackjackGame_.resetGame();
                std::cout << "Deck has been shuffled." << std::endl;
                break;

            case 2:
                blackjackGame_.startGame(player_);
                break;

            case 3:
                inMenu = false;
                break;

            case 4:
                clearConsole();
                break;

            default:
                std::cout << "Invalid choice. Try again" << std::endl;
                break;
            }
        }
        catch (const BaseException &exception)
        {
            clearInput();
            std::cout << exception.what() << std::endl;
        }
    }
}

void Casino::clearInput() const
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Casino::clearConsole() const
{
    std::system("cls");
}