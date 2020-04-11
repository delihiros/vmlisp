//
// Created by delihiros on 2020/04/10.
//

#include "ast.h"

DataType AST::get_datatype() {
    return dt;
}

int AST::get_int() const {
    return std::get<int>(value);
}

double AST::get_double() {
    return std::get<double>(value);
}

std::string AST::get_string() {
    return std::get<std::string>(value);
}

std::vector<AST> AST::get_vector() {
    return std::get<std::vector<AST>>(value);
}

AST::AST(DataType dt)
        : dt(dt) {}

AST::AST(DataType dt, int v)
        : dt(dt), value(v) {}

AST::AST(DataType dt, double v)
        : dt(dt), value(v) {}

AST::AST(DataType dt, std::string v)
        : dt(dt), value(v) {}

AST::AST(DataType dt, std::vector<AST> v)
        : dt(dt), value(v) {}

AST::AST()
        : dt(DataType::Unexpected) {}

std::ostream &operator<<(std::ostream &os, AST &ast) {
    switch (ast.get_datatype()){
        case DataType::Integer:
            os << "AST{ " << ast.get_int() << " Integer }";
        case DataType::Double:
            os << "AST{ " << ast.get_double() << " Double }";
        case DataType::Keyword:
            os << "AST{ " << ast.get_string() << " Keyword }";
        case DataType::Symbol:
            os << "AST{ " << ast.get_string() << " Symbol }";
        case DataType::List:
            os << "AST{ " << ast.get_string() << " List }";
            for (auto v: ast.get_vector()){
                os << "  " << v << std::endl;
            }
        default:
            os << "Unexpected";

    }
    return os;
}


