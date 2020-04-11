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

    AST parse_expr();
    
    AST parse_program();

private:
    bool next_token();

    AST parse_integer();

    AST parse_double();

    AST parse_symbol();

    AST parse_keyword();

    AST parse_string();

    AST parse_list();

    AST parse_vector();

    AST parse_set();

    AST parse_hashmap();
};

#endif //VMLISP_PARSER_H
