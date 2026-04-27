#pragma once

#include <exception>
#include <string>

class BaseException : public std::exception
{
public:
    explicit BaseException(std::string message);
    const char *what() const noexcept override;

private:
    std::string message_;
};