yacc -vd pascal_parser.y
flex pascal_lexer.l
gcc  -o a.out y.tab.c lex.yy.c
