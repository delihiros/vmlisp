//
// Created by delihiros on 2020/04/10.
//

#ifndef VMLISP_PARSER_H
#define VMLISP_PARSER_H

#include "lexer.h"
#include "token.h"
#include "ast.h"

class Parser {
    Lexer lexer;
    Token token;
public:

    Parser();

    explicit Parser(Lexer *lex);

    AST parse();

private:
    bool next_token();

    AST parse_integer();

    AST parse_double();
};

#endif //VMLISP_PARSER_H
