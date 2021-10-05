%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }

\-?[0-9]+ {
   yylval.intValue = atoi(yytext);
   return INT;
}



"+" { return PLUS; }
"-" {return MINUS;}
"*" {return MUL;}
"%" {return MOD;}
"/" {return DIV;}
"==" {return EQUAL;}
"!=" {return NOTEQ;}
"<" {return LESS;}
">" {return MORE;}
"<=" {return LESSEQ;}
">=" {return MOREEQ;}
"&&" {return AND;}
"||" {return OR;}
"=" {return EQ;}
";" {return SC;}
"{" {return LB;}
"}" {return RB;}
"(" {return LP;}
")" {return RP;}
"," {return C;}
"if" {return IF;}
"else" {return ELSE;}
"while" {return WHILE;}
"main()" {return MAIN;}
"int" {return INT;}
"true" {return TRUE;}
"false" {return FALSE;}
"printf" {return PRINTF;}
"scanf" {return SCANF;}
"&" {return CO;}

\-?[a-z][a-zA-Z0-9_]* {
   yylval.charValue = strdup(yytext);
   return ID;
}

\-?["][a-zA-Z0-9_!"#$%&/()=?" ]*["] {
   yylval.stringValue = strdup(yytext);
   return STRING;
}

.  { yyerror("unexpected character"); }
%%
