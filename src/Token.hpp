#pragma once

// std
#include <string>

// lox
#include "Object.hpp"
#include "TokenType.hpp"

namespace Lox {

class Token {
public:
    Token(TokenType type, std::string const& lexeme, Object literal, int line);
    TokenType getType();
    Object getLiteral();
    std::string getLexeme() const;
    int getLine() const;

    friend std::ostream& operator<<(std::ostream& out, Token const& token);

private:
    const TokenType mType;
    const std::string mLexeme;
    const Object mLiteral;
    int const mLine;
};

} // namespace Lox
