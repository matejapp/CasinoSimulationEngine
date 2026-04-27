#pragma once

#include <iosfwd>
#include <string>

class Player
{
public:
    Player(std::string name, double balance);

    int getId() const;
    const std::string &getName() const;
    double getBalance() const;

    void setName(std::string name);
    void setBalance(double balance);
    void deposit(double amount);
    void adjustBalance(double amount);

private:
    static int nextId_;

    int id_;
    std::string name_;
    double balance_;

    static std::string normalizeName(std::string name);
};

std::ostream &operator<<(std::ostream &out, const Player &player);
std::istream &operator>>(std::istream &in, Player &player);