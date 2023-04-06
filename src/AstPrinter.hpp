// lox
#include "Expr.hpp"
#include <string>

namespace Lox {

class AstPrinter : public Visitor<std::string>
{
public:
    std::string print(const Expr* expr);

    void visitBinaryExpr(const Binary* expr) override;
    void visitGroupingExpr(const Grouping* expr) override;
    void visitLiteralExpr(const Literal* expr) override;
    void visitUnaryExpr(const Unary* expr) override;

private:
    std::string parenthesize(const std::string& name, const Expr* left, const Expr* right);
    std::string parenthesize(const std::string& name, const Expr* expr);
};

} // namespace Lox
