#pragma once

// std
#include <exception>

// lox
#include <common/Token.hpp>

namespace Lox {

class ScanningError : public std::exception {
public:
    ScanningError(Token& token, char const* message)
        : mToken(token)
        , mMessage(message)
    {
    }

    ScanningError(Token& token, std::string const& message)
        : mToken(token)
        , mMessage(message)
    {
    }

    Token& getToken() const
    {
        return mToken;
    }

private:
    Token& mToken;
    std::string mMessage;
};

} // namespace Lox
