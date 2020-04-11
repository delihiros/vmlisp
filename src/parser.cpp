//
// Created by delihiros on 2020/04/10.
//

#include <deque>
#include "parser.h"
#include "ast.h"
#include "token.h"

Parser::Parser(Lexer *lex) {
    lexer = *lex;
}

AST Parser::parse_program() {
    std::vector<AST> expr;
    next_token();
    while (token.get_tokentype() != TokenType::End){
        expr.push_back(parse_expr());
    }
    return AST(DataType::Program, expr);
}

AST Parser::parse_expr() {
    switch (token.get_tokentype()) {
        case TokenType::Integer:
            return parse_integer();
        case TokenType::Double:
            return parse_double();
        case TokenType::Symbol:
            return parse_symbol();
        case TokenType::Keyword:
            return parse_keyword();
        case TokenType::String:
            return parse_string();
        case TokenType::LParen:
            return parse_list();
        case TokenType::LSquare:
            return parse_vector();
        case TokenType::LCurly:
            return parse_hashmap();
        case TokenType::LSharp:
            return parse_set();
        default:
            return AST();
    }
}

AST Parser::parse_integer() {
    auto ast = AST(DataType::Integer, std::stoi(token.get_string()));
    next_token();
    return ast;
}

AST Parser::parse_double() {
    auto ast = AST(DataType::Double, std::stod(token.get_string()));
    next_token();
    return ast;
}

AST Parser::parse_symbol() {
    auto ast = AST(DataType::Symbol, token.get_string());
    next_token();
    return ast;
}

AST Parser::parse_keyword() {
    auto ast = AST(DataType::Keyword, token.get_string());
    next_token();
    return ast;
}

AST Parser::parse_string() {
    auto ast = AST(DataType::String, token.get_string());
    next_token();
    return ast;
}

AST Parser::parse_list() {
    std::vector<AST> nodes;
    next_token();
    while (token.get_tokentype() != TokenType::RParen) {
        auto node = parse_expr();
        nodes.push_back(node);
    }
    next_token();
    return AST(DataType::List, nodes);
}

AST Parser::parse_vector() {
    std::vector<AST> nodes;
    next_token();
    while (token.get_tokentype() != TokenType::RSquare) {
        auto node = parse_expr();
        nodes.push_back(node);
    }
    next_token();
    return AST(DataType::Vector, nodes);
}

AST Parser::parse_set() {
    std::vector<AST> nodes;
    next_token();
    while (token.get_tokentype() != TokenType::RCurly) {
        auto node = parse_expr();
        nodes.push_back(node);
    }
    next_token();
    return AST(DataType::Set, nodes);
}

AST Parser::parse_hashmap() {
    std::vector<AST> nodes;
    next_token();
    while (token.get_tokentype() != TokenType::RCurly) {
        auto node = parse_expr();
        nodes.push_back(node);
    }
    next_token();
    return AST(DataType::HashMap, nodes);
}

bool Parser::next_token() {
    if (TokenType::End == token.get_tokentype())
        return false;
    token = lexer.next();
    return token.get_tokentype() != TokenType::End;
}

