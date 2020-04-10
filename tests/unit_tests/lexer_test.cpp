#include "gtest/gtest.h"
#include "lexer.h"

TEST(Lexer, integer) {
    auto lexer = new Lexer("123");
    auto token = lexer->next();
    EXPECT_EQ(token.get_string(), "123");
    EXPECT_EQ(token.get_token_type(), TokenType::Integer);

    lexer = new Lexer("123 345");
    lexer->next();
    token = lexer->next();
    EXPECT_EQ(token.get_string(), "345");
    EXPECT_EQ(token.get_token_type(), TokenType::Integer);

    lexer = new Lexer("-123");
    token = lexer->next();
    EXPECT_EQ(token.get_string(), "-123");
    EXPECT_EQ(token.get_token_type(), TokenType::Integer);
}

TEST(Lexer, double) {
    auto lexer = new Lexer("123.456");
    auto token = lexer->next();
    EXPECT_EQ(token.get_string(), "123.456");
    EXPECT_EQ(token.get_token_type(), TokenType::Double);

    lexer = new Lexer("123.456abc");
    token = lexer->next();
    EXPECT_EQ(token.get_string(), "123.456");
    EXPECT_EQ(token.get_token_type(), TokenType::Double);

    lexer = new Lexer("-123.456abc");
    token = lexer->next();
    EXPECT_EQ(token.get_string(), "-123.456");
    EXPECT_EQ(token.get_token_type(), TokenType::Double);
}

TEST(Lexer, symbol) {
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

TEST(Lexer, keyword) {
    auto lexer = new Lexer(":abc");
    auto token = lexer->next();
    EXPECT_EQ(token.get_string(), ":abc");
    EXPECT_EQ(token.get_token_type(), TokenType::Keyword);

    lexer = new Lexer(":abc123");
    token = lexer->next();
    EXPECT_EQ(token.get_string(), ":abc123");
    EXPECT_EQ(token.get_token_type(), TokenType::Keyword);
}

TEST(Lexer, symbol_special_cases) {
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

TEST(Lexer, comment) {
    auto lexer = new Lexer("// hello, world");
    auto token = lexer->next();
    EXPECT_EQ(token.get_string(), " hello, world");
    EXPECT_EQ(token.get_token_type(), TokenType::Comment);

    lexer = new Lexer("// hello, world\n");
    token = lexer->next();
    EXPECT_EQ(token.get_string(), " hello, world");
    EXPECT_EQ(token.get_token_type(), TokenType::Comment);
}

TEST(Lexer, string) {
    auto lexer = new Lexer("\"hello, world\"");
    auto token = lexer->next();
    EXPECT_EQ(token.get_string(), "hello, world");
    EXPECT_EQ(token.get_token_type(), TokenType::String);

    lexer = new Lexer("\"hello, world\n\"");
    token = lexer->next();
    EXPECT_EQ(token.get_string(), "hello, world\n");
    EXPECT_EQ(token.get_token_type(), TokenType::String);

    lexer = new Lexer("\"hello, \\\" world\\\n\"");
    token = lexer->next();
    EXPECT_EQ(token.get_string(), "hello, \\\" world\\\n");
    EXPECT_EQ(token.get_token_type(), TokenType::String);
}
