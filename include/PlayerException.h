#pragma once

#include "BaseException.h"

#include <string>

class PlayerException : public BaseException
{
public:
    explicit PlayerException(std::string message);
};