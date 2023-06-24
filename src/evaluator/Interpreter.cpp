// Lox
#include "Interpreter.hpp"

#include "common/Value.hpp"

// std
#include <cassert>

namespace Lox {

Value Interpreter::eval(Expr const* expr)
{
    return std::any_cast<Value>(expr->accept(*this));
}

std::any Interpreter::visitLiteralExpr(Literal const* expr)
{
    return *expr->value;
}

std::any Interpreter::visitUnaryExpr(Unary const* expr)
{
    std::any right = eval(expr->right.get());

    switch (expr->oper->getType()) {
    case Token::Type::MINUS:
        return Value::createNumber(std::any_cast<double>(right));
    case Token::Type::BANG:
        return Value::createBool(!std::any_cast<bool>(right));
    default:
        assert(nullptr != "Unreachable");
    }

    return nullptr;
}

} // namespace Lox
