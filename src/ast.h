//
// Created by delihiros on 2020/04/10.
//

#ifndef VMLISP_AST_H
#define VMLISP_AST_H

#include <utility>
#include <vector>
#include <string>
#include <variant>

enum class DataType {
    Integer,
    Double,
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

    int get_int();

    double get_double();

    std::string get_string();

    std::vector<AST> get_vector();
};

#endif //VMLISP_AST_H
