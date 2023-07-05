// Lox
#include "Interpreter.hpp"

#include "common/Value.hpp"

// std
#include <any>
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

std::any Interpreter::visitGroupingExpr(Grouping const* expr)
{
    return eval(expr->expr.get());
}

std::any Interpreter::visitBinaryExpr(Binary const* expr)
{
    Value left = eval(expr->left.get());
    Value right = eval(expr->right.get());

    switch (expr->oper->getType()) {
    case Token::Type::BANG_EQUAL:
        return Value::createBool(std::get<bool>(left.data) != std::get<bool>(right.data));
    case Token::Type::EQUAL_EQUAL:
        return Value::createBool(std::get<bool>(left.data) == std::get<bool>(right.data));
    case Token::Type::GREATER:
        return Value::createBool(std::get<double>(left.data) > std::get<double>(right.data));
    case Token::Type::GREATER_EQUAL:
        return Value::createBool(std::get<double>(left.data) >= std::get<double>(right.data));
    case Token::Type::LESS:
        return Value::createBool(std::get<double>(left.data) < std::get<double>(right.data));
    case Token::Type::LESS_EQUAL:
        return Value::createBool(std::get<double>(left.data) <= std::get<double>(right.data));
    case Token::Type::MINUS:
        return Value::createNumber(std::get<double>(left.data) - std::get<double>(right.data));
    case Token::Type::PLUS:
        return Value::createNumber(std::get<double>(left.data) + std::get<double>(right.data));
    case Token::Type::SLASH:
        return Value::createNumber(std::get<double>(left.data) / std::get<double>(right.data));
    case Token::Type::STAR:
        return Value::createNumber(std::get<double>(left.data) * std::get<double>(right.data));
    default:
        assert(nullptr != "Unreachable");
    }

    return nullptr;
}

std::any Interpreter::visitUnaryExpr(Unary const* expr)
{
    Value right = eval(expr->right.get());

    switch (expr->oper->getType()) {
    case Token::Type::MINUS:
        right.data = -std::get<double>(right.data);
        break;
    case Token::Type::BANG:
        right.data = !std::get<bool>(right.data);
        break;
    default:
        assert(nullptr != "Unreachable");
    }

    return right;
}

} // namespace Lox
