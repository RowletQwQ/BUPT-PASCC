#!/bin/bash
flex --outfile lex_pascal.cpp --header-file=lex_sql.h lex_pascal.l
`which bison` -d -Wcounterexamples --output yacc_pascal.cpp yacc_pascal.y