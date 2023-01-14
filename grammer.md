# Fish VM assembly grammar.


program ::= {[label] [instruction] [comment] newline}
label ::= symbol ':'
instruction ::= symbol [operand {',' operand}]
operand ::=  (symbol '[' [symbol | ['+' | '-']] ']' | symbol)

# Lexer rules in regex-ish.


newline ::= [\n\r]+
comment ::= ;[^\n\r]+
symbol ::= ([a-zA-Z0-9]('.'?[a-zA-Z0-9])*) | (\"(\\[^\n]|[^"\n])*\")
