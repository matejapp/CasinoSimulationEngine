#pragma once

#include "BaseException.h"

#include <string>

class PseudoRouletteException : public BaseException
{
public:
    explicit PseudoRouletteException(std::string message);
};