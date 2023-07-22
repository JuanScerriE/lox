
#include <iostream>

// lox
#include <common/AST.hpp>
#include <memory>

namespace Lox {

class ASTPrinter {
public:
    void printProgram(std::unique_ptr<Program>& program)
    {
        for (auto& stmt : program->stmts) {
            std::cout << print(stmt) << std::endl;
        }
    }

    std::string print(std::unique_ptr<Stmt>& stmt)
    {
        switch (stmt->type()) {
        case Stmt::PRINT:
            return "(print " + print(((PrintStmt*)stmt.get())->expr) + ")";
        case Stmt::EXPRESSION:
            return "(" + print(((ExprStmt*)stmt.get())->expr) + ")";
        }
    }

    std::string print(std::unique_ptr<Expr>& expr)
    {
        switch (expr->type()) {
        case Expr::GROUPING: {
            auto* ptr = (Grouping*)expr.get();
            return "(grouping " + print(ptr->expr) + ")";
        }
        case Expr::BINARY: {
            auto* ptr = (Binary*)expr.get();
            return "(" + ptr->oper.getLexeme() + print(ptr->left) + print(ptr->right) + ")";
        }
        case Expr::UNARY: {
            auto* ptr = (Unary*)expr.get();
            return "(" + ptr->oper.getLexeme() + print(ptr->expr) + ")";
        }
        case Expr::LITERAL: {
            return ((Literal*)expr.get())->value.toString();
        }
        }
    }
};

} // namespace Lox
