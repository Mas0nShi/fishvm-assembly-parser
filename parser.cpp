#include "parser.h"


Parser::Parser(std::string src) {
    lexer = new Lexer(src);
    prev = lexer->NextToken();
    tok = lexer->NextToken();
}

Parser::Parser(Lexer* lex) {
    lexer = lex;
    prev = lexer->NextToken();
    tok = lexer->NextToken();
}

Parser::~Parser() {
    delete lexer; // free.
}

void Parser::nextToken() {
    prev = tok;
    tok = lexer->NextToken();
}

DataLabel Parser::datalabel(std::string name) {
    // TODO: parse Data Label.
    DataLabel dl;
    dl.name = name;
    // 
    nextToken();
    ASSERT(tok.type == TokenType::Symbol)

    
    dl.type = DataLabelType::Unknown;
    for (int i = 0; i < DataLabelTypeStrs->length() + 1; i++)
    {
        if (DataLabelTypeStrs[i] == tok.literal) {
            dl.type = (DataLabelType) i;
            break;
        }
    }
    ASSERT(dl.type != DataLabelType::Unknown)
    
    nextToken();
    ASSERT(tok.type == TokenType::Symbol)

    dl.literal = tok.literal;
    nextToken();
    nextToken();
    std::cout << "\tData Label: '"<< DataLabelTypeStrs[dl.type] << "'" << "\tData: '" << dl.literal << "'" << std::endl;

    vDataLabels.push_back(dl);
    return dl;
}

CodeLabel Parser::codelabel(std::string name) {
    CodeLabel cl;
    // TODO: parse Code Label.
    cl.name = name;
    nextToken();

    vCodeLabels.push_back(cl);
    return cl;
}

void Parser::label() {
    std::string name = prev.literal;
    nextToken();
    if (tok.type == TokenType::Dot) { // data Label e.g,: `LC0: .string "hello world!\r\n"`
        datalabel(name);           
    } else if (tok.type == TokenType::Newline || tok.type == TokenType::Comment) { // code label.
        codelabel(name);
    } else {
        perror("Unknown?");
    }
}   

bool isHexdecimal(std::string& literal) {
    // prefix 0x
    if (literal.length() <= 2 || !(literal[0] == '0' && literal[1] == 'x')) return false;
    // check [1:] is xdigest.
    for (size_t i = 2; i < literal.length(); i++)
    {
        if (isxdigit(literal[i]) == 0) {
            return false;
        }
    }
    return true;
}

bool isDecimal(std::string& literal) {
    // empty string.
    if (literal.length() == 0) return false;
    for (size_t i = 0; i < literal.length(); i++)
    {
        if (isdigit(literal[i]) == 0) {
            return false;
        }
    }
    return true;
}

bool isCodeLabel(std::vector<CodeLabel>& codeLabels, std::string& literal) {
    for (size_t i = 0; i < codeLabels.size(); i++)
    {
        if (codeLabels[i].name == literal) return true;
    }
    return false;
}

bool isDataLabel(std::vector<DataLabel>& dataLabels, std::string& literal) {
    for (size_t i = 0; i < dataLabels.size(); i++)
    {
        if (dataLabels[i].name == literal) return true;
    }
    return false;
}


Operand Parser::operand() {
    Operand o;

    switch (prev.type)
    {
    case TokenType::LSquareBrackets:
        o.type = OperandType::address;
        o.literal += '[';
        nextToken();
        ASSERT(prev.type == TokenType::Symbol)
        // operand.
        o.literal += prev.literal;
        nextToken();
        ASSERT(prev.type == TokenType::RSquareBrackets) // Closure.
        o.literal += ']';
        nextToken();
        
        break;
    case TokenType::Symbol:
        o.literal = prev.literal;
        // TODO: Implenent Label.
        if (o.literal.length() == 0) o.type = OperandType::none;
        else if (isHexdecimal(o.literal) || isDecimal(o.literal)) o.type = OperandType::imm;
        else if (isCodeLabel(vCodeLabels, o.literal)) o.type = OperandType::codeLabel;
        else if (isDataLabel(vDataLabels, o.literal)) o.type = OperandType::dataLabel;
        
        else o.type = OperandType::reg;
        nextToken();
        break;
    default:
        perror("unknown operand");
        break;
    }

    return o;

}

Instruction Parser::instruction() {
    Instruction insn;
    // mnemonic
    insn.mnemonic = prev.literal;
    insn.left.type = OperandType::none;
    insn.right.type = OperandType::none;


    nextToken();
    // no operand.
    if (prev.type == TokenType::Newline || prev.type == TokenType::Comment) {
        return insn;
    }
    // has operand.
    
    // left operand.
    insn.left = operand();
    // no right operand.
    if (prev.type != TokenType::Comma) { // ,
        
        return insn;
    }
    nextToken();

    insn.right = operand();
    
    ASSERT(prev.type == TokenType::Newline || prev.type == TokenType::Comment)

    vInstructions.push_back(insn);
    return insn;
}

void Parser::Parse() {
    Instruction insn;

    while (prev.type != TokenType::End) {

        //std::cout << "Type: " << TokenTypeMaps[prev.type] << "\tLiteral: '" << prev.literal << "'"<< std::endl;
        
        switch (prev.type)
        {
        case TokenType::Symbol: 

            switch (tok.type)
            {
            case TokenType::Colon: // define label e.g.: LABEL:
                label();
                break;
            case TokenType::Comment:
            case TokenType::Symbol:
            case TokenType::Newline: // instruction. e.g.: mov rax, rbx
                insn = instruction();
                std::cout << "\tInsn: '"<< insn.mnemonic << " <" <<  OperandTypeStrs[insn.left.type] << ":" <<  insn.left.literal << "> , <" <<  OperandTypeStrs[insn.right.type] << ":" <<  insn.right.literal << "> '" << std::endl;
    
                break;
            default:
                nextToken();
                break;
            }
            
            break;
        
        case TokenType::Comment:
        case TokenType::Newline:
        case TokenType::RSquareBrackets:
        case TokenType::LSquareBrackets:
            nextToken();
            break;
        default:
            perror("Error Type!!!!");
            break;
        }

        // nextToken();
        
    }
}