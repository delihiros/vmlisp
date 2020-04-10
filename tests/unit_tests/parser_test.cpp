#include "gtest/gtest.h"
#include "lexer.h"
#include "parser.h"



TEST(Parser, integer) {
    auto lexer = new Lexer("123");
    auto parser = new Parser(lexer);
    AST ast = parser->parse();
    EXPECT_EQ(ast.get_datatype(), DataType::Integer);
    EXPECT_EQ(ast.get_int(), 123);

    lexer = new Lexer("-123");
    parser = new Parser(lexer);
    ast = parser->parse();
    EXPECT_EQ(ast.get_datatype(), DataType::Integer);
    EXPECT_EQ(ast.get_int(), -123);
}

TEST(Parser, double) {
    auto lexer = new Lexer("123.456");
    auto parser = new Parser(lexer);
    AST ast = parser->parse();
    EXPECT_EQ(ast.get_datatype(), DataType::Double);
    EXPECT_EQ(ast.get_double(), 123.456);

    lexer = new Lexer("-123.456");
    parser = new Parser(lexer);
    ast = parser->parse();
    EXPECT_EQ(ast.get_datatype(), DataType::Double);
    EXPECT_EQ(ast.get_double(), -123.456);
}

/*
TEST(Parser, symbol) {
    auto lexer = new Lexer("abc");
    auto token = lexer->next();
    EXPECT_EQ(token.get_string(), "abc");
    EXPECT_EQ(token.get_token_type(), TokenType::Symbol);

    lexer = new Lexer("Abc123");
    token = lexer->next();
    EXPECT_EQ(token.get_string(), "Abc123");
    EXPECT_EQ(token.get_token_type(), TokenType::Symbol);

    lexer = new Lexer("Abc123_12-abc");
    token = lexer->next();
    EXPECT_EQ(token.get_string(), "Abc123_12-abc");
    EXPECT_EQ(token.get_token_type(), TokenType::Symbol);
}

TEST(Parser, keyword) {
    auto lexer = new Lexer(":abc");
    auto token = lexer->next();
    EXPECT_EQ(token.get_string(), ":abc");
    EXPECT_EQ(token.get_token_type(), TokenType::Keyword);

    lexer = new Lexer(":abc123");
    token = lexer->next();
    EXPECT_EQ(token.get_string(), ":abc123");
    EXPECT_EQ(token.get_token_type(), TokenType::Keyword);
}

TEST(Parser, symbol_special_cases) {
    auto lexer = new Lexer("-");
    auto token = lexer->next();
    EXPECT_EQ(token.get_string(), "-");
    EXPECT_EQ(token.get_token_type(), TokenType::Symbol);

    lexer = new Lexer("--");
    token = lexer->next();
    EXPECT_EQ(token.get_string(), "--");
    EXPECT_EQ(token.get_token_type(), TokenType::Symbol);

    lexer = new Lexer("<=");
    token = lexer->next();
    EXPECT_EQ(token.get_string(), "<=");
    EXPECT_EQ(token.get_token_type(), TokenType::Symbol);
}

TEST(Parser, comment) {
    auto lexer = new Lexer("// hello, world");
    auto token = lexer->next();
    EXPECT_EQ(token.get_string(), " hello, world");
    EXPECT_EQ(token.get_token_type(), TokenType::Comment);

    lexer = new Lexer("// hello, world\n");
    token = lexer->next();
    EXPECT_EQ(token.get_string(), " hello, world");
    EXPECT_EQ(token.get_token_type(), TokenType::Comment);
}
*/
