//
// Created by delihiros on 2020/04/10.
//

#ifndef VMLISP_TOKEN_H
#define VMLISP_TOKEN_H

#include <string>
#include <sstream>
#include <iostream>


enum class TokenType {
    Keyword,
    Symbol,
    Integer,
    Double,
    String,
    Comment,
    LParen,
    RParen,
    LSquare,
    RSquare,
    LCurly,
    RCurly,
    LSharp,
    End,
    Unexpected
};

class Token {
    std::string s;
    TokenType tt;
public:
    Token();

    Token(std::string s, TokenType tt);

    TokenType get_tokentype();

    std::string get_string();

    friend std::ostream &operator<<(std::ostream &os, const Token &token);
};

#endif //VMLISP_TOKEN_H
