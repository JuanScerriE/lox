enable_testing()

add_library(lox_lib STATIC
    runner/Runner.cpp
    parser/Parser.cpp
    scanner/Scanner.cpp
    common/Token.cpp
    printer/AstPrinter.cpp
)

target_compile_options(lox_lib PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_include_directories(lox_lib PUBLIC .)

add_executable(lox
    Main.cpp
)

target_compile_options(lox PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(lox PRIVATE lox_lib)

add_executable(lox_tests
    tests/Tests.cpp
)

target_compile_options(lox_lib PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(lox_tests PRIVATE
    lox_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lox_tests)
