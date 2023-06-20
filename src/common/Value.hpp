#pragma once

// std
#include <string>
#include <variant>

namespace Lox {

struct Value {
    enum Type {
        NIL,
        STRING,
        NUMBER,
    };

    Type type;

    std::variant<std::monostate, std::string, double> value;

    static Value createNil()
    {
        return { Type::NIL, std::monostate {} };
    }

    static Value createString(std::string string)
    {
        return { Type::STRING, string };
    }

    static Value createNumber(double number)
    {
        return { Type::NUMBER, number };
    }

    std::string toString() const
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
};

} // namespace Lox
