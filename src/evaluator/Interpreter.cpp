// Lox
#include <common/Value.hpp>
#include <errors/RuntimeError.hpp>
#include <evaluator/Interpreter.hpp>

// std
#include <any>
#include <cassert>
#include <iostream>
#include <stdexcept>

namespace Lox {

void Interpreter::interpret(Expr const *expr) {
  try {
    Value value = eval(expr);

    std::cout << "Eval: " << value.toString() << std::endl;
  } catch (RuntimeError &e) {
    std::cout << e.what() << std::endl;
  }
}

void Interpreter::visitLiteralExpr(Literal const *expr) {
  mExprResult = expr->value;
}

void Interpreter::visitGroupingExpr(Grouping const *expr) {
  eval(expr->expr.get());
}

void Interpreter::visitBinaryExpr(Binary const *expr) {
  eval(expr->left.get());
  Value left = std::move(mExprResult);
  eval(expr->right.get());
  Value right = std::move(mExprResult);

  switch (expr->oper->getType()) {
  case Token::Type::BANG_EQUAL:
    mExprResult = Value::createBool(!isEqual(left, right));
  case Token::Type::EQUAL_EQUAL:
    mExprResult = Value::createBool(isEqual(left, right));
  case Token::Type::GREATER:
    checkNumberOperands(expr->oper, left, right);
    mExprResult = Value::createBool(std::get<double>(left.data) >
                             std::get<double>(right.data));
  case Token::Type::GREATER_EQUAL:
    checkNumberOperands(expr->oper, left, right);
    mExprResult = Value::createBool(std::get<double>(left.data) >=
                             std::get<double>(right.data));
  case Token::Type::LESS:
    checkNumberOperands(expr->oper, left, right);
    mExprResult = Value::createBool(std::get<double>(left.data) <
                             std::get<double>(right.data));
  case Token::Type::LESS_EQUAL:
    checkNumberOperands(expr->oper, left, right);
    mExprResult = Value::createBool(std::get<double>(left.data) <=
                             std::get<double>(right.data));
  case Token::Type::MINUS:
    checkNumberOperands(expr->oper, left, right);
    mExprResult = Value::createNumber(std::get<double>(left.data) -
                               std::get<double>(right.data));
  case Token::Type::PLUS:
    if (left.type == Value::NUMBER && right.type == Value::NUMBER) {
      mExprResult = Value::createNumber(std::get<double>(left.data) +
                                 std::get<double>(right.data));
    }

    if (left.type == Value::STRING && right.type == Value::STRING) {
      mExprResult = Value::createString(std::get<std::string>(left.data) +
                                 std::get<std::string>(right.data));
    }

    throw RuntimeError(*expr->oper.get(),
                       "Operands must be two numbers or two strings.");
  case Token::Type::SLASH:
    checkNumberOperands(*expr->oper.get(), left, right);
    return Value::createNumber(std::get<double>(left.data) /
                               std::get<double>(right.data));
  case Token::Type::STAR:
    checkNumberOperands(*expr->oper.get(), left, right);
    return Value::createNumber(std::get<double>(left.data) *
                               std::get<double>(right.data));
  default:
    assert(nullptr != "Unreachable");
  }

  return nullptr;
}

void Interpreter::visitUnaryExpr(Unary const *expr) {
  Value right = eval(expr->right.get());

  switch (expr->oper->getType()) {
  case Token::Type::MINUS:
    checkNumberOperand(*expr->oper.get(), right);
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

void Interpreter::eval(Expr *expr) {
  expr->accept(this);
}

bool Interpreter::isTruthy(Value &value) const {
  if (value.type == Value::NIL) {
    return false;
  }

  if (value.type == Value::BOOL) {
    return std::get<bool>(value.data);
  }

  return true;
}

bool Interpreter::isEqual(Value &value1, Value &value2) const {
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
    return std::get<std::string>(value1.data) !=
           std::get<std::string>(value2.data);
  }

  return false;
}

void Interpreter::checkNumberOperand(Token &exprOperator,
                                     Value &operand) const {
  if (operand.type == Value::NUMBER) {
    return;
  }

  throw RuntimeError(exprOperator, "Operand must be a number.");
}

void Interpreter::checkNumberOperands(Token &exprOperator, Value &left,
                                      Value &right) const {
  if (left.type == Value::NUMBER && right.type == Value::NUMBER) {
    return;
  }

  throw RuntimeError(exprOperator, "Operands must be a numbers.");
}

} // namespace Lox
