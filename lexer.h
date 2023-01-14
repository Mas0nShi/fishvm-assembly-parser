#pragma once
#ifndef C_VM_LEXER_H
#define C_VM_LEXER_H

#include<string>

#include "token.h"


class Lexer {
private:
    std::string source;
    char ch;
    int pos;

    void nextChar();
    char peekChar();

    bool isNewline();
    bool isSpace();
    bool isAlpha();
    bool isNumber();
    void skipSpace();

   
public:
    Lexer(std::string src);

    Token NextToken();

};


#endif //C_VM_LEXER_H
