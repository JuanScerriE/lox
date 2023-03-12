// lox
#include "Expr.hpp"
#include <string>

namespace Lox {

namespace AstPrinter {


class AstPrinter : public Expr::Visitor<std::string>
{
public:
    std::string print(const Expr::Expr* expr);

    void visitBinaryExpr(const Expr::Binary* expr) override;
    void visitGroupingExpr(const Expr::Grouping* expr) override;
    void visitLiteralExpr(const Expr::Literal* expr) override;
    void visitUnaryExpr(const Expr::Unary* expr) override;

private:
    std::string parenthesize(const std::string& name, const Expr::Expr* left, const Expr::Expr* right);
    std::string parenthesize(const std::string& name, const Expr::Expr* expr);
};

} // namespace AstPrinter

} // namespace Lox
