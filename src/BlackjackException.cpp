#include "BlackjackException.h"

#include <utility>

BlackjackException::BlackjackException(std::string message)
    : BaseException(std::move(message))
{
}