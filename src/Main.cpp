// std
#include <iostream>
#include <memory>

// lox
#include "Lox.hpp"
#include "Expr.hpp"
#include "Object.hpp"
#include "AstPrinter.hpp"

int main(int argc, char** argv)
{

    auto obj1 = std::make_unique<Lox::Object>();
    obj1->type = Lox::ObjectType::NUMBER;
    obj1->number = 123;

    auto obj2 = std::make_unique<Lox::Object>(); 
    obj2->type = Lox::ObjectType::NUMBER;
    obj2->number = 45.67;

    auto expression = std::make_unique<Lox::Expr::Binary>(
            std::make_unique<Lox::Expr::Unary>(
                std::make_unique<Lox::Token>(Lox::TokenType::MINUS, "-", Lox::Object::createNil(), 1),
                std::make_unique<Lox::Expr::Literal>(std::move(obj1))
            ),
            std::make_unique<Lox::Token>(
                Lox::TokenType::STAR, "*", Lox::Object::createNil(), 1
            ),
            std::make_unique<Lox::Expr::Grouping>(
                    std::make_unique<Lox::Expr::Literal>(std::move(obj2))
                )
            );

    Lox::AstPrinter::AstPrinter printer;

    std::cout << printer.print(expression.get()) << std::endl;

    if (argc > 2) {
        std::cout << "lox: usage lox [script]" << std::endl;

        return 64;
    } else if (argc == 2) {
        return Lox::Runner::runFile(argv[1]);
    } else {
        return Lox::Runner::runPrompt();
    }
}
