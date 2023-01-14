# Fish VM assembly Parser.

## TL;DR

implement a simple assembly language parser to parse x86-like assembly.


## Grammar

[Grammar for the Fish VM assembly language.](grammer.md)

## Lexer

The lexer is implemented in `lexer.cpp`. It is a simple lexer that uses char by char matching. It is not very efficient, but it is simple and easy to understand.

