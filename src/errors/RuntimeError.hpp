#pragma once

// std
#include <exception>

// lox
#include <common/Token.hpp>

namespace Lox {

class RuntimeError : public std::exception {
public:
    RuntimeError(Token& token, char const* message)
        : mToken(token)
        , mMessage(message)
    {
    }

    [[nodiscard]] Token& getToken() const
    {
        return mToken;
    }

    [[nodiscard]] char const* what() const noexcept override
    {
        return mMessage;
    }

private:
    Token& mToken;
    char const* mMessage;
};

} // namespace Lox
