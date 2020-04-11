#include "gtest/gtest.h"
#include "lexer.h"
#include "parser.h"



TEST(Parser, integer) {
    auto lexer = new Lexer("123");
    auto parser = new Parser(lexer);
    AST ast = parser->parse_program();
    ast = ast.get_vector()[0];
    EXPECT_EQ(ast.get_datatype(), DataType::Integer);
    EXPECT_EQ(ast.get_int(), 123);

    lexer = new Lexer("-123");
    parser = new Parser(lexer);
    ast = parser->parse_program();
    ast = ast.get_vector()[0];
    EXPECT_EQ(ast.get_datatype(), DataType::Integer);
    EXPECT_EQ(ast.get_int(), -123);
}

TEST(Parser, double) {
    auto lexer = new Lexer("123.456");
    auto parser = new Parser(lexer);
    auto ast = parser->parse_program();
    ast = ast.get_vector()[0];
    EXPECT_EQ(ast.get_datatype(), DataType::Double);
    EXPECT_EQ(ast.get_double(), 123.456);

    lexer = new Lexer("-123.456");
    parser = new Parser(lexer);
    ast = parser->parse_program();
    ast = ast.get_vector()[0];
    EXPECT_EQ(ast.get_datatype(), DataType::Double);
    EXPECT_EQ(ast.get_double(), -123.456);
}

TEST(Parser, symbol) {
    auto lexer = new Lexer("abc");
    auto parser = new Parser(lexer);
    auto ast = parser->parse_program();
    ast = ast.get_vector()[0];
    EXPECT_EQ(ast.get_datatype(), DataType::Symbol);
    EXPECT_EQ(ast.get_string(), "abc");
}

TEST(Parser, keyword) {
    auto lexer = new Lexer(":abc");
    auto parser = new Parser(lexer);
    auto ast = parser->parse_program();
    ast = ast.get_vector()[0];
    EXPECT_EQ(ast.get_datatype(), DataType::Keyword);
    EXPECT_EQ(ast.get_string(), ":abc");
}

TEST(Parser, string) {
    auto lexer = new Lexer("\"hello, world\"");
    auto parser = new Parser(lexer);
    auto ast = parser->parse_program();
    ast = ast.get_vector()[0];
    EXPECT_EQ(ast.get_datatype(), DataType::String);
    EXPECT_EQ(ast.get_string(), "hello, world");

    lexer = new Lexer("\"hello, world\n\"");
    parser = new Parser(lexer);
    ast = parser->parse_program();
    ast = ast.get_vector()[0];
    EXPECT_EQ(ast.get_string(), "hello, world\n");
    EXPECT_EQ(ast.get_datatype(), DataType::String);

    lexer = new Lexer("\"hello, \\\" world\\\n\"");
    parser = new Parser(lexer);
    ast = parser->parse_program();
    ast = ast.get_vector()[0];
    EXPECT_EQ(ast.get_datatype(), DataType::String);
    EXPECT_EQ(ast.get_string(), "hello, \\\" world\\\n");
}

TEST(Parser, symbol_special_cases) {
    auto lexer = new Lexer("-");
    auto parser = new Parser(lexer);
    auto ast = parser->parse_program();
    ast = ast.get_vector()[0];
    EXPECT_EQ(ast.get_datatype(), DataType::Symbol);
    EXPECT_EQ(ast.get_string(), "-");

    lexer = new Lexer("--");
    parser = new Parser(lexer);
    ast = parser->parse_program();
    ast = ast.get_vector()[0];
    EXPECT_EQ(ast.get_datatype(), DataType::Symbol);
    EXPECT_EQ(ast.get_string(), "--");
}

TEST(Parser, list) {
    auto lexer = new Lexer("()");
    auto parser = new Parser(lexer);
    auto ast = parser->parse_program();
    ast = ast.get_vector()[0];
    EXPECT_EQ(ast.get_datatype(), DataType::List);
    EXPECT_EQ(ast.get_vector().size(), 0);

    lexer = new Lexer("(a)");
    parser = new Parser(lexer);
    ast = parser->parse_program();
    ast = ast.get_vector()[0];
    auto v = ast.get_vector();
    EXPECT_EQ(ast.get_datatype(), DataType::List);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0].get_datatype(), DataType::Symbol);

    lexer = new Lexer("(a 123 345)");
    parser = new Parser(lexer);
    ast = parser->parse_program();
    ast = ast.get_vector()[0];
    v = ast.get_vector();
    EXPECT_EQ(ast.get_datatype(), DataType::List);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0].get_datatype(), DataType::Symbol);
    EXPECT_EQ(v[0].get_string(), "a");
    EXPECT_EQ(v[1].get_datatype(), DataType::Integer);
    EXPECT_EQ(v[1].get_int(), 123);


    lexer = new Lexer("(a (123 345 567))");
    parser = new Parser(lexer);
    ast = parser->parse_program();
    ast = ast.get_vector()[0];
    v = ast.get_vector();
    EXPECT_EQ(ast.get_datatype(), DataType::List);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0].get_datatype(), DataType::Symbol);
    EXPECT_EQ(v[0].get_string(), "a");
    EXPECT_EQ(v[1].get_datatype(), DataType::List);
    EXPECT_EQ(v[1].get_vector().size(), 3);
}

TEST(Parser, vector) {
    auto lexer = new Lexer("[]");
    auto parser = new Parser(lexer);
    auto ast = parser->parse_program();
    ast = ast.get_vector()[0];
    EXPECT_EQ(ast.get_datatype(), DataType::Vector);
    EXPECT_EQ(ast.get_vector().size(), 0);

    lexer = new Lexer("[a]");
    parser = new Parser(lexer);
    ast = parser->parse_program();
    ast = ast.get_vector()[0];
    auto v = ast.get_vector();
    EXPECT_EQ(ast.get_datatype(), DataType::Vector);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0].get_datatype(), DataType::Symbol);

    lexer = new Lexer("[a 123 345]");
    parser = new Parser(lexer);
    ast = parser->parse_program();
    ast = ast.get_vector()[0];
    v = ast.get_vector();
    EXPECT_EQ(ast.get_datatype(), DataType::Vector);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0].get_datatype(), DataType::Symbol);
    EXPECT_EQ(v[0].get_string(), "a");
    EXPECT_EQ(v[1].get_datatype(), DataType::Integer);
    EXPECT_EQ(v[1].get_int(), 123);


    lexer = new Lexer("[a [123 345 567]]");
    parser = new Parser(lexer);
    ast = parser->parse_program();
    ast = ast.get_vector()[0];
    v = ast.get_vector();
    EXPECT_EQ(ast.get_datatype(), DataType::Vector);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0].get_datatype(), DataType::Symbol);
    EXPECT_EQ(v[0].get_string(), "a");
    EXPECT_EQ(v[1].get_datatype(), DataType::Vector);
    EXPECT_EQ(v[1].get_vector().size(), 3);
}

TEST(Parser, hashmap) {
    auto lexer = new Lexer("{}");
    auto parser = new Parser(lexer);
    auto ast = parser->parse_program();
    ast = ast.get_vector()[0];
    EXPECT_EQ(ast.get_datatype(), DataType::HashMap);
    EXPECT_EQ(ast.get_vector().size(), 0);

    lexer = new Lexer("{a 1}");
    parser = new Parser(lexer);
    ast = parser->parse_program();
    ast = ast.get_vector()[0];
    auto v = ast.get_vector();
    EXPECT_EQ(ast.get_datatype(), DataType::HashMap);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0].get_datatype(), DataType::Symbol);
    EXPECT_EQ(v[1].get_datatype(), DataType::Integer);

    lexer = new Lexer("{a 123, b 345}");
    parser = new Parser(lexer);
    ast = parser->parse_program();
    ast = ast.get_vector()[0];
    v = ast.get_vector();
    EXPECT_EQ(ast.get_datatype(), DataType::HashMap);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0].get_datatype(), DataType::Symbol);
    EXPECT_EQ(v[0].get_string(), "a");
    EXPECT_EQ(v[1].get_datatype(), DataType::Integer);
    EXPECT_EQ(v[1].get_int(), 123);
    EXPECT_EQ(v[2].get_datatype(), DataType::Symbol);
    EXPECT_EQ(v[2].get_string(), "b");
    EXPECT_EQ(v[3].get_datatype(), DataType::Integer);
    EXPECT_EQ(v[3].get_int(), 345);
}

TEST(Parser, set) {
    auto lexer = new Lexer("#{}");
    auto parser = new Parser(lexer);
    auto ast = parser->parse_program();
    ast = ast.get_vector()[0];
    EXPECT_EQ(ast.get_datatype(), DataType::Set);
    EXPECT_EQ(ast.get_vector().size(), 0);

    lexer = new Lexer("#{a 1}");
    parser = new Parser(lexer);
    ast = parser->parse_program();
    ast = ast.get_vector()[0];
    auto v = ast.get_vector();
    EXPECT_EQ(ast.get_datatype(), DataType::Set);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0].get_datatype(), DataType::Symbol);
    EXPECT_EQ(v[1].get_datatype(), DataType::Integer);

    lexer = new Lexer("#{a 123 b 345}");
    parser = new Parser(lexer);
    ast = parser->parse_program();
    ast = ast.get_vector()[0];
    v = ast.get_vector();
    EXPECT_EQ(ast.get_datatype(), DataType::Set);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0].get_datatype(), DataType::Symbol);
    EXPECT_EQ(v[0].get_string(), "a");
    EXPECT_EQ(v[1].get_datatype(), DataType::Integer);
    EXPECT_EQ(v[1].get_int(), 123);
    EXPECT_EQ(v[2].get_datatype(), DataType::Symbol);
    EXPECT_EQ(v[2].get_string(), "b");
    EXPECT_EQ(v[3].get_datatype(), DataType::Integer);
    EXPECT_EQ(v[3].get_int(), 345);
}

