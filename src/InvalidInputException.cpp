#include "InvalidInputException.h"

#include <utility>

InvalidInputException::InvalidInputException(std::string message)
    : BaseException(std::move(message))
{
}