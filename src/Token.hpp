#pragma once

// std
#include <string>

// lox
#include "TokenType.hpp"
#include "Literal.hpp"

namespace Lox {
  class Token {
  public:
    Token(TokenType type, const std::string& lexeme, Literal literal, int line);
    TokenType getType();
    Literal getLiteral();

    friend std::ostream& operator<<(std::ostream& out, const Token& token);

  private:
    const TokenType mType;
    const std::string mLexeme;
    const Literal mLiteral;
    const int mLine;
  };
} // namespace Lox
