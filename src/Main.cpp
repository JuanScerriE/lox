// std
#include <iostream>
#include <memory>

// lox
#include "runner/Runner.hpp"

namespace Lox {

int main(int argc, char** argv)
{
    if (argc > 2) {
        std::cout << "lox: usage lox [script]" << std::endl;

        return 64;
    } else if (argc == 2) {
        return Runner::runFile(argv[1]);
    } else {
        return Runner::runPrompt();
    }
}

} // namespace Lox
