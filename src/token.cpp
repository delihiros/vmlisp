//
// Created by delihiros on 2020/04/10.
//

#include "token.h"

Token::Token(std::string s, TokenType tt)
        : s(std::move(s)), tt(tt) {}

TokenType Token::get_token_type() {
    return tt;
}

std::string Token::get_string() {
    return s;
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << "Token{ " << token.s << ", " << int(token.tt) << " }";
    return os;
}

Token::Token() {}
