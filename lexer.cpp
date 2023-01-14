#include "lexer.h"

//#include <iostream>

Lexer::Lexer(std::string src) {
    source = src;
    pos = 0;
    ch = 0;
    nextChar(); // start.
}

void Lexer::nextChar() {
    ch = (pos >= source.length()) ? EOF : source[pos++];
}

char Lexer::peekChar() {
    return pos + 1 >= source.length() ? EOF : source[pos++];
}


bool Lexer::isNewline() {
    return ch == '\r' || ch == '\n';
}

bool Lexer::isSpace() {
    return ch == '\t' || ch == ' ';
}

void Lexer::skipSpace() {
    while (isSpace()) nextChar();
}

bool Lexer::isAlpha() {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool Lexer::isNumber() {
    return ch >= '0' && ch <= '9';
}

Token Lexer::NextToken() {
    Token t;
    skipSpace(); // skip space.

    t.literal = "";
    
    switch (ch)
    {
    case '\r':
    case '\n':
        t.type = TokenType::Newline;
        while (isNewline() || isSpace()) nextChar();
        break;
    case ';':
        t.type = TokenType::Comment;
        nextChar(); // skip ';'
        while(!isNewline()) {
            t.literal += ch;
            nextChar();
        }
        break;
    case '+':
        t.type = TokenType::Plus;
        nextChar();
        break;
    case '-': 
        t.type = TokenType::Minus;
        nextChar();
        break;
    case '[':
        t.type = TokenType::LSquareBrackets;
        nextChar();
        break;
    case ']':
        t.type = TokenType::RSquareBrackets;
        nextChar();
        break;
    case ',':
        t.type = TokenType::Comma;
        nextChar();
        break;
    case ':':
        t.type = TokenType::Colon;
        nextChar();
        break;
    case '.':
        t.type = TokenType::Dot;
        nextChar();
        break;
    case EOF:
    case '\0':
        t.type = TokenType::End;
        nextChar(); // TODO: Don't needed.
        break;
    default:
        t.type = TokenType::Symbol;
        if (ch == '"') { // string literal
            nextChar(); // skip '"'
            while (ch != '"') {
                t.literal += ch;

                if (ch == '\\') { // escape char.
                    nextChar();
                    t.literal += ch;
                }

                nextChar();
            }
            nextChar(); // skip '"'.
        } else {
            // symbol
            while (isAlpha() || isNumber()) {
                t.literal += ch;
                nextChar();
            }
        }
        break;
    }
    return t;
}