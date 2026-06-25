#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <string>
#include <vector>

struct Expr {
    virtual ~Expr() = default;
};
struct NumberExpr : Expr {
    long long val;
    explicit NumberExpr(long long v) : val(v) {}
};
struct VarExpr : Expr {
    std::string name;
    explicit VarExpr(std::string n) : name(std::move(n)) {}
};
struct BinaryExpr : Expr {
    char op;
    std::unique_ptr<Expr> lhs, rhs;
    BinaryExpr(char o, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(o), lhs(std::move(l)), rhs(std::move(r)) {}
};

struct Stmt { virtual ~Stmt() = default; };
struct LetStmt : Stmt {
    std::string name;
    std::unique_ptr<Expr> expr;
    LetStmt(std::string n, std::unique_ptr<Expr> e)
        : name(std::move(n)), expr(std::move(e)) {}
};
struct PrintStmt : Stmt {
    std::unique_ptr<Expr> expr;
    explicit PrintStmt(std::unique_ptr<Expr> e) : expr(std::move(e)) {}
};

#endif
