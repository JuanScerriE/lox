#pragma once

// lox
#include "ObjectType.hpp"

// std
#include <string>

namespace Lox {
struct Object {
    ObjectType type;

    union {
        // TODO: Remove char* and use std::string
        char* string;
        double number;
    };

    static Object createNil() {
        Object obj;
        obj.type = ObjectType::NIL;
        return obj;
    }

    static Object createString(char* string) {
        Object obj;
        obj.type = ObjectType::STRING;
        obj.string = string;
        return obj;
    }

    static Object createNumber(double number) {
        Object obj;
        obj.type = ObjectType::NUMBER;
        obj.number = number;
        return obj;
    }

    std::string toString() const
    {
        switch (type) {
        case ObjectType::NIL:
            return "nil";
        case ObjectType::NUMBER:
            return std::to_string(number);
        case ObjectType::STRING:
            return std::string {string};
        default:
            return "Undefined Object Type";
        }
    }
};
} // namespace Lox
