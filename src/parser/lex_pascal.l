%top{
/*
这里的代码会被复制到lex_pascal.cpp的最开始位置
定义yy_size_t的原因是因为flex生成的代码，会使用yy_size_t与其他类型的数字
做比较，导致编译报警
*/

#define YY_TYPEDEF_YY_SIZE_T
typedef int yy_size_t;

/* 参考生成的lex_pascal.cpp代码，这个宏定义会放在每次运行yylex()最开始的地方 */
#define YY_USER_INIT                                         \
  yycolumn = 0;

/* 参考生成的lex_pascal.cpp代码，这个宏定义会放在解析一个token之后，也可以在网上找到大量的参考资料 */
/* 我们在这里设置当前解析的token的位置信息，这样在yacc中就可以使用这些信息了 */
#define YY_USER_ACTION                                       \
do {                                                         \
  yylloc->first_line   = yylloc->last_line = yylineno;       \
  yylloc->first_column = yycolumn;                           \
  yylloc->last_column  = yylloc->first_column + yyleng - 1;  \
  yycolumn += yyleng;                                        \
}                                                            \
while (0);


}
%{
#include<cstring>
#include<cstdio>
/**
 * flex 代码包含三个部分，使用 %% 分隔
 * 第一个部分的代码是C代码，flex会原样复制到目标文件中
 * 第二个部分是规则部分，使用正则表达式定义一系列规则
 * 第三个部分还是C代码，flex 会复制此段代码
 */

#include "ast/stmt.hpp"
#include "common/log/log.hpp"
#include "yacc_pascal.hpp"

#define TABSIZE 4
#ifndef register
#define register 
#endif // register

extern int atoi();
extern double atof();

#define RETURN_TOKEN(token) LOG_DEBUG("%s  %s", #token, yytext);return token

char *strdup_tolower(const char *s) {
    char *d = (char *)malloc(strlen(s) + 1);
    if (d == NULL) return NULL;
    for (int i = 0; s[i]; i++) {
        d[i] = tolower((unsigned char)s[i]);
    }
    d[strlen(s)] = '\0';  // 确保字符串以 null 结尾
    return d;
}

%}

/* Prevent the need for linking with -lfl */
%option noyywrap
%option nounput
%option noinput
%option bison-bridge
%option reentrant
%option yylineno
/* 不区分大小写 */
%option case-insensitive
%option bison-locations

DIGIT                   [0-9]
INTEGER         {DIGIT}+
REAL               {DIGIT}+"."{DIGIT}+

LETTER                  [a-zA-Z]
IDENTIFIER              ({LETTER}|[_])({LETTER}|{DIGIT}|[_])*


CHAR               (\'([^'\n]|\\.)\')


ANNO_BIGBRACKET         (\{[^\}]*\})
ANNO_DOUBLE                (\/\/[^\n]*)
ANNO_MULTILINE            (\/\*([^*]|\*[^/])*\*\/)

BRACE_PAIR                (\]\[)
OTHER_SIGN                     [\~\;\:\.\,\+\-\*\/\(\)\[\]\=\>\<\&\|\!]

%%
"program"                        RETURN_TOKEN(PROGRAM);
"const"                              RETURN_TOKEN(CONST);
"type"                                RETURN_TOKEN(TYPE);
"record"                             RETURN_TOKEN(RECORD);
"array"                               RETURN_TOKEN(ARRAY);
"of"                                    RETURN_TOKEN(OF);
"var"                                   RETURN_TOKEN(VAR);
"function"                          RETURN_TOKEN(FUNCTION);
"procedure"                       RETURN_TOKEN(PROCEDURE);
"begin"                               RETURN_TOKEN(BEGIN_TOKEN);
"end"                                  RETURN_TOKEN(END);
"if"                                      RETURN_TOKEN(IF);
"then"                                 RETURN_TOKEN(THEN);
"else"                                  RETURN_TOKEN(ELSE);
"case"                                 RETURN_TOKEN(CASE);
"while"                               RETURN_TOKEN(WHILE);
"repeat"                             RETURN_TOKEN(REPEAT);
"until"                                RETURN_TOKEN(UNTIL);
"for"                                   RETURN_TOKEN(FOR);
"to"                                     RETURN_TOKEN(TO);
"downto"                           RETURN_TOKEN(DOWNTO);
"do"                                   RETURN_TOKEN(DO);
"read"                                RETURN_TOKEN(READ);
"readln"                            RETURN_TOKEN(READLN);
"write"                               RETURN_TOKEN(WRITE);
"writeln"                            RETURN_TOKEN(WRITELN);
"char"                                RETURN_TOKEN(CHAR_KW);
"integer"                           RETURN_TOKEN(INTEGER_KW);
"real"                                  RETURN_TOKEN(REAL_KW);
"boolean"                           RETURN_TOKEN(BOOLEAN_KW);

"true"                                     yylval->boolean = true;  return BOOLEAN;
"false"                                   yylval->boolean = false;  return BOOLEAN;

"not"                                    RETURN_TOKEN(NOT);

"div"                                       RETURN_TOKEN(DIV);
"mod"                                    RETURN_TOKEN(MOD);
"and"                                      RETURN_TOKEN(AND);

"or"                           RETURN_TOKEN(OR);
                              
"<>"                          RETURN_TOKEN(NE);
"<="                         RETURN_TOKEN(LE);
">="                        RETURN_TOKEN(GE);


":="                         RETURN_TOKEN(ASSIGNOP);
"in"                              RETURN_TOKEN(IN);

"or else"                        RETURN_TOKEN(ORELSE);
"and then"                             RETURN_TOKEN(ANDTHEN);

{BRACE_PAIR}                            RETURN_TOKEN(BRACE_PAIR);
".."                                       RETURN_TOKEN(DOUBLE_DOT);

{OTHER_SIGN}                            RETURN_TOKEN(yytext[0]);

{INTEGER}                                yylval->number = atoi(yytext); RETURN_TOKEN(INTEGER);
{REAL}                                     yylval->real = (float)atof(yytext); RETURN_TOKEN(REAL);
{CHAR}                                    yylval->charactor = yytext[1]; RETURN_TOKEN(CHAR);
{IDENTIFIER}                          yylval->string = strdup_tolower(yytext);RETURN_TOKEN(IDENTIFIER);

{ANNO_BIGBRACKET}               // ignore comments
{ANNO_DOUBLE}                       // ignore comments
{ANNO_MULTILINE}                   // ignore comments

"\t"                                       /* ignore whitespace */
"\n"
"\r"
" "
\"[^"]*\"                               yylval->string = strdup(yytext); RETURN_TOKEN(STRING);
'[^']*\'                                yylval->string = strdup(yytext); RETURN_TOKEN(STRING);

.                                                /* ignore other characters */
%%

void scan_string(const char *str, yyscan_t scanner) {
    yy_switch_to_buffer(yy_scan_string(str, scanner), scanner);
    //{STRING}                                yylval->string = strdup(yytext); RETURN_TOKEN(STRING);
}