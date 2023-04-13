#pragma once

// std
#include <exception>
#include <memory>
#include <stdexcept>
#include <vector>

// lox
#include "Expr.hpp"
#include "Token.hpp"
#include "TokenType.hpp"

namespace Lox {

class Parser {
public:
  Parser(std::vector<Token> &tokens);

  // TODO: maybe use std::runtime_error
  class ParserError : std::exception {};

private:
  std::unique_ptr<Expr> expression();
  std::unique_ptr<Expr> equality();
  std::unique_ptr<Expr> comparison();
  std::unique_ptr<Expr> term();
  std::unique_ptr<Expr> factor();
  std::unique_ptr<Expr> unary();
  std::unique_ptr<Expr> primary();

  bool match(std::vector<TokenType> types);
  Token consume(TokenType type, std::string message);
  bool check(TokenType type);
  Token advance();
  bool isAtEnd();
  Token peek();
  Token previous();
  ParserError error(Token token, std::string message);
  void synchronize();

  std::vector<Token> &mTokens;

  int mCurrent;
};

} // namespace Lox
