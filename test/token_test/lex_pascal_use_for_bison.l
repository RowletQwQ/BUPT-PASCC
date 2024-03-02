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
{PROGRAM}                      { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return PROGRAM; }
{CONST}                           { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return CONST; }
{TYPE}                             { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return TYPE; }
{RECORD}                         { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return RECORD; }
{ARRAY}                          { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return ARRAY; }
{OF}                                 { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return OF; }
{VAR}                               { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return VAR; }
{FUNCTION}                    { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return FUNCTION; }
{PROCEDURE}                  { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return PROCEDURE; }
{BEGINTOKEN}                  { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return BEGINTOKEN; }
{END}                             { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return END; }
{IF}                                 { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return IF; }
{THEN}                           { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return THEN; }
{ELSE}                           { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return ELSE; }
{CASE}                           { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return CASE; }
{WHILE}                         { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return WHILE; }
{REPEAT}                       { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return REPEAT; }
{UNTIL}                         { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return UNTIL; }
{FOR}                             { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return FOR; }
{TO}                               { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return TO; }
{DOWNTO}                     { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return DOWNTO; }
{DO}                               { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return DO; }
{READ}                           { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return READ; }
{READLN}                     { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return READLN; }
{WRITE}                         { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return WRITE; }
{WRITELN}                   { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return WRITELN; }
{CHAR_KW}                   { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return CHAR_KW; }
{INTEGER_KW}               { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return INTEGER_KW; }
{REAL_KW}                   { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return REAL_KW; }
{BOOLEAN_KW}               { yylval.token.fill(Token::KW, yytext, lineno, colno);addcolno(yyleng); return BOOLEAN_KW; }
{NOT}                             { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng); return NOT; }
{PLUS}                           { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng); return PLUS; }
{MINUS}                         { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng); return MINUS; }
{INTEGER}                     { yylval.token.fill(Token::INT, yytext, lineno, colno);addcolno(yyleng); return INTEGER; }
{REAL}                           { yylval.token.fill(Token::REAL, yytext, lineno, colno);addcolno(yyleng); return REAL; }
{CHAR}                           { yylval.token.fill(Token::CHAR, yytext, lineno, colno);addcolno(yyleng); return CHAR; }
{TRUE}                           { yylval.token.fill(Token::BOOL, yytext, lineno, colno);addcolno(yyleng); return TRUE; }
{FALSE}                         { yylval.token.fill(Token::BOOL, yytext, lineno, colno);addcolno(yyleng); return FALSE; }
{STRING}                      { yylval.token.fill(Token::STRING, yytext, lineno, colno);addcolno(yyleng); return STRING; }
{IDENTIFIER}                { yylval.token.fill(Token::ID, yytext, lineno, colno);addcolno(yyleng); return IDENTIFIER; }
{COMMA}                     { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return COMMA; }
{COLON}                     { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return COLON; }
{SEMICOLON}             { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return SEMICOLON; }
{DOT}                           { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return DOT; }
{DOUBLE_DOT}            { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return DOUBLE_DOT; }
{LEFT_PARENTHESIS}  { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return LEFT_PARENTHESIS; }
{RIGHT_PARENTHESIS} { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return RIGHT_PARENTHESIS; }
{LEFT_BRACKET}          { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return LEFT_BRACKET; }
{RIGHT_BRACKET}         { yylval.token.fill(Token::SEPARATOR, yytext, lineno, colno);addcolno(yyleng); return RIGHT_BRACKET; }
{CONSTANTASSIGN}    { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng); return CONSTANTASSIGN; }
{ASSIGN}                  { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng); return ASSIGN; }
{RELOP}                   { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng); return RELOP; }
{MULOP}                   { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng); return MULOP; }
{ADDOP}                   { yylval.token.fill(Token::OPERATOR, yytext, lineno, colno);addcolno(yyleng); return ADDOP; }
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