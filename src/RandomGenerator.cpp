#include "RandomGenerator.h"

RandomGenerator::RandomGenerator()
    : engine_(std::random_device{}())
{
}

RandomGenerator &RandomGenerator::instance()
{
    static RandomGenerator generator;
    return generator;
}

int RandomGenerator::nextInt(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(engine_);
}

std::mt19937 &RandomGenerator::engine()
{
    return engine_;
}