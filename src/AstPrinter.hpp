// lox
#include "Expr.hpp"

namespace Lox {

namespace AstPrinter {

std::string print(Expr const* expr);
std::string parenthesize(std::string const& name, Expr const* left, Expr const* right);
std::string parenthesize(std::string const& name, Expr const* expr);

}

}
