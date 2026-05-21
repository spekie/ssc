#include <sstream>
#include <iostream>
#include "codegen.hpp"

void CodeGen::emit(const std::string &s) { out.push_back(s); }

void CodeGen::genExpr(Expr *e) {
    if (auto n = dynamic_cast<NumberExpr*>(e)) {
        emit("    movq $" + std::to_string(n->val) + ", %rax");
        emit("    pushq %rax");
        return;
    }
    if (auto v = dynamic_cast<VarExpr*>(e)) {
        int off = vars[v->name];
        emit("    movq " + std::to_string(off) + "(%rbp), %rax");
        emit("    pushq %rax");
        return;
    }
    if (auto b = dynamic_cast<BinaryExpr*>(e)) {
        genExpr(b->lhs.get());
        genExpr(b->rhs.get());
        emit("    popq %rdx");
        emit("    popq %rax");
        switch (b->op) {
            case '+': emit("    addq %rdx, %rax"); break;
            case '-': emit("    subq %rdx, %rax"); break;
            case '*': emit("    imulq %rdx, %rax"); break;
            case '/': emit("    cqto"); emit("    idivq %rdx"); break;
        }
        emit("    pushq %rax");
    }
}

void CodeGen::genStmt(Stmt *s) {
    if (auto l = dynamic_cast<LetStmt*>(s)) {
        if (!vars.count(l->name)) { nextOffset += 8; vars[l->name] = -nextOffset; }
        genExpr(l->expr.get());
        emit("    popq %rax");
        emit("    movq %rax, " + std::to_string(vars[l->name]) + "(%rbp)");
    } else if (auto p = dynamic_cast<PrintStmt*>(s)) {
        genExpr(p->expr.get());
        emit("    popq %rsi");
        emit("    leaq .Lfmt(%rip), %rdi");
        emit("    movl $0, %eax");
        emit("    call printf@PLT");
    }
}

std::string CodeGen::generate(const std::vector<std::unique_ptr<Stmt>> &program) {
    for (auto &s : program) genStmt(s.get());
    int frame = ((nextOffset + 15) / 16) * 16;
    std::vector<std::string> prologue = {
        "    .text",
        "    .globl main",
        "main:",
        "    pushq %rbp",
        "    movq %rsp, %rbp",
        "    subq $" + std::to_string(frame) + ", %rsp"
    };
    std::vector<std::string> epilogue = {
        "    movl $0, %eax",
        "    leave",
        "    ret",
        "    .section .rodata",
        ".Lfmt:",
        "    .string \"%lld\\n\""
    };
    std::ostringstream ss;
    for (auto &l : prologue) ss << l << "\n";
    for (auto &l : out) ss << l << "\n";
    for (auto &l : epilogue) ss << l << "\n";
    return ss.str();
}
