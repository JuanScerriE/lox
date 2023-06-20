#pragma once

// std
#include <string>

// lox
#include "../common/Expr.hpp"

namespace Lox {

class AstPrinter : public Visitor<std::string> {
public:
    std::string print(Expr const* expr);

    void visitBinaryExpr(Binary const* expr) override;
    void visitGroupingExpr(Grouping const* expr) override;
    void visitLiteralExpr(Literal const* expr) override;
    void visitUnaryExpr(Unary const* expr) override;

private:
    std::string parenthesize(std::string const& name, Expr const* left, Expr const* right);
    std::string parenthesize(std::string const& name, Expr const* expr);
};

} // namespace Lox
