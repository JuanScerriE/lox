// Lox
#include <common/Value.hpp>
#include <errors/RuntimeError.hpp>
#include <evaluator/Interpreter.hpp>

// std
#include <any>
#include <cassert>
#include <stdexcept>

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
        return Value::createBool(!isEqual(left, right));
    case Token::Type::EQUAL_EQUAL:
        return Value::createBool(isEqual(left, right));
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
        if (left.type == Value::NUMBER && right.type == Value::NUMBER) {
            return Value::createNumber(std::get<double>(left.data) + std::get<double>(right.data));
        }

        if (left.type == Value::STRING && right.type == Value::STRING) {
            return Value::createString(std::get<std::string>(left.data) + std::get<std::string>(right.data));
        }

        break;
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
        right.data = !isTruthy(right);
        break;
    default:
        assert(nullptr != "Unreachable");
    }

    return right;
}

bool Interpreter::isTruthy(Value& value) const
{
    if (value.type == Value::NIL) {
        return false;
    }

    if (value.type == Value::BOOL) {
        return std::get<bool>(value.data);
    }

    return true;
}

bool Interpreter::isEqual(Value& value1, Value& value2) const
{
    if (value1.type == Value::NIL && value2.type == Value::NIL) {
        return true;
    }

    if (value1.type == Value::NIL) {
        return false;
    }

    if (value2.type == Value::NIL) {
        return false;
    }

    if (value1.type == Value::NUMBER && value2.type == Value::NUMBER) {
        return std::get<bool>(value1.data) != std::get<bool>(value2.data);
    }

    if (value1.type == Value::STRING && value2.type == Value::STRING) {
        return std::get<std::string>(value1.data) != std::get<std::string>(value2.data);
    }

    return false;
}

void Interpreter::checkNumberOperand(Token& exprOperator, Value& operand) const
{
    if (operand.type == Value::NUMBER) {
        return;
    }

    throw RuntimeError(exprOperator, "Operand must be a number.");
}

} // namespace Lox
