%{
// #include <iostream>
/* #include <string> */
/* #include "parser.hpp" */
#include <stdio.h>
#include <string.h>
// #include "y.tab.h"
/* using namespace beast; */
/* using token = Parser::token; */
int line_num = 1;

%}

/* %option reentrant interactive outfile="scanner.cpp" header="scanner.h" */
%option yylineno
/* %option debug */
%%

"def"                     printf("DEF ");
"build"                   printf("BUILD ");
[a-zA-Z][a-zA-Z0-9_]*    printf("WORD "); 
[0-9]+                  printf("NUMBER "); 
"\""                      printf("QUOTE "); 
"("                       printf("SBRAC "); 
")"                       printf("EBRAC "); 
":"                       printf("COLON "); 
"="                       printf("ASSIGN "); 
"*"                      printf("MULTIPLY ");
"+"                      printf("ADD "); 
"/"                       printf("DIVIDE "); 
"-"                       printf("SUBTRACT "); 
\"[^\"]*\"                   printf("STRING LIT ");
[a-zA-Z0-9\/.-]*\.[a-zA-Z0-9\.-]+            printf("FILENAME "); 
\$[a-zA-Z][a-zA-Z0-9_]*     printf("DEREF "); 
\![ ]*([^\n])*              printf("COMMAND "); 
"\n"                      printf("\n"); line_num++; 
" "                  /* ignore whitespace */;
"\t"                    printf("TAB "); 
.                    return (int)yytext[0];

%%

