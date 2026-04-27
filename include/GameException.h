#pragma once

#include "BaseException.h"

#include <string>

class GameException : public BaseException
{
public:
    explicit GameException(std::string message);
};