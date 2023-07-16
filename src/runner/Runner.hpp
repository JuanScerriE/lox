#pragma once

// std
#include <string>

// lox
#include <common/Token.hpp>
#include <evaluator/Interpreter.hpp>
#include <errors/RuntimeError.hpp>

namespace Lox {

class Runner {
public:
    int runFile(std::string& path);
    int runPrompt();

    void error(int line, std::string const& message);
    void error(Token token, std::string const& message);
    void runtimeError(RuntimeError& error);
    void report(int line, std::string const& where,
        std::string const& message);

private:
    void run(std::string const& source);

    bool mHadError = false;
    bool mHadRuntimeError = false;
    Interpreter mInterpreter;
};

} // namespace Lox
