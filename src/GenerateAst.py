#!/usr/bin/python3  

import sys


def define_type(file, class_name, base_name, field_list):
    fields = field_list.split(", ")

    file.write(
"""  class {0} : {1}
  {{
  public:
    {0}
    (
""".format(class_name, base_name)
    )

    for i in range(len(fields)):
        field_arr = fields[i].split(" ")
        type = field_arr[0]
        name = field_arr[1]

        if i < len(fields) - 1:
            file.write(
"""      const {0}& {1},
""".format(type, name)
            )
        else:
            file.write(
"""      const {0}& {1}
""".format(type, name)
            )

    file.write(
"""    )
    :
"""
    )

    for i in range(len(fields)):
        name = fields[i].split(" ")[1]

        if i < len(fields) - 1:
            file.write(
"""    {0}({0}),
""".format(name)
            )
        else:
            file.write(
"""    {0}({0}) {{}}

""".format(name)
            )

    for i in range(len(fields)):
        field_arr = fields[i].split(" ")
        type = field_arr[0]
        name = field_arr[1]

        file.write(
"""    const {0}& {1};
""".format(type, name)
        )

    file.write(
"""  };

"""
    )


def define_ast(output_dir, base_name, types):
    path = output_dir + "/" + base_name + ".hpp"

    file = open(path, "w")

    file.write(
"""#pragma once

// std
#include <list>

// lox
#include "Object.hpp"
#include "Token.hpp"

namespace Lox
{{
  class {0}
  {{
  }};

""".format(base_name)
    )

    for type in types:
        type_arr = type.split(":")
        class_name = type_arr[0].strip()
        field_list = type_arr[1].strip()
        define_type(file, class_name, base_name, field_list)

    file.write(
"""} // namespace Lox"""
    )

    file.close()


def main():
    if len(sys.argv) != 2:
        print("usage: generate_ast <output directory>",
              file=sys.stderr)
        return 64

    output_dir = sys.argv[1]

    define_ast(output_dir, "Expr", [
        "Binary : Expr left, Token oper, Expr right",
        "Grouping : Expr expr",
        "Literal : Object value",
        "Unary : Token oper, Expr right"
    ])

    return 0


if __name__ == "__main__":
    sys.exit(main())
