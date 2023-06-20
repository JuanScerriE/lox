#pragma once

// std
#include <memory>

// lox
#include <common/Token.hpp>
#include <common/Value.hpp>

namespace Lox {

class Expr;

class Binary;
class Grouping;
class Literal;
class Unary;

class VisitorBase {
public:
    virtual void visitBinaryExpr(Binary const* expr) = 0;
    virtual void visitGroupingExpr(Grouping const* expr) = 0;
    virtual void visitLiteralExpr(Literal const* expr) = 0;
    virtual void visitUnaryExpr(Unary const* expr) = 0;
};

template<typename R>
class Visitor : public VisitorBase {
public:
    R result() const
    {
        return _result;
    }

protected:
    R _result;
};

class Expr {
public:
    enum ExprType {
        LITERAL,
        UNARY,
        BINARY,
        GROUPING,
    };

    template<typename R>
    R accept(Visitor<R>& visitor) const
    {
        do_accept(visitor);
        return visitor.result();
    }

    virtual void do_accept(VisitorBase& visitor) const = 0;

    virtual ~Expr() {};
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

    void do_accept(VisitorBase& visitor) const override
    {
        visitor.visitBinaryExpr(this);
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

    void do_accept(VisitorBase& visitor) const override
    {
        visitor.visitGroupingExpr(this);
    }

    std::unique_ptr<Expr> expr;
};

class Literal : public Expr {
public:
    Literal(
        std::unique_ptr<Value> object)
        : object(std::move(object))
    {
    }

    void do_accept(VisitorBase& visitor) const override
    {
        visitor.visitLiteralExpr(this);
    }

    std::unique_ptr<Value> object;
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

    void do_accept(VisitorBase& visitor) const override
    {
        visitor.visitUnaryExpr(this);
    }

    std::unique_ptr<Token> oper;
    std::unique_ptr<Expr> right;
};

} // namespace Lox
