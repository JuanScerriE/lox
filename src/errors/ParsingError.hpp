#pragma once

// std
#include <exception>

// lox
#include <common/Token.hpp>

namespace Lox {

class ParsingError : public std::exception {
public:
    ParsingError(Token& token, char const* message)
        : mToken(token)
        , mMessage(message)
    {
    }

    ParsingError(Token& token, std::string const& message)
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
