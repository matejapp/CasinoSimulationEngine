#include "PseudoRouletteException.h"

#include <utility>

PseudoRouletteException::PseudoRouletteException(std::string message)
    : BaseException(std::move(message))
{
}