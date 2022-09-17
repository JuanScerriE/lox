def defineType(file, baseName, className, fields):
    file.write(
            """
                    class {} : {} {
                    public:
                    };    
            """.format(className, baseName)
            )


def defineAst(outputDir, baseName, types):
    path = outputDir + "/" + baseName + ".hpp"

    file = open(path, "w")

    file.write(
            """
            #pragma once

            // std
            #include <list>

            namespace Lox {
                class {} {
                public:
            """.format(baseName);                        
            )

    for type in types:
        type_arr = type.split(":", 1)
        className = type_arr[0].strip() 
        fields = type_arr[1].strip()
        defineType(file, className, baseName, fields)


    file.write(
            """
                };    
            } // namespace Lox
            """
            )

    file.close()


defineAst(outputDir, "Expr", [
    "Binary : Expr left, Token opertator, Expr right",
    "Grouping : Expr expression",
    "Literal : Object value",
    "Unary : Token operator, Expr right"
    ])
