#pragma once
#ifndef C_VM_PARSER_H
#define C_VM_PARSER_H

// #define DEBUG

#include "lexer.h"
#include<iostream>
#include <vector> 
#ifdef DEBUG

#define ASSERT( expression ) 					            \
	std::cout << "ASSERT: " << #expression << "    ";       \
	if( (expression) != true) {				                \
  		std::cout << " Failed in file: " << __FILE__ ;      \
  		std::cout << " at line: " << __LINE__ << std::endl; \
	}							                            \
	else std::cout << " Passed" << std::endl; 	
#else
#define ASSERT( ... )
#endif 


enum DataLabelType {
    byte = 0,
    word,
    dword,
    qword,
    string,
    // Overflow.
    Unknown,
};

const std::string DataLabelTypeStrs[] = {
    "byte",
    "word",
    "dword",
    "qword",
    "string",
};

struct DataLabel {
    std::string name;
    DataLabelType type;
    std::string literal;
};

struct CodeLabel {
    std::string name;
    std::string literal;
};

enum OperandType {
    none = 0,
    reg,
    imm,
    address,
    dataLabel,
    codeLabel,
};
const std::string OperandTypeStrs[] = {
    "None",
    "Register",
    "Immediate",
    "Address",
    "DataLabel",
    "CodeLabel",
    
};


struct Operand {
    OperandType type;
    std::string literal;
};

// instruction.
// [label] mnemonic [operands] [;comment]
struct Instruction {
    std::string label;
    std::string mnemonic;
    Operand left;
    Operand right;
    std::string comment;
};


class Parser {
    private:
    Lexer* lexer;

    Token prev;
    Token tok;

    std::vector<DataLabel> vDataLabels;
    std::vector<CodeLabel> vCodeLabels;
    std::vector<Instruction> vInstructions;
    

    void nextToken();
    DataLabel datalabel(std::string name);
    CodeLabel codelabel(std::string name);
    Operand operand();
    void label();
    
    Instruction instruction();


    public:
    Parser(Lexer* lex);
    Parser(std::string src);
    ~Parser();

    void Parse();
};


#endif // C_VM_PARSER_H