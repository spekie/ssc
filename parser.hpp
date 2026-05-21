#include <vector>
#include <memory>
#include "token.hpp"
#include "ast.hpp"

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
