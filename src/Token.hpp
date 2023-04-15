#pragma once

// std
#include <string>
#include <vector>

// lox
#include "Object.hpp"
#include "TokenType.hpp"

namespace Lox {

class Token {
public:
    Token(Token const&);
    Token(TokenType type, std::string const& lexeme, Object literal, int line);
    TokenType getType();
    Object getLiteral();
    std::string getLexeme() const;
    int getLine() const;

    friend std::ostream& operator<<(std::ostream& out, Token const& token);
    friend std::ostream& operator<<(std::ostream& out, std::vector<Token> const& token);

private:
    TokenType mType;
    std::string mLexeme;
    Object mLiteral;
    int mLine;
};

} // namespace Lox
