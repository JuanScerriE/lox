add_executable(lox
  Main.cpp
  Lox.cpp
  Scanner.cpp
  Token.cpp
  AstPrinter.cpp
)

target_compile_options(lox PRIVATE -Wall -Wextra -Wpedantic -Werror)
