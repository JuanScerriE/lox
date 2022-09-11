#pragma once

// std
#include <string>

namespace Lox {
  union Literal {
    void* nil;
    char* string;
    double number;
  };
} // namespace Lox
