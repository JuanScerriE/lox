// std
#include <iostream>

// lox
#include "Object.hpp"
#include "Token.hpp"

namespace Lox {

Token::Token(TokenType type, std::string const& lexeme, Object literal,
    int line)
    : mType(type)
    , mLexeme(lexeme)
    , mLiteral(literal)
    , mLine(line)
{
}

std::ostream& operator<<(std::ostream& out, Token const& token)
{
    switch (token.mType) {
    case TokenType::LEFT_PAREN:
        out << "LEFT_PAREN " << token.mLexeme;
        break;
    case TokenType::RIGHT_PAREN:
        out << "RIGHT_PAREN " << token.mLexeme;
        break;
    case TokenType::LEFT_BRACE:
        out << "LEFT_BRACE " << token.mLexeme;
        break;
    case TokenType::RIGHT_BRACE:
        out << "RIGHT_BRACE " << token.mLexeme;
        break;
    case TokenType::COMMA:
        out << "COMMA " << token.mLexeme;
        break;
    case TokenType::DOT:
        out << "DOT " << token.mLexeme;
        break;
    case TokenType::MINUS:
        out << "MINUS " << token.mLexeme;
        break;
    case TokenType::PLUS:
        out << "PLUS " << token.mLexeme;
        break;
    case TokenType::SEMICOLON:
        out << "SEMICOLON " << token.mLexeme;
        break;
    case TokenType::SLASH:
        out << "SLASH " << token.mLexeme;
        break;
    case TokenType::STAR:
        out << "STAR " << token.mLexeme;
        break;
    case TokenType::BANG:
        out << "BANG " << token.mLexeme;
        break;
    case TokenType::BANG_EQUAL:
        out << "BANG_EQUAL " << token.mLexeme;
        break;
    case TokenType::EQUAL:
        out << "EQUAL " << token.mLexeme;
        break;
    case TokenType::EQUAL_EQUAL:
        out << "EQUAL_EQUAL " << token.mLexeme;
        break;
    case TokenType::GREATER:
        out << "GREATER " << token.mLexeme;
        break;
    case TokenType::GREATER_EQUAL:
        out << "GREATER_EQUAL " << token.mLexeme;
        break;
    case TokenType::LESS:
        out << "LESS " << token.mLexeme;
        break;
    case TokenType::LESS_EQUAL:
        out << "LESS_EQUAL " << token.mLexeme;
        break;
    case TokenType::IDENTIFIER:
        out << "IDENTIFIER " << token.mLexeme;
        break;
    case TokenType::STRING:
        out << "STRING " << token.mLexeme << " " << token.mLiteral.toString();
        break;
    case TokenType::NUMBER:
        out << "NUMBER " << token.mLexeme << " " << token.mLiteral.toString();
        break;
    case TokenType::AND:
        out << "AND " << token.mLexeme;
        break;
    case TokenType::CLASS:
        out << "CLASS " << token.mLexeme;
        break;
    case TokenType::ELSE:
        out << "ELSE " << token.mLexeme;
        break;
    case TokenType::FALSE:
        out << "FALSE " << token.mLexeme;
        break;
    case TokenType::FUN:
        out << "FUN " << token.mLexeme;
        break;
    case TokenType::FOR:
        out << "FOR " << token.mLexeme;
        break;
    case TokenType::IF:
        out << "IF " << token.mLexeme;
        break;
    case TokenType::NIL:
        out << "NIL " << token.mLexeme;
        break;
    case TokenType::OR:
        out << "OR " << token.mLexeme;
        break;
    case TokenType::PRINT:
        out << "PRINT " << token.mLexeme;
        break;
    case TokenType::RETURN:
        out << "RETURN " << token.mLexeme;
        break;
    case TokenType::SUPER:
        out << "SUPER " << token.mLexeme;
        break;
    case TokenType::THIS:
        out << "THIS " << token.mLexeme;
        break;
    case TokenType::TRUE:
        out << "TRUE " << token.mLexeme;
        break;
    case TokenType::VAR:
        out << "VAR " << token.mLexeme;
        break;
    case TokenType::WHILE:
        out << "WHILE " << token.mLexeme;
        break;
    case TokenType::END_OF_FILE:
        out << "END_OF_FILE " << token.mLexeme;
        break;
    }

    return out;
}

TokenType Token::getType() { return mType; }

Object Token::getLiteral() { return mLiteral; }

std::string Token::getLexeme() const { return mLexeme; }

int Token::getLine() const { return mLine; }

} // namespace Lox
