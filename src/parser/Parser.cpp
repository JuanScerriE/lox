
// std
#include <iostream>

// lox
#include <parser/Parser.hpp>
#include <runner/Runner.hpp>

namespace Lox {

Parser::Parser(std::vector<Token>& tokens)
    : mTokens(tokens)
{
}

std::unique_ptr<Expr> Parser::parse()
{
    try {
        return expression();
    } catch (Error& error) {
        return nullptr;
    }
}

std::unique_ptr<Expr> Parser::expression()
{
    return equality();
}

std::unique_ptr<Expr> Parser::equality()
{
    std::unique_ptr<Expr> expr = comparison();

    while (match({ Token::Type::BANG_EQUAL, Token::Type::EQUAL_EQUAL })) {
        std::unique_ptr<Token> oper = std::make_unique<Token>(previous());
        std::unique_ptr<Expr> right = comparison();

        expr = std::make_unique<Binary>(std::move(expr), std::move(oper),
            std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::comparison()
{
    std::unique_ptr<Expr> expr = term();

    while (match({ Token::Type::GREATER, Token::Type::GREATER_EQUAL, Token::Type::LESS,
        Token::Type::LESS_EQUAL })) {
        std::unique_ptr<Token> oper = std::make_unique<Token>(previous());
        std::unique_ptr<Expr> right = term();

        expr = std::make_unique<Binary>(std::move(expr), std::move(oper),
            std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::term()
{
    std::unique_ptr<Expr> expr = factor();

    while (match({ Token::Type::MINUS, Token::Type::PLUS })) {
        std::unique_ptr<Token> oper = std::make_unique<Token>(previous());
        std::unique_ptr<Expr> right = factor();

        expr = std::make_unique<Binary>(std::move(expr), std::move(oper),
            std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::factor()
{
    std::unique_ptr<Expr> expr = unary();

    while (match({ Token::Type::SLASH, Token::Type::STAR })) {
        std::unique_ptr<Token> oper = std::make_unique<Token>(previous());
        std::unique_ptr<Expr> right = unary();

        expr = std::make_unique<Binary>(std::move(expr), std::move(oper),
            std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::unary()
{
    while (match({ Token::Type::BANG, Token::Type::MINUS })) {
        std::unique_ptr<Token> oper = std::make_unique<Token>(previous());
        std::unique_ptr<Expr> right = unary();

        return std::make_unique<Unary>(std::move(oper), std::move(right));
    }

    return primary();
}

std::unique_ptr<Expr> Parser::primary()
{
    if (match({ Token::Type::FALSE, Token::Type::TRUE, Token::Type::NUMBER,
            Token::Type::STRING })) {
        return std::make_unique<Literal>(
            std::make_unique<Value>(previous().getLiteral()));
    }

    if (match({ Token::Type::LEFT_PAREN })) {
        std::unique_ptr<Expr> expr = expression();

        consume(Token::Type::RIGHT_PAREN, "Expect ')' after expression.");

        return std::make_unique<Grouping>(std::move(expr));
    }

    throw error(peek(), "Expect expression.");
}

Token Parser::consume(Token::Type type, std::string message)
{
    if (check(type)) {
        return advance();
    }

    throw error(peek(), message);
}

bool Parser::match(std::vector<Token::Type> types)
{
    for (Token::Type type : types) {
        if (check(type)) {
            advance();

            return true;
        }
    }

    return false;
}

bool Parser::check(Token::Type type)
{
    if (isAtEnd()) {
        return false;
    }

    return peek().getType() == type;
}

Token Parser::advance()
{
    if (!isAtEnd()) {
        mCurrent++;
    }

    return previous();
}

bool Parser::isAtEnd() { return peek().getType() == Token::Type::END_OF_FILE; }

Token Parser::peek() { return mTokens[mCurrent]; }

Token Parser::previous() { return mTokens[mCurrent - 1]; }

Parser::Error Parser::error(Token token, std::string message)
{
    // Runner::error(token, message);

    return Error();
}

void Parser::synchronize()
{
    advance();

    while (!isAtEnd()) {
        if (previous().getType() == Token::Type::SEMICOLON)
            return;

        switch (peek().getType()) {
        case Token::Type::CLASS:
        case Token::Type::FUN:
        case Token::Type::VAR:
        case Token::Type::FOR:
        case Token::Type::IF:
        case Token::Type::WHILE:
        case Token::Type::PRINT:
        case Token::Type::RETURN:
            return;
        default:; // Do nothing
        }

        advance();
    }
}

} // namespace Lox
