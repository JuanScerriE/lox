add_executable(lox
  AstPrinter.cpp
  Lox.cpp
  Main.cpp
  Parser.cpp
  Scanner.cpp
  Token.cpp
)

target_compile_options(lox PRIVATE -Wall -Wextra -Wpedantic -Werror)
