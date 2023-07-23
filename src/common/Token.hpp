#pragma once

// std
#include <string>
#include <vector>

// lox
#include <common/Value.hpp>

namespace Lox {

class Token {
public:
    enum class Type {
        // single character tokens
        LEFT_PAREN,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        COMMA,
        DOT,
        MINUS,
        PLUS,
        SEMICOLON,
        SLASH,
        STAR,

        // one or two character tokens
        BANG,
        BANG_EQUAL,
        EQUAL,
        EQUAL_EQUAL,
        GREATER,
        GREATER_EQUAL,
        LESS,
        LESS_EQUAL,

        // literals
        IDENTIFIER,
        STRING,
        NUMBER,

        // keywords
        AND,
        CLASS,
        ELSE,
        FALSE,
        FUN,
        FOR,
        IF,
        NIL,
        OR,
        PRINT,
        RETURN,
        SUPER,
        THIS,
        TRUE,
        VAR,
        WHILE,

        END_OF_FILE
    };

    Token(Token const&);
    Token(Type type, std::string  lexeme, Value literal, int line);

    [[nodiscard]] Type getType() const;
    [[nodiscard]] Value getLiteral() const;
    [[nodiscard]] std::string getLexeme() const;
    [[nodiscard]] int getLine() const;

    friend std::ostream& operator<<(std::ostream& out, Token const& token);

private:
    Type mType;
    Value mLiteral;
    std::string mLexeme;
    int mLine;
};

} // namespace Lox
