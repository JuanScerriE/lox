#pragma once

// std
#include <memory>
#include <vector>

// lox
#include "Expr.hpp"
#include "Token.hpp"
#include "TokenType.hpp"

namespace Lox {

class Parser {
public:
    Parser(std::vector<Token>& tokens);

private:
    std::unique_ptr<Expr> expression()
    {
        return equality();
    }

    std::unique_ptr<Expr> equality()
    {
        std::unique_ptr<Expr> expr = comparison();

        while (match({ TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL })) {
            std::unique_ptr<Token> oper = std::make_unique<Token>(previous());
            std::unique_ptr<Expr> right = comparison();

            expr = std::make_unique<Binary>(std::move(expr), std::move(oper), std::move(right));
        }

        return expr;
    }

    std::unique_ptr<Expr> comparison()
    {
        std::unique_ptr<Expr> expr = term();

        while (match({ TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL })) {
            std::unique_ptr<Token> oper = std::make_unique<Token>(previous());
            std::unique_ptr<Expr> right = term();

            expr = std::make_unique<Binary>(std::move(expr), std::move(oper), std::move(right));
        }

        return expr;
    }

    std::unique_ptr<Expr> term()
    {
        std::unique_ptr<Expr> expr = factor();

        while (match({ TokenType::MINUS, TokenType::PLUS })) {
            std::unique_ptr<Token> oper = std::make_unique<Token>(previous());
            std::unique_ptr<Expr> right = factor();

            expr = std::make_unique<Binary>(std::move(expr), std::move(oper), std::move(right));
        }

        return expr;
    }

    std::unique_ptr<Expr> factor()
    {
        std::unique_ptr<Expr> expr = unary();

        while (match({ TokenType::SLASH, TokenType::STAR })) {
            std::unique_ptr<Token> oper = std::make_unique<Token>(previous());
            std::unique_ptr<Expr> right = unary();

            expr = std::make_unique<Binary>(std::move(expr), std::move(oper), std::move(right));
        }

        return expr;
    }

    std::unique_ptr<Expr> unary()
    {
        while (match({ TokenType::BANG, TokenType::MINUS })) {
            std::unique_ptr<Token> oper = std::make_unique<Token>(previous());
            std::unique_ptr<Expr> right = unary();

            return std::make_unique<Unary>(std::move(oper), std::move(right));
        }

        return primary();
    }

    std::unique_ptr<Expr> primary()
    {
        if (match({ TokenType::FALSE, TokenType::TRUE, TokenType::NUMBER, TokenType::STRING })) {
            return std::make_unique<Literal>(std::make_unique<Object>(previous().getLiteral()));
        }

        if (match({ TokenType::LEFT_PAREN })) {
            std::unique_ptr<Expr> expr = expression();

            // TODO: continue from page 90
            consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");

            return std::make_unique<Grouping>(std::move(expr));
        }
    }

    bool match(std::vector<TokenType> types)
    {
        for (TokenType type : types) {
            if (check(type)) {
                advance();
                return true;
            }
        }
        return false;
    }

    bool check(TokenType type)
    {
        if (!isAtEnd()) {
            return false;
        }

        return peek().getType() == type;
    }

    Token advance()
    {
        if (!isAtEnd())
            mCurrent++;
        return previous();
    }

    bool isAtEnd()
    {
        return peek().getType() == TokenType::END_OF_FILE;
    }

    Token peek()
    {
        return mTokens[mCurrent];
    }

    Token previous()
    {
        return mTokens[mCurrent - 1];
    }

    std::vector<Token>& mTokens;

    int mCurrent;
};

} // namespace Lox
