// std
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <list>

// lox
#include "Lox.hpp"

namespace Lox {
  bool Runner::mHadError = false;

  void Runner::report(int line, const std::string& where, const std::string& message) {
    std::cerr << "[line " << line << "] Error" << where << ": " << message;  
    mHadError = true;
  }

  void Runner::error(int line, const std::string& message) {
    report(line, "", message);
  }

  void Runner::run(const std::string& source) {
    Scanner scanner(source);
    std::list<Token> tokens = scanner.scanTokens();     

    for (Token token : tokens) {
      std::cout << token << std::endl;
    }
  }

  int Runner::runFile(char* path) {
    FILE *fp = fopen(path, "r");

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

  int Runner::runPrompt() {
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
