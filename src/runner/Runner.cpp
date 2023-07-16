// std
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <memory>

// lox
#include <evaluator/Interpreter.hpp>
#include <parser/Parser.hpp>
#include <printer/AstPrinter.hpp>
#include <runner/Runner.hpp>
#include <errors/RuntimeError.hpp>
#include <scanner/Scanner.hpp>

namespace Lox {

void Runner::report(int line, std::string const& where,
    std::string const& message)
{
    std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;

    mHadError = true;
}

void Runner::error(int line, std::string const& message)
{
    report(line, "", message);
}

void Runner::error(Token token, std::string const& message)
{
    if (token.getType() == Token::Type::END_OF_FILE) {
        report(token.getLine(), " at end", message);
    } else {
        report(token.getLine(), " at '" + token.getLexeme() + "'", message);
    }
}

void Runner::runtimeError(RuntimeError& error) {
    std::cerr << error.what() << "\n[line " << error.getToken().getLine() << "]" << std::endl;
    mHadRuntimeError = true;
}

void Runner::run(std::string const& source)
{
    // TODO: add scanning exceptions
    Scanner scanner(source);

    std::vector<Token> tokens = scanner.scanTokens();

    for (Token const& token : tokens) {
        std::cout << token << std::endl;
    }

    // TODO: add parsing exceptions
    Parser parser(tokens);

    std::unique_ptr<Expr> expression = parser.parse();

    if (mHadError)
        return;

    AstPrinter printer;

    std::cout << printer.print(expression.get()) << std::endl;

    mInterpreter.interpret(expression.get());
}

std::string readFile(std::string_view path) {
    constexpr auto read_size = std::size_t(4096);

    auto file = std::ifstream(path);

    if (!file) {
        throw std::ios_base::failure("file does not exist");
    }

    auto out = std::string();

    auto buf = std::string(read_size, '\0');

    while (file.read(&buf[0], read_size)) {
        out.append(buf, 0, file.gcount());
    }

    out.append(buf, 0, file.gcount());

    return out;
}

int Runner::runFile(std::string& path)
{
    std::ifstream file(path);

    // make sure the file is opened correcntly
    if (!file) {
        std::cerr << "lox: " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }

    // TODO: figure out when this fails and handle everything
    // properly

    // get the length of the file
    file.seekg(0, file.end);
    auto length = file.tellg();
    file.seekg(0, file.beg);

    // load the source file into a string
    std::string source(length, '\0');
    file.read(source.data(), length);

    // close file
    file.close();

    // run the source file
    run(source);

    if (mHadError) {
        return 65;
    } else if(mHadRuntimeError) {
        return 70;
    } else {
        return 0;
    }
}

int Runner::runPrompt()
{
    std::string line;

    for (;;) {
        std::cout << "> ";
        std::getline(std::cin, line);

        if (line.empty()) {
            break;
        }

        run(line);
        mHadError = false;
    }

    return 0;
}

} // namespace Lox
