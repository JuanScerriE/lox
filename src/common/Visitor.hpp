#pragma once

// std
#include <any>
#include <memory>

class Visitor {
public:
    // Stmt
    virtual std::any visitPrintStmt(PrintStmt const* stms) = 0;
    virtual std::any visitExprStmt(ExprStmt const* stmt) = 0;

    // Expr
    virtual std::any visitBinaryExpr(Binary const* expr) = 0;
    virtual std::any visitGroupingExpr(Grouping const* expr) = 0;
    virtual std::any visitLiteralExpr(Literal const* expr) = 0;
    virtual std::any visitUnaryExpr(Unary const* expr) = 0;

};
