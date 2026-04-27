#include "BaseException.h"
#include "Casino.h"
#include "CasinoData.h"
#include "CasinoRepository.h"

#include <iostream>
#include <string>

int main()
{
    try
    {
        CasinoRepository repository("casino_data.txt");
        CasinoData data;

        if (repository.load(data))
        {
            std::cout << "Previous data found!" << std::endl;
            std::cout << "Welcome back, " << data.playerName << "! your balance is: " << data.playerBalance << std::endl;
        }
        else
        {
            std::cout << "no previous data found. starting a new game!" << std::endl;
            std::cout << "enter your name: ";
            std::cin >> data.playerName;
            std::cout << "enter your starting balance: ";
            std::cin >> data.playerBalance;
            data.budget = 5000;

            if (repository.save(data))
            {
                std::cout << "Initial game data saved successfully!" << std::endl;
            }
            else
            {
                std::cout << "Failed to save initial game data." << std::endl;
            }
        }

        Casino casino(data, repository);
        casino.addGame("Roulette");
        casino.addGame("Blackjack");
        casino.run();
        return 0;
    }
    catch (const BaseException &exception)
    {
        std::cout << exception.what() << std::endl;
    }
    catch (const std::exception &exception)
    {
        std::cout << exception.what() << std::endl;
    }

    return 1;
}