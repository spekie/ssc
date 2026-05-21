#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>
#include <string>
#include "token.hpp"

class Lexer {
    std::string src;
    size_t pos = 0;
    int line = 1;

    void skipWhitespaceAndComments();
    bool startsWith(const std::string &s) const;

public:
    explicit Lexer(std::string text);
    Token nextToken();
    std::vector<Token> tokenize();
};

#endif
