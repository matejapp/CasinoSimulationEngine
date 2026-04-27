#include "BaseException.h"

#include <utility>

BaseException::BaseException(std::string message)
    : message_(std::move(message))
{
}

const char *BaseException::what() const noexcept
{
    return message_.c_str();
}