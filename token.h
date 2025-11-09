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

#ifndef TOKEN_HPP
#define TOKEN_HPP

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
