#include <iostream>
#include <fstream>
#include <string>

#include "parser.h"


int main(int argc, char const *argv[])
{
    std::ifstream inFile("/Users/mason/c-vm-implement/examples/jump.asm");
    std::string source((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    
    std::cout << "Read Content: \n" << source << std::endl;
    Parser* parser = new Parser(source+"\n"); // need ends with \n
    parser->Parse();
    return 0;
}
