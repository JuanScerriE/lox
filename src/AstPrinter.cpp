// std
#include <sstream>
#include <string>

// lox
#include "AstPrinter.hpp"

namespace Lox {

namespace AstPrinter {


std::string AstPrinter::print(const Expr::Expr* expr)
{
    return expr->accept(*this);
}


void AstPrinter::visitBinaryExpr(const Expr::Binary* expr) {
    _result = parenthesize(expr->oper->getLexeme(), expr->left.get(), expr->right.get());
}

void AstPrinter::visitGroupingExpr(const Expr::Grouping* expr) {
    _result = parenthesize("group", expr->expr.get());
}

void AstPrinter::visitLiteralExpr(const Expr::Literal* expr) {
    _result = expr->value->toString();
}

void AstPrinter::visitUnaryExpr(const Expr::Unary* expr) {
    _result = parenthesize(expr->oper->getLexeme(), expr->right.get());
}

std::string AstPrinter::parenthesize(const std::string& name, const Expr::Expr* left, const Expr::Expr* right)
{
    std::ostringstream stream {};
    stream << "(" << name << " " << print(left) << " " << print(right) << ")";
    return stream.str();
}

std::string AstPrinter::parenthesize(const std::string& name, const Expr::Expr* expr)
{
    std::ostringstream stream {};
    stream << "(" << name << " " << print(expr) << ")";
    return stream.str();
}

} // namespace AstPrinter

} // namespace Lox
