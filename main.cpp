#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "codegen.h"

int main() {
    std::string s;
    while (std::cin >> s) {
        auto lexer = new Lexer(s);
        auto parser = new Parser(lexer);
        auto generator = new Generator();
        auto ast = parser->parse_program();
        auto code = generator->generate_code(ast);
        // std::cout << code << std::endl;

    }
}