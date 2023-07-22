#pragma once

// std
#include <string>

// lox
#include <common/AST.hpp>

namespace Lox {

class AstPrinter : public ExprVisitor, public StmtVisitor {
public:
    std::string print(Expr const* expr);

    std::any visitBinaryExpr(Binary const* expr) override;
    std::any visitGroupingExpr(Grouping const* expr) override;
    std::any visitLiteralExpr(Literal const* expr) override;
    std::any visitUnaryExpr(Unary const* expr) override;

private:
    std::string parenthesize(std::string const& name, Expr const* left, Expr const* right);
    std::string parenthesize(std::string const& name, Expr const* expr);
};

} // namespace Lox
