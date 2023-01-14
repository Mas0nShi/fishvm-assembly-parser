#include <iostream>
#include <fstream>
#include <string>

#include "lexer.h"


int main(int argc, char const *argv[])
{
    std::ifstream inFile("/Users/mason/c-vm-implement/examples/write.asm");
    std::string source((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    
    std::cout << "Read Content: \n" << source << std::endl;
    Lexer* lexer = new Lexer(source);
    Token t;

    do {
        t = lexer->NextToken();
        std::cout << "Type: " << TokenTypeMaps[t.type] << "\tLiteral: '" << t.literal << "'"<< std::endl;
    } while (t.type != TokenType::End);

    return 0;
}
