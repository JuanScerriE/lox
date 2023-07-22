#pragma once

// std
#include <any>
#include <memory>
#include <utility>
#include <algorithm>

// lox
#include <common/Token.hpp>

namespace Lox {

class Expr {
public:
    enum Type {
        GROUPING,
        BINARY,
        UNARY,
        LITERAL
    };
    [[nodiscard]] virtual Type type() const = 0;
    virtual ~Expr() = default;
};

class Grouping : public Expr {
public:
    explicit Grouping(std::unique_ptr<Expr> expr)
        : expr(std::move(expr))
    {
    }
    [[nodiscard]] Type type() const override { return GROUPING; }
    std::unique_ptr<Expr> expr;
};

class Binary : public Expr {
public:
    Binary(
        std::unique_ptr<Expr> left,
        const Token& oper,
        std::unique_ptr<Expr> right)
        : left(std::move(left))
        , oper(oper)
        , right(std::move(right))
    {
    }
    [[nodiscard]] Type type() const override { return BINARY; }
    std::unique_ptr<Expr> left;
    Token oper;
    std::unique_ptr<Expr> right;
};

class Unary : public Expr {
public:
    Unary(
        const Token& oper,
        std::unique_ptr<Expr> expr)
        : oper(oper)
        , expr(std::move(expr))
    {
    }
    [[nodiscard]] Type type() const override { return UNARY; }
    Token oper;
    std::unique_ptr<Expr> expr;
};

class Literal : public Expr {
public:
    explicit Literal(Value value)
        : value(std::move(value))
    {
    }
    [[nodiscard]] Type type() const override { return LITERAL; }
    Value value;
};

// class ExprVisitor {
// public:
//     virtual std::any visitBinaryExpr(Binary const* expr) = 0;
//     virtual std::any visitGroupingExpr(Grouping const* expr) = 0;
//     virtual std::any visitLiteralExpr(Literal const* expr) = 0;
//     virtual std::any visitUnaryExpr(Unary const* expr) = 0;
// };

class Stmt {
public:
    enum Type {
        PRINT,
        EXPRESSION,
    };
    [[nodiscard]] virtual Type type() const = 0;
    virtual ~Stmt() = default;
};

class PrintStmt : public Stmt {
public:
    explicit PrintStmt(std::unique_ptr<Expr> expr)
        : expr(std::move(expr))
    {
    }
    [[nodiscard]] Type type() const override { return PRINT; }
    std::unique_ptr<Expr> expr;
};

class ExprStmt : public Stmt {
public:
    explicit ExprStmt(std::unique_ptr<Expr> expr)
        : expr(std::move(expr))
    {
    }
    [[nodiscard]] Type type() const override { return EXPRESSION; }
    std::unique_ptr<Expr> expr;
};

// class StmtVisitor {
// public:
//     virtual std::any visitPrintStmt(PrintStmt const* expr) = 0;
//     virtual std::any visitExprStmt(ExprStmt const* expr) = 0;
// };

class Program {
public:
    explicit Program(std::vector<std::unique_ptr<Stmt>> stmts)
        : stmts(std::move(stmts))
    {
    }
    std::vector<std::unique_ptr<Stmt>> stmts;
};

} // namespace Lox
