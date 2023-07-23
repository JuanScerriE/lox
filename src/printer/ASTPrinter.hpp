
#include <iostream>

// lox
#include <common/AST.hpp>
#include <memory>

namespace Lox {

class ASTPrinter : public ExprVisitor, public StmtVisitor {
public:
    void visitBinaryExpr(Binary const* expr) override {
        _str += "(" + expr->oper.getLexeme() + " ";
        stringify(*expr->left);
        _str += " ";
        stringify(*expr->right);
        _str += ")";
    }
    void visitUnaryExpr(Unary const* expr) override{
        _str += "(" + expr->oper.getLexeme() + " ";
        stringify(*expr->expr);
        _str += ")";
    }
    void visitLiteralExpr(Literal const* expr) override {
        _str += expr->value.toString();
    }
    void visitGroupingExpr(Grouping const* expr) override {
        _str += "(grouping ";
        stringify(*expr->expr);
        _str += ")";
    }

    void visitPrintStmt(PrintStmt const* stmt) override {
        _str += "(print ";
        stringify(*stmt->expr);
        _str += ")";
    }
    void visitExprStmt(ExprStmt const* stmt) override {
        stringify(*stmt->expr);
    }

    void print(std::unique_ptr<Program>& program)
    {
        for (auto& stmt : program->stmts) {
            stringify(*stmt);
            std::cout << _str << std::endl;
            _str.clear();
        }
    }

    void stringify(Stmt& stmt)
    {
        stmt.accept(this);

    }

    void stringify(Expr& expr)
    {
        expr.accept(this);
    }

    std::string _str;
};

} // namespace Lox
