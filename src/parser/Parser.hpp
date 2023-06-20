#pragma once

// std
#include <exception>
#include <memory>
#include <stdexcept>
#include <vector>

// lox
#include <common/Expr.hpp>
#include <common/Token.hpp>

namespace Lox {

class Parser {
public:
    Parser(std::vector<Token>& tokens);

    // TODO: maybe use std::runtime_error
    class Error : std::exception { };

    std::unique_ptr<Expr> parse();

private:
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> term();
    std::unique_ptr<Expr> factor();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();

    bool match(std::vector<Token::Type> types);
    Token consume(Token::Type type, std::string message);
    bool check(Token::Type type);
    Token advance();
    bool isAtEnd();
    Token peek();
    Token previous();
    Error error(Token token, std::string message);
    void synchronize();

    std::vector<Token>& mTokens;

    int mCurrent = 0;
};

} // namespace Lox
