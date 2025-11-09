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

#include <cctype>
#include <iostream>
#include "lexer.h"

Lexer::Lexer(std::string text) : src(std::move(text)) {}

bool Lexer::startsWith(const std::string &s) const {
    return src.compare(pos, s.size(), s) == 0;
}

void Lexer::skipWhitespaceAndComments() {
    while (pos < src.size()) {
        char c = src[pos];
        if (isspace(c)) { if (c == '\n') line++; pos++; continue; }
        if (startsWith("//")) {
            while (pos < src.size() && src[pos] != '\n') pos++;
            continue;
        }
        break;
    }
}

Token Lexer::nextToken() {
    skipWhitespaceAndComments();
    if (pos >= src.size()) return Token(TokenKind::End);

    char c = src[pos];
    if (isalpha(c) || c == '_') {
        size_t start = pos;
        while (pos < src.size() && (isalnum(src[pos]) || src[pos]=='_')) pos++;
        std::string word = src.substr(start, pos - start);
        if (word == "let") return Token(TokenKind::Let, word);
        if (word == "print") return Token(TokenKind::Print, word);
        return Token(TokenKind::Ident, word);
    }
    if (isdigit(c)) {
        size_t start = pos;
        while (pos < src.size() && isdigit(src[pos])) pos++;
        std::string num = src.substr(start, pos - start);
        return Token(TokenKind::Int, num, std::stoll(num));
    }
    pos++;
    switch (c) {
        case '+': return Token(TokenKind::Plus, "+");
        case '-': return Token(TokenKind::Minus, "-");
        case '*': return Token(TokenKind::Mul, "*");
        case '/': return Token(TokenKind::Div, "/");
        case '=': return Token(TokenKind::Assign, "=");
        case '(': return Token(TokenKind::LParen, "(");
        case ')': return Token(TokenKind::RParen, ")");
        case ';': return Token(TokenKind::Semi, ";");
        default:
            std::cerr << "Unexpected character '" << c << "' at line " << line << "\n";
            exit(1);
    }
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (true) {
        Token t = nextToken();
        tokens.push_back(t);
        if (t.kind == TokenKind::End) break;
    }
    return tokens;
}
