#include "GameException.h"

#include <utility>

GameException::GameException(std::string message)
    : BaseException(std::move(message))
{
}