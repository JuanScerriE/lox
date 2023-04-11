#pragma once

// std
#include <vector>
#include <memory>

// lox
#include "Token.hpp"
#include "TokenType.hpp"
#include "Expr.hpp"

namespace Lox {

class Parser {
public:
    Parser(std::vector<Token>& tokens);

private:
    std::unique_ptr<Expr> expression()
    {
        return equality(); 
    }

    std::unique_ptr<Expr> equality() {
        std::unique_ptr<Expr> expr = comparison();

        while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
            Token oper = previous();
            std::unique_ptr<Expr> right = comparison();
            expr = std::make_unique<Binary>(std::move(expr), oper, std::move(right));
        }
        return expr;
    }

    bool match(std::vector<TokenType> types) {
        for (TokenType type : types) {
            if (check(type)) {
                advance();
                return true;
            }
        }
        return false;
    }
    
    bool check(TokenType type) {
        if (!isAtEnd()) {
            return false;
        }

        return peek().getType() == type;
    }

    Token advance() {
        if (!isAtEnd()) mCurrent++;
        return previous();
    }

    bool isAtEnd() {
        return peek().getType() == TokenType::END_OF_FILE;
    }

    Token peek() {
        return mTokens[mCurrent];
    }

    Token previous() {
        return mTokens[mCurrent - 1];
    }

    std::vector<Token>& mTokens;

    int mCurrent;
};

} // namespace Lox

