//
// Created by delihiros on 2020/04/11.
//

#ifndef VMLISP_CODEGEN_H
#define VMLISP_CODEGEN_H

#include <string>
#include <sstream>
#include "ast.h"
#include "llvm/IR/Value.h"
#include "llvm/ADT/APInt.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

static llvm::LLVMContext context;
static llvm::IRBuilder<> builder(context);
static std::unique_ptr<llvm::Module> module;
static std::map<std::string, llvm::Value *> named_values;

class Generator {
public:
    Generator();
    std::string generate_code(AST ast);

private:

    llvm::Value *generate(AST ast);

    llvm::Value *generate_program(AST ast);

    llvm::Value *generate_int(AST ast);

    llvm::Value *generate_double(AST ast);
};


#endif //VMLISP_CODEGEN_H
