// std
#include <cstring>
#include <exception>
#include <iostream>
#include <vector>

// lox
#include "Lox.hpp"
#include "Scanner.hpp"
#include "TokenType.hpp"

namespace Lox {

Scanner::Scanner(std::string const& source)
    : mSource(source)
{
}

std::vector<Token> Scanner::scanTokens()
{
    while (!isAtEnd()) {
        // we are at the beginning of the next lexeme
        mStart = mCurrent;
        scanToken();
    }

    mTokens.push_back(
        Token(TokenType::END_OF_FILE, "", Object::createNil(), mLine));

    return { mTokens.begin(), mTokens.end() };
}

bool Scanner::isAtEnd() { return mCurrent >= mSource.length(); }

void Scanner::scanToken()
{
    char c = advance();

    switch (c) {
    case '(':
        addToken(TokenType::LEFT_PAREN);
        break;
    case ')':
        addToken(TokenType::RIGHT_PAREN);
        break;
    case '{':
        addToken(TokenType::LEFT_BRACE);
        break;
    case '}':
        addToken(TokenType::RIGHT_BRACE);
        break;
    case '.':
        addToken(TokenType::DOT);
        break;
    case ',':
        addToken(TokenType::COMMA);
        break;
    case ';':
        addToken(TokenType::SEMICOLON);
        break;
    case '+':
        addToken(TokenType::PLUS);
        break;
    case '-':
        addToken(TokenType::MINUS);
        break;
    case '*':
        addToken(TokenType::STAR);
        break;
    case '!':
        addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        break;
    case '=':
        addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        break;
    case '<':
        addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
    case '>':
        addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;
    case '/':
        if (match('/')) {
            while (peek() != '\n' && !isAtEnd()) {
                advance();
            }
        } else {
            addToken(TokenType::SLASH);
        }
        break;
    case ' ':
    case '\r':
    case '\t':
        // ignore whitespace
        break;
    case '\n':
        mLine++;
        break;
    case '"':
        string();
        break;
    default:
        if (isDigit(c)) {
            number();
        } else if (isAlpha(c)) {
            identifier();
        } else {
            Runner::error(mLine, "lox: unexpected character");
        }
        break;
    }
}

char Scanner::advance() { return mSource[mCurrent++]; }

void Scanner::addToken(TokenType type)
{
    addToken(type, Object::createNil());
}

void Scanner::addToken(TokenType type, Object literal)
{
    mTokens.push_back(
        Token(type, mSource.substr(mStart, mCurrent - mStart), literal, mLine));
}

bool Scanner::match(char expected)
{
    if (isAtEnd()) {
        return false;
    }

    if (mSource[mCurrent] != expected) {
        return false;
    }

    mCurrent++;

    return true;
}

char Scanner::peek()
{
    if (isAtEnd()) {
        return '\0';
    }

    return mSource[mCurrent];
}

void Scanner::string()
{
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') {
            mLine++;
        }

        advance();
    }

    if (isAtEnd()) {
        Runner::error(mLine, "lox: unterminated string");
        return;
    }

    // the closing "
    advance();

    // we can use substring contructor
    std::string value(mSource, mStart + 1, mCurrent - 1 - mStart - 1);

    addToken(TokenType::STRING, Object::createString(value));
}

void Scanner::number()
{
    while (isDigit(peek())) {
        advance();
    }

    // look for fractional part
    if (peek() == '.' && isDigit(peekNext())) {
        // consume the "."
        advance();
        while (isDigit(peek())) {
            advance();
        }
    }

    addToken(TokenType::NUMBER,
        Object::createNumber(atof(mSource.substr(mStart, mCurrent - mStart).c_str())));
}

char Scanner::peekNext()
{
    if (mCurrent + 1 >= mSource.length()) {
        return '\0';
    }

    return mSource[mCurrent + 1];
}

void Scanner::identifier()
{
    while (isAlphaNumeric(peek())) {
        advance();
    }

    std::string text = mSource.substr(mStart, mCurrent - mStart);

    try {
        addToken(keywords.at(text));
    } catch (std::exception& ex) {
        addToken(TokenType::IDENTIFIER);
    }
}

bool Scanner::isDigit(char c) { return c >= '0' && c <= '9'; }

bool Scanner::isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isAlphaNumeric(char c) { return isDigit(c) || isAlpha(c); }

} // namespace Lox
