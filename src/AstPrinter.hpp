// lox
#include "Expr.hpp"
#include <string>

namespace Lox {

namespace AstPrinter {


class AstPrinter : public Expr::Visitor<std::string>
{
public:
    std::string print(Expr::Expr& expr);
    void visitBinaryExpr(Expr::Binary& expr) override;
    void visitGroupingExpr(Expr::Grouping& expr) override;
    void visitLiteralExpr(Expr::Literal& expr) override;
    void visitUnaryExpr(Expr::Unary& expr) override;

private:
    std::string parenthesize(const std::string& name, Expr::Expr& left, Expr::Expr& right);
    std::string parenthesize(const std::string& name, Expr::Expr& expr);
};

} // namespace AstPrinter

} // namespace Lox
