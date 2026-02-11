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
