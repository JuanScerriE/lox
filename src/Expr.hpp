#pragma once

// std
#include <list>

// lox
#include "ExprType.hpp"
#include "Object.hpp"
#include "Token.hpp"

namespace Lox {
class Expr {
public:
  ExprType type;
};

class Binary : public Expr {
public:
    Binary(
        Expr* left,
        Token* oper,
        Expr* right)
        : mLeft(left)
        , mOper(oper)
        , mRight(right)
    {
        type = ExprType::BINARY;
    }

    Expr* mLeft;
    Token* mOper;
    Expr* mRight;
};

class Grouping : public Expr {
public:
    Grouping(
        Expr* expr)
        : mExpr(expr)
    {
        type = ExprType::GROUPING;
    }

    Expr* mExpr;
};

class Literal : public Expr {
public:
    Literal(
        Object* value)
        : mValue(value)
    {
        type = ExprType::LITERAL;
    }

    Object* mValue;
};

class Unary : public Expr {
public:
    Unary(
        Token* oper,
        Expr* right)
        : mOper(oper)
        , mRight(right)
    {
        type = ExprType::UNARY;
    }

    Token* mOper;
    Expr* mRight;
};

} // namespace Lox
