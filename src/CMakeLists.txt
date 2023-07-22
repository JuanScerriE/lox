add_library(lox_lib STATIC
    runner/Runner.cpp
    evaluator/Interpreter.cpp
    parser/Parser.cpp
    scanner/Scanner.cpp
    common/Token.cpp
    # printer/AstPrinter.cpp
)

target_compile_options(lox_lib PRIVATE)
target_include_directories(lox_lib PUBLIC .)

#---------------------------------

add_executable(lox
    Main.cpp
)

target_compile_options(lox PRIVATE)
target_link_libraries(lox PRIVATE lox_lib)

#---------------------------------

# enable_testing()
#
# add_executable(lox_tests
#     tests/Tests.cpp
# )
#
# target_compile_options(lox_lib PRIVATE)
# target_link_libraries(lox_tests PRIVATE
#     lox_lib
#     GTest::gtest_main
# )
#
# include(GoogleTest)
# gtest_discover_tests(lox_tests)
