#pragma once

// std
#include <string>

// lox
#include "TokenType.hpp"
#include "Object.hpp"

namespace Lox {
  class Token {
  public:
    Token(TokenType type, const std::string& lexeme, Object literal, int line);
    TokenType getType();
    Object getLiteral();

    friend std::ostream& operator<<(std::ostream& out, const Token& token);

  private:
    const TokenType mType;
    const std::string mLexeme;
    const Object mLiteral;
    const int mLine;
  };
} // namespace Lox
