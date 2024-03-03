%{
#include <stdio.h>
#include <stdlib.h>
#inlcude "../token/token.hpp"

#define TABSIZE 4


int lineno = 1;             
int colno = 1;            

void newline();
void addcolno(int n);
void countlines(char *s);


extern "C"
{
    int yywrap();
    int yylex();
    void yyerror(const char *s);
}

Token token;
%}


%option noyywrap
%option nounput
%option noinput
%option bison-bridge
%option reentrant
%option case-insensitive
%option bison-locations

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
INTEGER         {DIGIT}+
REAL            {DIGIT}+"."{DIGIT}+([eE][+-]?{DIGIT}+)?


LETTER                  [a-zA-Z]
IDENTIFIER              ({LETTER}|[_])({LETTER}|{DIGIT}|[_])*

CHAR               '\''[^'\n]\''
STRING          '\''([^'\n]|\\')*\'

PLUS                    "+"
MINUS                   "-"
CONSTANTASSIGN                   "="
ASSIGN                  ":="
RELOP                   "<"|">"|"="|"<>"|"<="|">=" 
MULOP                   "*"|"/"|"%" |"div"|"mod"| "and" 
ADDOP                   "or" 

COMMA                   ","
COLON                   ":"
SEMICOLON               ";"
DOT                     "."
DOUBLE_DOT              ".."

LEFT_PARENTHESIS        "("
RIGHT_PARENTHESIS       ")"
LEFT_BRACKET            "["
RIGHT_BRACKET           "]"

ANNO_BIGBRACKET         (\{[^}]*\} )
ANNO_DOUBLE                (\/\/[^\n]*)
ANNO_MULTILINE            (\/\*([^*]|\*[^/])*\*\/)


%%
"\t"                                   { addcolno(TABSIZE); } 
"\n"                                  { newline(); }
" "                                    { addcolno(1); }
{ANNO_BIGBRACKET}       { addcolno(yyleng); }
{ANNO_DOUBLE}               { addcolno(yyleng); }
{ANNO_MULTILINE}        { countlines(yytext); }
{PROGRAM}                      { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{CONST}                           { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{TYPE}                             { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{RECORD}                         { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{ARRAY}                          { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{OF}                                 { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{VAR}                               { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{FUNCTION}                    { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{PROCEDURE}                  { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{BEGINTOKEN}                  { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{END}                             { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{IF}                                 { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{THEN}                           { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{ELSE}                           { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{CASE}                           { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{WHILE}                         { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{REPEAT}                       { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{UNTIL}                         { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{FOR}                             { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{TO}                               { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{DOWNTO}                     { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{DO}                               { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{READ}                           { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{READLN}                     { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{WRITE}                         { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{WRITELN}                   { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{CHAR_KW}                   { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{INTEGER_KW}               { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{REAL_KW}                   { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{BOOLEAN_KW}               { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng);   }
{NOT}                             { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng);   }
{PLUS}                           { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng);   }
{MINUS}                         { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng);   }
{INTEGER}                     { yylval.token.fill(Token::INT, yytext, lineno, colno);addcolno(yyleng);   }
{REAL}                           { yylval.token.fill(Token::REAL, yytext, lineno, colno);addcolno(yyleng);   }
{CHAR}                           { yylval.token.fill(Token::CHAR, yytext, lineno, colno);addcolno(yyleng);   }
{TRUE}                           { yylval.token.fill(Token::BOOL, yytext, lineno, colno);addcolno(yyleng);   }
{FALSE}                         { yylval.token.fill(Token::BOOL, yytext, lineno, colno);addcolno(yyleng);   }
{STRING}                      { yylval.token.fill(Token::STRING, yytext, lineno, colno);addcolno(yyleng);   }
{IDENTIFIER}                { yylval.token.fill(Token::ID, yytext, lineno, colno);addcolno(yyleng);   }
{COMMA}                     { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng);   }
{COLON}                     { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng);   }
{SEMICOLON}             { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng);   }
{DOT}                           { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng);   }
{DOUBLE_DOT}            { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng);   }
{LEFT_PARENTHESIS}  { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng);   }
{RIGHT_PARENTHESIS} { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng);   }
{LEFT_BRACKET}          { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng);   }
{RIGHT_BRACKET}         { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng);   }
{CONSTANTASSIGN}    { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng);   }
{ASSIGN}                  { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng);   }
{RELOP}                   { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng);   }
{MULOP}                   { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng);   }
{ADDOP}                   { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng);   }
.                                  { printf("Error: Unknown character %s\n", yytext); addcolno(yyleng); }

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
    return 1;
}