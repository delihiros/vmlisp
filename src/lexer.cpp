//
// Created by delihiros on 2020/04/10.
//

#include "lexer.h"

Lexer::Lexer(std::string s) {
    s = s;
    it = s.begin();
}

Token Lexer::next() {
    while (is_space(peek())) forward();

    if (peek() == '\0') {
        return end();
    } else if (is_digit(peek())) {
        return numeral();
    } else if (peek() == ':') {
        return keyword();
    } else if (is_alpha(peek())) {
        return symbol();
    } else if (peek() == '#' && peek_forward() == '{') {
        forward();
        forward();
        return Token("#{", TokenType::LSharp);
    } else if (peek() == '(') {
        forward();
        return Token("(", TokenType::LParen);
    } else if (peek() == ')') {
        forward();
        return Token(")", TokenType::RParen);
    } else if (peek() == '{') {
        forward();
        return Token("{", TokenType::LCurly);
    } else if (peek() == '}') {
        forward();
        return Token("}", TokenType::RCurly);
    } else if (peek() == '[') {
        forward();
        return Token("[", TokenType::LSquare);
    } else if (peek() == ']') {
        forward();
        return Token("]", TokenType::RSquare);
    } else if (peek() == '"') {
        return string();
    } else if (is_special(peek())) {
        if (peek() == '-' && is_digit(peek_forward())) {
            return numeral();
        } else if (peek() == '/' && peek_forward() == '/') {
            return comment();
        }
        return special_symbol();
    }
    return Token("", TokenType::Unexpected);
}

bool Lexer::is_space(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == ',';
}

bool Lexer::is_alpha(char c) {
    return is_s_alpha(c) || is_b_alpha(c);
}

bool Lexer::is_s_alpha(char c) {
    return 'a' <= c && c <= 'z';
}

bool Lexer::is_b_alpha(char c) {
    return 'A' <= c && c <= 'Z';
}

bool Lexer::is_digit(char c) {
    return '0' <= c && c <= '9';
}

bool Lexer::is_special(char c) {
    const std::set<char> special_symbols = {
            '!', '#', '$', '%', '&', '=', '-', '^', '~', '|', '+', '*', '/', '?', '<', '>'};
    return special_symbols.count(c) != 0;
}

Token Lexer::keyword() {
    std::string s = ":";
    forward(); // skipping the first colon.
    while (is_alpha(peek()) || is_digit(peek()) || peek() == '-' || peek() == '_') {
        s += peek();
        forward();
    }
    return Token(s, TokenType::Keyword);
}

Token Lexer::symbol() {
    std::string s;
    while (is_alpha(peek()) || is_digit(peek()) || peek() == '-' || peek() == '_') {
        s += peek();
        forward();
    }
    return Token(s, TokenType::Symbol);
}

Token Lexer::special_symbol() {
    std::string s;
    while (is_special(peek())) {
        s += peek();
        forward();
    }
    return Token(s, TokenType::Symbol);
}

Token Lexer::numeral() {
    std::string s;
    if (peek() == '-') {
        s += '-';
        forward();
    }
    while (is_digit(peek())) {
        s += peek();
        forward();
    }
    // TODO: need to track back when it's not a valid numeral e.x. 123.456abc
    if (peek() == '.') {
        s += peek();
        forward();
        while (is_digit(peek())) {
            s += peek();
            forward();
        }
        return Token(s, TokenType::Double);
    }
    return Token(s, TokenType::Integer);
}

Token Lexer::string() {
    std::string s;
    forward();
    while (peek() != '"' && peek() != '\0') {
        if (peek() == '\\') {
            s += "\\";
            forward();
        }
        s += peek();
        forward();
    }
    return Token(s, TokenType::String);
}

Token Lexer::comment() {
    forward();
    forward(); // These are to skip "//"

    std::string s;
    while (peek() != '\n' && peek() != '\0') {
        s += peek();
        forward();
    }
    return Token(s, TokenType::Comment);
}

char Lexer::peek() {
    return *it;
}

char Lexer::peek_forward() {
    return *(it + 1);
}

char Lexer::forward() {
    return *it++;
}

Token Lexer::end() {
    return Token("", TokenType::End);
}

Lexer::Lexer() {}
