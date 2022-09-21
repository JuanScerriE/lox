// std
#include <sstream>
#include <string>

// lox
#include "AstPrinter.hpp"

namespace Lox {

namespace AstPrinter {

std::string print(Expr const* expr)
{
    if (expr->type == ExprType::BINARY) {
        Binary const* castExpr = (Binary*)expr;
        return parenthesize(castExpr->mOper->getLexeme(), castExpr->mLeft, castExpr->mRight);
    } else if (expr->type == ExprType::GROUPING) {
        Grouping const* castExpr = (Grouping*)expr;
        return parenthesize("group", castExpr->mExpr);
    } else if (expr->type == ExprType::LITERAL) {
        Literal const* castExpr = (Literal*)expr;
        return castExpr->mValue->toString();
    } else if (expr->type == ExprType::UNARY) {
        Unary const* castExpr = (Unary*)expr;
        return parenthesize(castExpr->mOper->getLexeme(), castExpr->mRight);
    }
}

std::string parenthesize(std::string const& name, Expr const* left, Expr const* right)
{
    std::ostringstream stream {};
    stream << "(" << name << " " << print(left) << " " << print(right) << ")";
    return stream.str();
}

std::string parenthesize(std::string const& name, Expr const* expr)
{
    std::ostringstream stream {};
    stream << "(" << name << " " << print(expr) << ")";
    return stream.str();
}

}

} // namespace Lox
