#pragma once

// std
#include <any>
#include <memory>

// lox
#include <common/Token.hpp>
#include <common/Expr.hpp>
#include <common/Value.hpp>

namespace Lox {

class Stmt;

class Print;

class Visitor {
public:
    virtual std::any visitPrintStmt(Print const* expr) = 0;
    virtual std::any visitExprStmt(Expr const* expr) = 0;
};

class Stmt {
public:
    enum Type {
        PRINT,
        EXPRESSION,
    };

    virtual std::any accept(Visitor& visitor) const = 0;

    virtual ~Stmt() {};
};

class Print : public Stmt {
public:
    Literal(
        std::unique_ptr<Value> value)
        : value(std::move(value))
    {
    }

    std::any accept(Visitor& visitor) const override
    {
        return visitor.visitLiteralExpr(this);
    }

    std::unique_ptr<Value> value;
};

class Unary : public Expr {
public:
    Unary(
        std::unique_ptr<Token> oper,
        std::unique_ptr<Expr> right)
        : oper(std::move(oper))
        , right(std::move(right))
    {
    }

    std::any accept(Visitor& visitor) const override
    {
        return visitor.visitUnaryExpr(this);
    }

    std::unique_ptr<Token> oper;
    std::unique_ptr<Expr> right;
};

class Binary : public Expr {
public:
    Binary(
        std::unique_ptr<Expr> left,
        std::unique_ptr<Token> oper,
        std::unique_ptr<Expr> right)
        : left(std::move(left))
        , oper(std::move(oper))
        , right(std::move(right))
    {
    }

    std::any accept(Visitor& visitor) const override
    {
        return visitor.visitBinaryExpr(this);
    }

    std::unique_ptr<Expr> left;
    std::unique_ptr<Token> oper;
    std::unique_ptr<Expr> right;
};

class Grouping : public Expr {
public:
    Grouping(
        std::unique_ptr<Expr> expr)
        : expr(std::move(expr))
    {
    }

    std::any accept(Visitor& visitor) const override
    {
        return visitor.visitGroupingExpr(this);
    }

    std::unique_ptr<Expr> expr;
};

} // namespace Lox
