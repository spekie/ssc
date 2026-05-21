#include <string>
#include <vector>
#include <unordered_map>
#include "ast.hpp"

#ifndef CODEGEN_HPP
#define CODEGEN_HPP

class CodeGen {
    std::vector<std::string> out;
    std::unordered_map<std::string,int> vars;
    int nextOffset = 0;

    void emit(const std::string &s);
    void genExpr(Expr *e);
    void genStmt(Stmt *s);

public:
    std::string generate(const std::vector<std::unique_ptr<Stmt>> &program);
};

#endif
