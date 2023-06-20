// std
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <list>
#include <memory>

// lox
#include <parser/Parser.hpp>
#include <printer/AstPrinter.hpp>
#include <runner/Runner.hpp>
#include <scanner/Scanner.hpp>

namespace Lox {

bool Runner::mHadError = false;

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

void Runner::run(std::string const& source)
{
    Scanner scanner(source);

    std::vector<Token> tokens = scanner.scanTokens();

    for (Token const& token : tokens) {
        std::cout << token << std::endl;
    }

    Parser parser(tokens);

    std::unique_ptr<Expr> expression = parser.parse();

    if (mHadError)
        return;

    AstPrinter printer;

    std::cout << printer.print(expression.get()) << std::endl;
}

int Runner::runFile(char* path)
{
    FILE* fp = fopen(path, "r");

    if (!fp) {
        perror("lox:");
        return EXIT_FAILURE;
    }

    if (fseek(fp, 0, SEEK_END) == -1) {
        perror("lox");
        fclose(fp);
        return EXIT_FAILURE;
    }

    long size = ftell(fp);

    if (size == -1) {
        perror("lox");
        fclose(fp);
        return EXIT_FAILURE;
    }

    if (fseek(fp, 0, SEEK_SET) == -1) {
        perror("lox");
        fclose(fp);
        return EXIT_FAILURE;
    }

    char* file = (char*)malloc((size + 1) * sizeof(char));
    file[size] = 0;
    fread(file, sizeof(char), size, fp);

    if (ferror(fp)) {
        std::cerr << "lox: error reading file " << path << std::endl;
        perror("lox");
        fclose(fp);
        return EXIT_FAILURE;
    }

    fclose(fp);
    std::string source(file);
    free(file);
    run(source);

    if (mHadError) {
        return 65;
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
