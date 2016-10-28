%{
 
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
int c;
extern YYSTYPE yylval;
%}
%%


[0-1]{32}\n { 
            yylval.str = strdup(yytext); 
            return(LINE); 
            } 


#.* {}
