#pragma once

// lox
#include "ObjectType.hpp"

// std
#include <string>
#include <variant>

namespace Lox {

struct Object {
    ObjectType type;

    std::variant<std::monostate, std::string, double> value;

    static Object createNil() {
        return {ObjectType::NIL, std::monostate{}};
    }

    static Object createString(std::string string) {
        return {ObjectType::STRING, string};
    }

    static Object createNumber(double number) {
        return {ObjectType::NUMBER, number};
    }

    std::string toString() const
    {
        switch (type) {
        case ObjectType::NIL:
            return "nil";
        case ObjectType::NUMBER:
            return std::to_string(std::get<double>(value));
        case ObjectType::STRING:
            return std::get<std::string>(value);
        default:
            return "Undefined Object Type";
        }
    }
};

} // namespace Lox
