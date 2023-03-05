// std
#include <sstream>
#include <string>

// lox
#include "AstPrinter.hpp"

namespace Lox {

namespace AstPrinter {


std::string AstPrinter::print(Expr::Expr& expr)
{
    return expr.accept(*this);
}


void AstPrinter::visitBinaryExpr(Expr::Binary& expr) {
    _result = parenthesize(expr.oper.getLexeme(), expr.left, expr.right);
}

void AstPrinter::visitGroupingExpr(Expr::Grouping& expr) {
    _result = parenthesize("group", expr.expr);
}

void AstPrinter::visitLiteralExpr(Expr::Literal& expr) {
    _result = expr.value.toString();
}

void AstPrinter::visitUnaryExpr(Expr::Unary& expr) {
    _result = parenthesize(expr.oper.getLexeme(), expr.right);
}

std::string AstPrinter::parenthesize(const std::string& name, Expr::Expr& left, Expr::Expr& right)
{
    std::ostringstream stream {};
    stream << "(" << name << " " << print(left) << " " << print(right) << ")";
    return stream.str();
}

std::string AstPrinter::parenthesize(const std::string& name, Expr::Expr& expr)
{
    std::ostringstream stream {};
    stream << "(" << name << " " << print(expr) << ")";
    return stream.str();
}

} // namespace AstPrinter

} // namespace Lox
