add_executable(lox
  Main.cpp
  runner/Runner.cpp
  parser/Parser.cpp
  scanner/Scanner.cpp
  common/Token.cpp
  printer/AstPrinter.cpp
)

target_compile_options(lox PRIVATE -Wall -Wextra -Wpedantic -Werror)

target_include_directories(lox PUBLIC .)
