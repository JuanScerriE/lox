// lox
#include <common/Value.hpp>

namespace Lox {

Value Value::createNil()
{
    return { Type::NIL, std::monostate {} };
}

Value Value::createString(std::string string)
{
    return { Type::STRING, string };
}

Value Value::createNumber(double number)
{
    return { Type::NUMBER, number };
}

std::string Value::toString() const
{
    switch (type) {
    case Type::NIL:
        return "nil";
    case Type::NUMBER:
        return std::to_string(std::get<double>(value));
    case Type::STRING:
        return std::get<std::string>(value);
    default:
        return "Undefined Value Type";
    }
}

} // namespace Lox
