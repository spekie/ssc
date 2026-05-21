#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenKind {
    End,
    Int,
    Ident,
    Let,
    Print,
    Plus, Minus, Mul, Div,
    Assign,
    LParen, RParen,
    Semi
};

struct Token {
    TokenKind kind;
    std::string text;
    long long val = 0;
    Token(TokenKind k=TokenKind::End, std::string t="", long long v=0)
        : kind(k), text(std::move(t)), val(v) {}
};

#endif
