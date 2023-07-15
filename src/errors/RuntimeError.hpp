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

    RuntimeError(Token& token, std::string const& message)
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

}
