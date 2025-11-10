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

#include <vector>
#include <string>
#include "token.hpp"

#ifndef LEXER_HPP
#define LEXER_HPP

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
