#pragma once

#include <common/Expr.hpp>
#include <common/Value.hpp>

namespace Lox {

class Interpreter : public Visitor {
public:
    void interpret(Expr const* expr);

private:
    std::any visitLiteralExpr(Literal const* expr) override;
    std::any visitGroupingExpr(Grouping const* expr) override;
    std::any visitBinaryExpr(Binary const* expr) override;
    std::any visitUnaryExpr(Unary const* expr) override;

    Value eval(Expr const* expr);

    bool isTruthy(Value& value) const;
    bool isEqual(Value& value1, Value& value2) const;
    void checkNumberOperand(Token& exprOperator, Value& operand) const;
    void checkNumberOperands(Token& exprOperator, Value& left, Value& right) const;
};

} // namespace Lox
