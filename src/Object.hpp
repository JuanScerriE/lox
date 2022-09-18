#pragma once

// std
#include <string>

namespace Lox {
  union Object {
    void* nil;
    char* string;
    double number;
  };
} // namespace Lox
