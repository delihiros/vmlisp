//
// Created by delihiros on 2020/04/10.
//

#ifndef VMLISP_LEXER_H
#define VMLISP_LEXER_H

#include <utility>
#include <vector>
#include <set>
#include "token.h"

class Lexer {
    std::string s;
    decltype(s)::iterator it;

public:

    Lexer();

    explicit Lexer(std::string s);

    Token next();

private:
    char peek();

    char peek_forward();

    char forward();

    Token keyword();

    Token symbol();

    Token special_symbol();

    Token numeral();

    Token string();

    Token comment();

    Token end();

    static bool is_space(char c);

    static bool is_alpha(char c);

    static bool is_s_alpha(char c);

    static bool is_b_alpha(char c);

    static bool is_digit(char c);

    static bool is_special(char c);

};

#endif //VMLISP_LEXER_H
