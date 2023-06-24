// std
#include <sstream>
#include <string>

// lox
#include <printer/AstPrinter.hpp>

namespace Lox {

std::string AstPrinter::print(Expr const* expr)
{
    return std::any_cast<std::string>(expr->accept(*this));
}

std::any AstPrinter::visitBinaryExpr(Binary const* expr)
{
    return parenthesize(expr->oper->getLexeme(), expr->left.get(), expr->right.get());
}

std::any AstPrinter::visitGroupingExpr(Grouping const* expr)
{
    return parenthesize("group", expr->expr.get());
}

std::any AstPrinter::visitLiteralExpr(Literal const* expr)
{
    return expr->value->toString();
}

std::any AstPrinter::visitUnaryExpr(Unary const* expr)
{
    return parenthesize(expr->oper->getLexeme(), expr->right.get());
}

std::string AstPrinter::parenthesize(std::string const& name, Expr const* left, Expr const* right)
{
    std::ostringstream stream {};
    stream << "(" << name << " " << print(left) << " " << print(right) << ")";
    return stream.str();
}

std::string AstPrinter::parenthesize(std::string const& name, Expr const* expr)
{
    std::ostringstream stream {};
    stream << "(" << name << " " << print(expr) << ")";
    return stream.str();
}

} // namespace Lox
