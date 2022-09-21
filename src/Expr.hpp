#pragma once

// std
#include <list>

// lox
#include "Object.hpp"
#include "Token.hpp"

namespace Lox
{
  class Expr
  {
  };

  class Binary : Expr
  {
  public:
    Binary
    (
      const Expr& left,
      const Token& oper,
      const Expr& right
    )
    :
    left(left),
    oper(oper),
    right(right) {}

    const Expr& left;
    const Token& oper;
    const Expr& right;
  };

  class Grouping : Expr
  {
  public:
    Grouping
    (
      const Expr& expr
    )
    :
    expr(expr) {}

    const Expr& expr;
  };

  class Literal : Expr
  {
  public:
    Literal
    (
      const Object& value
    )
    :
    value(value) {}

    const Object& value;
  };

  class Unary : Expr
  {
  public:
    Unary
    (
      const Token& oper,
      const Expr& right
    )
    :
    oper(oper),
    right(right) {}

    const Token& oper;
    const Expr& right;
  };

} // namespace Lox