%{
#include <stdio.h>
#include <stdlib.h>
#include "../token/token.hpp"
#define TABSIZE 4


int lineno = 1;             
int colno = 1;            

void newline();
void addcolno(int n);
void countlines(char *s);
Token token;
%}


%option case-insensitive

PROGRAM                 "program"
CONST                   "const"
TYPE                    "type"
RECORD                  "record"
ARRAY                   "array"
OF                      "of"
VAR                     "var"
FUNCTION                "function"
PROCEDURE               "procedure"
BEGINTOKEN                  "begin"
END                     "end"
IF                      "if"
THEN                    "then"
ELSE                    "else"
CASE                    "case"
WHILE                   "while"
REPEAT                  "repeat"
UNTIL                   "until"
FOR                     "for"
TO                      "to"
DOWNTO                  "downto"
DO                      "do"
READ                    "read"
READLN                  "readln"
WRITE                   "write"
WRITELN                 "writeln"
NOT                     "not"
TRUE                    "true"
FALSE                   "false"

INTEGER_KW                "integer"
REAL_KW                   "real"
BOOLEAN_KW                "boolean"
CHAR_KW                    "char"

DIGIT                   [0-9]
INTEGER                 "-"?{DIGIT}+
REAL                    "-"?{DIGIT}+"."{DIGIT}+([eE][+-]?{DIGIT}+)?


LETTER                  [a-zA-Z]
IDENTIFIER              ({LETTER}|[_])({LETTER}|{DIGIT}|[_])*

CHAR               \'(\\.|[^'\\])\'
STRING             \'([^'\n]|'')*\'


PLUS                    "+"
MINUS                   "-"
CONSTANTASSIGN           "="
ASSIGN                  ":="
RELOP                   ("<>"|"<"|"<="|">"|">=")
MULOP                   ("*"|"/"|"div"|"mod"|"and")
ADDOP   "or"


COMMA                   ","
COLON                   ":"
SEMICOLON               ";"
DOT                     "."
DOUBLE_DOT              ".."

LEFT_PARENTHESIS        "("
RIGHT_PARENTHESIS       ")"
LEFT_BRACKET            "["
RIGHT_BRACKET           "]"

ANNO_BIGBRACKET         (\{[^\}]*\})
ANNO_DOUBLE                (\/\/[^\n]*)
ANNO_MULTILINE            (\/\*([^*]|\*[^/])*\*\/)


%%
{ANNO_BIGBRACKET}       { addcolno(yyleng); token.fill(Token::ANNO, yytext, lineno, colno);return 1;}
{ANNO_DOUBLE}               { addcolno(yyleng); token.fill(Token::ANNO, yytext, lineno, colno);return 1;}
{ANNO_MULTILINE}        { countlines(yytext); token.fill(Token::ANNO, yytext, lineno, colno);return 1; }
{CHAR}                           { token.fill(Token::CHAR, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{PROGRAM}                      { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{CONST}                           { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{TYPE}                             { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{RECORD}                         { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{ARRAY}                          { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{OF}                                 { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{VAR}                               { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{FUNCTION}                    { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{PROCEDURE}                  { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{BEGINTOKEN}                  { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{END}                             { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{IF}                                 { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{THEN}                           { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{ELSE}                           { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{CASE}                           { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{WHILE}                         { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{REPEAT}                       { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{UNTIL}                         { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{FOR}                             { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{TO}                               { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{DOWNTO}                     { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{DO}                               { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{READ}                           { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{READLN}                     { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{WRITE}                         { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{WRITELN}                   { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{CHAR_KW}                   { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{INTEGER_KW}               { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{REAL_KW}                   { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{BOOLEAN_KW}               { token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{NOT}                             { token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{INTEGER}                     { token.fill(Token::INT, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{REAL}                           { token.fill(Token::REAL, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{PLUS}                           { token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng);  return 1; }
{MINUS}                         { token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng); return 1; }
{TRUE}                           { token.fill(Token::BOOL, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{FALSE}                         { token.fill(Token::BOOL, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{STRING}                      { token.fill(Token::STRING, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{COMMA}                     { token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{COLON}                     { token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{SEMICOLON}             { token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{DOT}                           { token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{DOUBLE_DOT}            { token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{LEFT_PARENTHESIS}  { token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{RIGHT_PARENTHESIS} { token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{LEFT_BRACKET}          { token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{RIGHT_BRACKET}         { token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{CONSTANTASSIGN}    { token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{RELOP}                   { token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{MULOP}                   { token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{ADDOP}                   { token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng); return 1;  }
{IDENTIFIER}                { token.fill(Token::ID, yytext, lineno, colno);addcolno(yyleng); return 1;  }
"\t"                                   { addcolno(TABSIZE); }
"\r"                                    {  }
"\n"                                  { newline(); }
" "                                    { addcolno(1); }
.                                  {  printf("Error: Unknown character"); printf( "before %d ",colno);addcolno(yyleng); printf(" at line %d, column %d\n", lineno, colno); }
%%

/*
* @brief 新行
*/
void newline() {
    lineno++;
    colno = 1;
}

/*
* @brief 增加列号
* @param n 增加的列数
*/
void addcolno(int n) {
    colno += n;
}

/*
* @brief 计算行数
* @param s 字符串
*/
void countlines(char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == '\n') {
            newline();
        }
    }
}

int yywrap() {
    return 0;
}