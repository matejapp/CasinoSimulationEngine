#include "PlayerException.h"

#include <utility>

PlayerException::PlayerException(std::string message)
    : BaseException(std::move(message))
{
}