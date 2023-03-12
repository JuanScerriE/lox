#pragma once

// std
#include <list>
#include <unordered_map>

// lox
#include "Token.hpp"

namespace Lox {
  class Scanner {
  public:
    Scanner(const std::string& source);
    ~Scanner();
    std::list<Token> scanTokens();

  private:
    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, Object literal);
    bool match(char expected);
    char peek();
    void string();
    void number();
    char peekNext();
    void identifier();

    static bool isDigit(char c);
    static bool isAlpha(char c);
    static bool isAlphaNumeric(char c);

    const std::string mSource;
    std::list<Token> mTokens;

    const std::unordered_map<std::string, TokenType> keywords {
      {"and", TokenType::AND},
      {"class", TokenType::CLASS},
      {"else", TokenType::ELSE},
      {"false", TokenType::FALSE},
      {"for", TokenType::FOR},
      {"fun", TokenType::FUN},
      {"if", TokenType::IF},
      {"nil", TokenType::NIL},
      {"or", TokenType::OR},
      {"print", TokenType::PRINT},
      {"return", TokenType::RETURN},
      {"super", TokenType::SUPER},
      {"this", TokenType::THIS},
      {"true", TokenType::TRUE},
      {"var", TokenType::VAR},
      {"while", TokenType::WHILE},
    };

    int mLine = 1;
    size_t mCurrent = 0;
    size_t mStart = 0;
  };
} // namespace Lox
