// std
#include <sstream>
#include <string>

// lox
#include "AstPrinter.hpp"

namespace Lox {

namespace AstPrinter {

std::string AstPrinter::print(Expr::Expr const* expr)
{
    return expr->accept(*this);
}

void AstPrinter::visitBinaryExpr(Expr::Binary const* expr)
{
    _result = parenthesize(expr->oper->getLexeme(), expr->left.get(), expr->right.get());
}

void AstPrinter::visitGroupingExpr(Expr::Grouping const* expr)
{
    _result = parenthesize("group", expr->expr.get());
}

void AstPrinter::visitLiteralExpr(Expr::Literal const* expr)
{
    _result = expr->value->toString();
}

void AstPrinter::visitUnaryExpr(Expr::Unary const* expr)
{
    _result = parenthesize(expr->oper->getLexeme(), expr->right.get());
}

std::string AstPrinter::parenthesize(std::string const& name, Expr::Expr const* left, Expr::Expr const* right)
{
    std::ostringstream stream {};
    stream << "(" << name << " " << print(left) << " " << print(right) << ")";
    return stream.str();
}

std::string AstPrinter::parenthesize(std::string const& name, Expr::Expr const* expr)
{
    std::ostringstream stream {};
    stream << "(" << name << " " << print(expr) << ")";
    return stream.str();
}

} // namespace AstPrinter

} // namespace Lox
