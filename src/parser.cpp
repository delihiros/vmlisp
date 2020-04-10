//
// Created by delihiros on 2020/04/10.
//

#include "parser.h"
#include "ast.h"

Parser::Parser(Lexer *lex) {
    lexer = *lex;
}

AST Parser::parse() {
    next_token();
    switch (token.get_token_type()) {
        case TokenType::Integer:
            return parse_integer();
        case TokenType::Double:
            return parse_double();
        default:
            return AST();
    }
}

AST Parser::parse_integer() {
    return AST(DataType::Integer, std::stoi(token.get_string()));
}

AST Parser::parse_double() {
    return AST(DataType::Double, std::stod(token.get_string()));
}

bool Parser::next_token() {
    token = lexer.next();
    return token.get_token_type() != TokenType::End;
}
