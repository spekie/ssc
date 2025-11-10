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

#include <memory>
#include <string>
#include <vector>

#ifndef AST_HPP
#define AST_HPP

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
