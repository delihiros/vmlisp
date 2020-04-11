#include <iostream>
#include "lexer.h"

int main() {
    std::string s;
    while (std::cin >> s) {
        auto lexer = new Lexer(s);

        for (Token token = lexer->next(); token.get_tokentype() != TokenType::End; token = lexer->next()) {
            std::cout << token << std::endl;
        }
    }
}