#pragma once

// std
#include <string>

// lox
#include "Scanner.hpp"

namespace Lox {
class Runner {
public:
  static int runFile(char *path);
  static int runPrompt();
  static void error(int line, const std::string &message);
  static void error(Token token, const std::string &message);
  static void report(int line, const std::string &where,
                     const std::string &message);

private:
  static void run(const std::string &source);

  static bool mHadError;
};

} // namespace Lox
