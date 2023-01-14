#pragma once
#ifndef C_VM_TOKEN_H
#define C_VM_TOKEN_H
#include <string>

enum TokenType {
    Symbol = 0,
    LSquareBrackets,   // [
    RSquareBrackets,   // ]
    Plus,              // +
    Minus,             // - 
    Colon,             // :
    Comma,             // ,
    Dot,               // .
    Newline,           // \n or \r\n
    Comment,           // ;
    End,               // end of file
};

const std::string TokenTypeMaps[] = {
    "Symbol",
    "LSquareBrackets",
    "RSquareBrackets",
    "Plus",
    "Minus",
    "Colon",
    "Comma",
    "Dot",
    "Newline",
    "Comment",
    "End",


};


struct Token {
    TokenType type;
    std::string literal;
};

#endif // C_VM_TOKEN_H