#pragma once

#include "Expr.hpp"
#include "Object.hpp"

namespace Lox {

class Interpreter : public Visitor<Object> {

public:
    void visitLiteralExpr(Literal const* value) override;
    void visitGroupingExpr(Grouping const* value) override;
    void visitBinaryExpr(Binary const* value) override;
    void visitUnaryExpr(Unary const* value) override;
};

} // namespace Lox
