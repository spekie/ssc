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
#include <iostream>
#include "parser.hpp"

Parser::Parser(std::vector<Token> t) : tokens(std::move(t)) {}

Token Parser::peek() const {
    return pos < tokens.size() ? tokens[pos] : Token(TokenKind::End);
}
Token Parser::consume() { return pos < tokens.size() ? tokens[pos++] : Token(TokenKind::End); }
bool Parser::accept(TokenKind k) { if (peek().kind == k) { consume(); return true; } return false; }
void Parser::expect(TokenKind k) {
    if (peek().kind != k) {
        std::cerr << "Expected token kind but got " << peek().text << "\n";
        exit(1);
    }
    consume();
}

int Parser::precedence(TokenKind k) const {
    if (k == TokenKind::Mul || k == TokenKind::Div) return 20;
    if (k == TokenKind::Plus || k == TokenKind::Minus) return 10;
    return -1;
}

std::unique_ptr<Expr> Parser::parsePrimary() {
    Token t = peek();
    if (t.kind == TokenKind::Int) { consume(); return std::make_unique<NumberExpr>(t.val); }
    if (t.kind == TokenKind::Ident) { consume(); return std::make_unique<VarExpr>(t.text); }
    if (t.kind == TokenKind::LParen) {
        consume();
        auto e = parseExpr();
        expect(TokenKind::RParen);
        return e;
    }
    std::cerr << "Unexpected token " << t.text << "\n";
    exit(1);
}

std::unique_ptr<Expr> Parser::parseBinRHS(int exprPrec, std::unique_ptr<Expr> lhs) {
    while (true) {
        TokenKind op = peek().kind;
        int tokPrec = precedence(op);
        if (tokPrec < exprPrec) return lhs;
        consume();
        auto rhs = parsePrimary();
        int nextPrec = precedence(peek().kind);
        if (tokPrec < nextPrec)
            rhs = parseBinRHS(tokPrec + 1, std::move(rhs));

        char opch = (op==TokenKind::Plus)?'+':(op==TokenKind::Minus)?'-':(op==TokenKind::Mul)?'*':'/';
        lhs = std::make_unique<BinaryExpr>(opch, std::move(lhs), std::move(rhs));
    }
}

std::unique_ptr<Expr> Parser::parseExpr() {
    auto lhs = parsePrimary();
    return parseBinRHS(0, std::move(lhs));
}

std::vector<std::unique_ptr<Stmt>> Parser::parseProgram() {
    std::vector<std::unique_ptr<Stmt>> program;
    while (peek().kind != TokenKind::End) {
        if (accept(TokenKind::Let)) {
            Token id = peek(); expect(TokenKind::Ident);
            expect(TokenKind::Assign);
            auto e = parseExpr();
            expect(TokenKind::Semi);
            program.push_back(std::make_unique<LetStmt>(id.text, std::move(e)));
        } else if (accept(TokenKind::Print)) {
            auto e = parseExpr();
            expect(TokenKind::Semi);
            program.push_back(std::make_unique<PrintStmt>(std::move(e)));
        } else {
            std::cerr << "Unexpected token " << peek().text << "\n";
            exit(1);
        }
    }
    return program;
}
