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

    static Value createNil();
    static Value createString(std::string string);
    static Value createNumber(double number);

    std::string toString() const;
};

} // namespace Lox
