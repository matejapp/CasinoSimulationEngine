#include "Player.h"

#include "PlayerException.h"

#include <iostream>
#include <utility>

int Player::nextId_ = 1;

Player::Player(std::string name, double balance)
    : id_(nextId_++), name_(normalizeName(std::move(name))), balance_(balance)
{
    if (balance < 0)
    {
        throw PlayerException("Player balance cannot be negative.");
    }
}

int Player::getId() const
{
    return id_;
}

const std::string &Player::getName() const
{
    return name_;
}

double Player::getBalance() const
{
    return balance_;
}

void Player::setName(std::string name)
{
    name_ = normalizeName(std::move(name));
}

void Player::setBalance(double balance)
{
    if (balance < 0)
    {
        throw PlayerException("Player balance cannot be negative.");
    }
    balance_ = balance;
}

void Player::deposit(double amount)
{
    if (amount <= 0)
    {
        throw PlayerException("Deposit amount must be positive.");
    }
    balance_ += amount;
}

void Player::adjustBalance(double amount)
{
    setBalance(balance_ + amount);
}

std::string Player::normalizeName(std::string name)
{
    if (name.length() > 80)
    {
        return name.substr(0, 80);
    }
    return name;
}

std::ostream &operator<<(std::ostream &out, const Player &player)
{
    out << "Player ID: " << player.getId()
        << ", Name: " << player.getName()
        << ", Balance: " << player.getBalance();
    return out;
}

std::istream &operator>>(std::istream &in, Player &player)
{
    std::string name;
    double balance = 0.0;

    std::cout << "Enter player name: ";
    in >> name;
    std::cout << "Enter balance: ";
    in >> balance;

    if (in)
    {
        player.setName(name);
        player.setBalance(balance);
    }

    return in;
}