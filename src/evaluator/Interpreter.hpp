#pragma once

#include <common/Expr.hpp>
#include <common/Value.hpp>

namespace Lox {

class Interpreter : public Visitor {
public:
    Value eval(Expr const* expr);

private:
    std::any visitLiteralExpr(Literal const* expr) override;
    std::any visitGroupingExpr(Grouping const* expr) override;
    std::any visitBinaryExpr(Binary const* expr) override;
    std::any visitUnaryExpr(Unary const* expr) override;

    bool isTruthy(Value& value) const;
    bool isEqual(Value& value1, Value& value2) const;
    void checkNumberOperand(Token& exprOperator, Value& operand) const;
};

} // namespace Lox
