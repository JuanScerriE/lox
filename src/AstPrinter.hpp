#pragma once

// std
#include <iostream>
#include <sstream>

// lox
#include "Expr.hpp"

namespace Lox
{
  template<typename B, typename T>
  inline bool instanceOf(const T&) {
    return std::is_base_of<B, T>::value;
  }

  class AstPrinter
  {
    std::string parenthesize(const std::string& name, const Expr& exprs...) {
      va_list args;
      va_start(args, exprs);

      std::stringstream s;
      s << "(";

      for (auto arg : args) {

      }

      s << ")";

      va_end(args);
    }

    std::string print(const Expr& expr)
    {
      if (instanceOf<Binary>(expr)) {
        return parenthesize();
      }

      if (instanceOf<Grouping>(expr)) {
        return parenthesize();
      }

      if (instanceOf<Literal>(expr)) {
        Literal* _ptr = (Literal*)&expr;

        if (_ptr->value.type == TokenType::NIL) {
          return "nil";
        }

        if (_ptr->value.type == TokenType::NUMBER) {
          std::ostringstream s;
          s << _ptr->value.type;
          return s.str();
        }

        if (_ptr->value.type == TokenType::STRING) {
          return _ptr->value.string;
        }
      }

      if (instanceOf<Unary>(expr)) {
        return parenthesize();
      }
    }
  };
} // namespace Lox