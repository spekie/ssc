/*
 * This file is part of SSC.
 *
 * SSC is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * SSC is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SSC.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <fstream>
#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"
#include "codegen.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
		std::cout << "Simple Syntax Compiler (SSC)" << "\n" << "Copyright (C) 2025 Spekie" << "\n" << "\n";
        std::cerr << "Usage: " << argv[0] << " <file>\n";
        return 1;
    }
    std::ifstream in(argv[1]);
    if (!in) {
		std::cout << "Simple Syntax Compiler (SSC)" << "\n" << "Copyright (C) 2025 Spekie" << "\n" << "\n";
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
