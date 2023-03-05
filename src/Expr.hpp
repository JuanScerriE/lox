#pragma once

// std
#include <list>

// lox
#include "Object.hpp"
#include "Token.hpp"

namespace Lox
{

namespace Expr
{
  class Expr;
  class Binary;
  class Grouping;
  class Literal;
  class Unary;

  class VisitorBase
  {
  public:
    virtual void visitBinaryExpr(Binary& expr) = 0;
    virtual void visitGroupingExpr(Grouping& expr) = 0;
    virtual void visitLiteralExpr(Literal& expr) = 0;
    virtual void visitUnaryExpr(Unary& expr) = 0;
  };

  template<typename R>
  class Visitor : public VisitorBase 
  {
  public:
      R result() const {
          return _result;
      }
  
  protected:
      R _result;
  };

  class Expr
  {
  public:

    template<typename R>
    R accept(Visitor<R>& visitor) {
      do_accept(visitor);
      return visitor.result();
    }

    virtual void do_accept(VisitorBase& visitor) = 0;
  };

  class Binary : Expr
  {
  public:
    Binary
    (
      Expr& left,
      Token& oper,
      Expr& right
    )
    :
    left(left),
    oper(oper),
    right(right) {}

    void do_accept(VisitorBase& visitor) override {
      visitor.visitBinaryExpr(*this);
    }
    
    Expr& left;
    Token& oper;
    Expr& right;
  };

  class Grouping : Expr
  {
  public:
    Grouping
    (
      Expr& expr
    )
    :
    expr(expr) {}

    void do_accept(VisitorBase& visitor) override {
      visitor.visitGroupingExpr(*this);
    }
    
    Expr& expr;
  };

  class Literal : Expr
  {
  public:
    Literal
    (
      Object& value
    )
    :
    value(value) {}

    void do_accept(VisitorBase& visitor) override {
      visitor.visitLiteralExpr(*this);
    }
    
    Object& value;
  };

  class Unary : Expr
  {
  public:
    Unary
    (
      Token& oper,
      Expr& right
    )
    :
    oper(oper),
    right(right) {}

    void do_accept(VisitorBase& visitor) override {
      visitor.visitUnaryExpr(*this);
    }
    
    Token& oper;
    Expr& right;
  };


} // namespace Expr

} // namespace Lox
