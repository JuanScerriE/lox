// std
#include <iostream>
#include <memory>

// lox
#include <runner/Runner.hpp>

int main(int argc, char** argv)
{
    if (argc > 2) {
        std::cout << "lox: usage lox [script]" << std::endl;

        return 64;
    } else if (argc == 2) {
        return Lox::Runner::runFile(argv[1]);
    } else {
        return Lox::Runner::runPrompt();
    }
}
