#pragma once

// std
#include <string>

namespace Lox {
  struct Object {
    TokenType type;

    union
    {
      void *nil;
      char *string;
      double number;
    };
  };
} // namespace Lox
