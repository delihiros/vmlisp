//
// Created by delihiros on 2020/04/11.
//

#include "codegen.h"

std::string Generator::generate_code(AST ast){
    std::string code;
    llvm::raw_string_ostream stream(code);
    auto value = generate(ast);
    value->print(stream);
    return code;
}

llvm::Value *Generator::generate(AST ast) {
    switch (ast.get_datatype()){
        case DataType::Program:
            return generate_program(ast);
        case DataType::Integer:
            return generate_int(ast);
        case DataType::Double:
            return generate_double(ast);
    }
}

llvm::Value *Generator::generate_program(AST ast) {
    // TODO: currently this only evaluates the first element of vec.
    return generate(ast.get_vector()[0]);
}

llvm::Value *Generator::generate_int(AST ast) {
    return llvm::ConstantInt::get(context, llvm::APInt(64, ast.get_int(), true));
}

llvm::Value *Generator::generate_double(AST ast) {
    return llvm::ConstantFP::get(context, llvm::APFloat(ast.get_double()));
}

Generator::Generator() {
    module = std::make_unique<llvm::Module>("VMLispJIT", context);
}

