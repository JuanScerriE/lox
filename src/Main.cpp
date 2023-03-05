// std
#include <iostream>

// lox
#include "Lox.hpp"
#include "Expr.hpp"
#include "Object.hpp"
#include "AstPrinter.hpp"

int main(int argc, char** argv)
{

    auto obj1 = new Lox::Object();
    obj1->type = Lox::ObjectType::NUMBER;
    obj1->number = 123;

    auto obj2 = new Lox::Object();
    obj2->type = Lox::ObjectType::NUMBER;
    obj2->number = 45.67;

    Lox::Expr::Binary expression = Lox::Expr::Binary(
            Lox::Expr::Unary(
                Lox::Token(Lox::TokenType::MINUS, "-", {.type = Lox::ObjectType::NIL}, 1),
                Lox::Expr::Literal(*obj1)
                ),
            Lox::Token(Lox::TokenType::STAR, "*", {.type = Lox::ObjectType::NIL}, 1),
            Lox::Expr::Grouping(
                Lox::Expr::Literal(*obj2)
                )
            );

    Lox::AstPrinter::AstPrinter printer;

    std::cout << printer.print(*expression) << std::endl;

    if (argc > 2) {
        std::cout << "lox: usage lox [script]" << std::endl;

        return 64;
    } else if (argc == 2) {
        return Lox::Runner::runFile(argv[1]);
    } else {
        return Lox::Runner::runPrompt();
    }
}
