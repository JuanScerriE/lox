#pragma once

// lox
#include "ObjectType.hpp"

// std
#include <string>

namespace Lox {
struct Object {
    ObjectType type;

    union {
        char* string;
        double number;
    };

    std::string toString() const
    {
        switch (type) {
        case ObjectType::NIL:
            return "nil";
        case ObjectType::NUMBER:
            return std::to_string(number);
        case ObjectType::STRING:
            return std::string {string};
        }
    }
};
} // namespace Lox
