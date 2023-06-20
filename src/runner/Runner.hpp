#pragma once

// std
#include <string>

// lox
#include <common/Token.hpp>

namespace Lox {

class Runner {
public:
    static int runFile(char* path);
    static int runPrompt();
    static void error(int line, std::string const& message);
    static void error(Token token, std::string const& message);
    static void report(int line, std::string const& where,
        std::string const& message);

private:
    static void run(std::string const& source);

    static bool mHadError;
};

} // namespace Lox
