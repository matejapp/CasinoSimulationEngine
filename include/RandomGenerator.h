#pragma once

#include <random>

class RandomGenerator
{
public:
    static RandomGenerator &instance();

    int nextInt(int min, int max);
    std::mt19937 &engine();

private:
    RandomGenerator();

    std::mt19937 engine_;
};