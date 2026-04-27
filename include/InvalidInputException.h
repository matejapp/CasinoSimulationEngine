#pragma once

#include "BaseException.h"

#include <string>

class InvalidInputException : public BaseException
{
public:
    explicit InvalidInputException(std::string message);
};