#pragma once

#include "BaseException.h"

#include <string>

class BlackjackException : public BaseException
{
public:
    explicit BlackjackException(std::string message);
};