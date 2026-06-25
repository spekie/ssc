#include <fstream>
#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"
#include "codegen.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Simple Syntax Compiler (SSC)" << "\n" << "Copyright (C) 2026 Spekie" << "\n" << "\n";
        std::cerr << "Usage: " << argv[0] << " <file>\n";
        return 1;
    }
    std::ifstream in(argv[1]);
    if (!in) {
        std::cout << "Simple Syntax Compiler (SSC)" << "\n" << "Copyright (C) 2026 Spekie" << "\n" << "\n";
        std::cerr << "Cannot open file." << "\n";
        return 1;
    }
    std::string src((std::istreambuf_iterator<char>(in)), {});

    Lexer lex(src);
    auto tokens = lex.tokenize();

    Parser parser(std::move(tokens));
    auto program = parser.parseProgram();

    CodeGen cg;
    std::string asmText = cg.generate(program);
    std::cout << asmText;
}
