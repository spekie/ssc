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

#include <vector>
#include <memory>
#include "token.h"
#include "ast.h"

#ifndef PARSER_HPP
#define PARSER_HPP

class Parser {
    std::vector<Token> tokens;
    size_t pos = 0;

    Token peek() const;
    Token consume();
    bool accept(TokenKind k);
    void expect(TokenKind k);
    int precedence(TokenKind k) const;

    std::unique_ptr<Expr> parsePrimary();
    std::unique_ptr<Expr> parseBinRHS(int prec, std::unique_ptr<Expr> lhs);
    std::unique_ptr<Expr> parseExpr();

public:
    explicit Parser(std::vector<Token> t);
    std::vector<std::unique_ptr<Stmt>> parseProgram();
};

#endif
