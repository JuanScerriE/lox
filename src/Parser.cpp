#include "Parser.hpp"
#include "Lox.hpp"

namespace Lox {

Parser::Parser(std::vector<Token>& tokens)
    : mTokens(tokens)
{
}

std::unique_ptr<Expr> Parser::expression() { return equality(); }

std::unique_ptr<Expr> Parser::equality()
{
    std::unique_ptr<Expr> expr = comparison();

    while (match({ TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL })) {
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

    while (match({ TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS,
        TokenType::LESS_EQUAL })) {
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

    while (match({ TokenType::MINUS, TokenType::PLUS })) {
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

    while (match({ TokenType::SLASH, TokenType::STAR })) {
        std::unique_ptr<Token> oper = std::make_unique<Token>(previous());
        std::unique_ptr<Expr> right = unary();

        expr = std::make_unique<Binary>(std::move(expr), std::move(oper),
            std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::unary()
{
    while (match({ TokenType::BANG, TokenType::MINUS })) {
        std::unique_ptr<Token> oper = std::make_unique<Token>(previous());
        std::unique_ptr<Expr> right = unary();

        return std::make_unique<Unary>(std::move(oper), std::move(right));
    }

    return primary();
}

std::unique_ptr<Expr> Parser::primary()
{
    if (match({ TokenType::FALSE, TokenType::TRUE, TokenType::NUMBER,
            TokenType::STRING })) {
        return std::make_unique<Literal>(
            std::make_unique<Object>(previous().getLiteral()));
    }

    if (match({ TokenType::LEFT_PAREN })) {
        std::unique_ptr<Expr> expr = expression();

        // TODO: continue from page 90
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");

        return std::make_unique<Grouping>(std::move(expr));
    }

    return nullptr;
}

Token Parser::consume(TokenType type, std::string message)
{
    if (check(type)) {
        return advance();
    }

    throw error(peek(), message);
}

bool Parser::match(std::vector<TokenType> types)
{
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type)
{
    if (!isAtEnd()) {
        return false;
    }

    return peek().getType() == type;
}

Token Parser::advance()
{
    if (!isAtEnd())
        mCurrent++;
    return previous();
}

bool Parser::isAtEnd() { return peek().getType() == TokenType::END_OF_FILE; }

Token Parser::peek() { return mTokens[mCurrent]; }

Token Parser::previous() { return mTokens[mCurrent - 1]; }

Parser::ParserError Parser::error(Token token, std::string message)
{
    Runner::error(token, message);

    return ParserError();
}

void Parser::synchronize()
{
    advance();

    while (!isAtEnd()) {
        if (previous().getType() == TokenType::SEMICOLON)
            return;

        switch (peek().getType()) {
        case TokenType::CLASS:
        case TokenType::FUN:
        case TokenType::VAR:
        case TokenType::FOR:
        case TokenType::IF:
        case TokenType::WHILE:
        case TokenType::PRINT:
        case TokenType::RETURN:
            return;
        default:; // do nothing
        }

        advance();
    }
}

} // namespace Lox
