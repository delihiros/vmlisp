//
// Created by delihiros on 2020/04/10.
//

#ifndef VMLISP_AST_H
#define VMLISP_AST_H

#include <utility>
#include <vector>
#include <string>
#include <variant>
#include <sstream>
#include <iostream>

enum class DataType {
    Integer,
    Double,
    Symbol,
    Keyword,
    String,
    List,
    Vector,
    Set,
    HashMap,
    Program,
    Unexpected
};

class AST {
    DataType dt;
    std::variant<int, double, std::string, std::vector<AST>> value;

public:
    AST();

    explicit AST(DataType dt);

    AST(DataType dt, int v);

    AST(DataType dt, double v);

    AST(DataType dt, std::string v);

    AST(DataType dt, std::vector<AST> v);

    DataType get_datatype();

    int get_int() const;

    double get_double();

    std::string get_string();

    std::vector<AST> get_vector();

    friend std::ostream &operator<<(std::ostream &os, AST &ast);
};

#endif //VMLISP_AST_H
