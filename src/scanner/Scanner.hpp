#pragma once

// std
#include <list>
#include <unordered_map>
#include <vector>

// lox
#include "../common/Token.hpp"

namespace Lox {

class Scanner {
public:
    Scanner(std::string const& source);
    std::vector<Token> scanTokens();

private:
    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(Token::Type type);
    void addToken(Token::Type type, Value literal);
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

    // TODO: Checkout how this compiles with constexpr and
    // consteval. We just need to be embedded in the binary.
    const std::unordered_map<std::string, Token::Type> keywords {
        { "and", Token::Type::AND },
        { "class", Token::Type::CLASS },
        { "else", Token::Type::ELSE },
        { "false", Token::Type::FALSE },
        { "for", Token::Type::FOR },
        { "fun", Token::Type::FUN },
        { "if", Token::Type::IF },
        { "nil", Token::Type::NIL },
        { "or", Token::Type::OR },
        { "print", Token::Type::PRINT },
        { "return", Token::Type::RETURN },
        { "super", Token::Type::SUPER },
        { "this", Token::Type::THIS },
        { "true", Token::Type::TRUE },
        { "var", Token::Type::VAR },
        { "while", Token::Type::WHILE },
    };

    int mLine = 1;
    size_t mCurrent = 0;
    size_t mStart = 0;
};

} // namespace Lox
