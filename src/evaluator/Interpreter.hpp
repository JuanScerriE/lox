#pragma once

#include <common/AST.hpp>
#include <common/Value.hpp>

namespace Lox {

class Interpreter : ExprVisitor, StmtVisitor {
public:
  void interpret(Expr const *expr);

private:
  void visitExprStmt(ExprStmt const *expr) override;
  void visitPrintStmt(PrintStmt const *expr) override;

  void visitLiteralExpr(Literal const *expr) override;
  void visitGroupingExpr(Grouping const *expr) override;
  void visitBinaryExpr(Binary const *expr) override;
  void visitUnaryExpr(Unary const *expr) override;

  void eval(Expr *expr);

  bool isTruthy(Value &value) const;
  bool isEqual(Value &value1, Value &value2) const;
  void checkNumberOperand(Token &exprOperator, Value &operand) const;
  void checkNumberOperands(Token &exprOperator, Value &left,
                           Value &right) const;

  Value mExprResult;
};

} // namespace Lox
