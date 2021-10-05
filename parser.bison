// Tokens
%token
  INT BOOL
  PLUS MINUS
  MUL DIV MOD
  EQUAL NOTEQ MORE MOREEQ LESS LESSEQ
  AND OR
  ID
  EQ
  SC LB RB LP RP C CO
  IF ELSE WHILE
  MAIN
  TRUE FALSE
  PRINTF SCANF
  STRING





// Operator associativity & precedence
%right PLUS
%right MINUS
%right MUL DIV MOD
%right EQUAL NOTEQ LESS LESSEQ MOREEQ MORE AND OR

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  Expr* exprValue;
  ExprList* exprlistValue;
  BoolExpr* boolValue;
  char* charValue;
  CmdList* CmdListValue;
  Cmd* CmdValue;
  char* stringValue;
}

%type <intValue> INT
%type <exprValue> expr
%type <exprlistValue> exprlist
%type <boolValue> boolexpr
%type <charValue> ID
%type <CmdListValue> cmdList
%type <CmdValue> cmd
%type <stringValue> STRING

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
CmdList* root;
}

%%
program: INT MAIN LB cmdList RB { root = $4; }


expr:
  INT {$$ = ast_integer($1);}
  |ID {$$ = ast_var($1);}
  |expr PLUS expr {  $$ = ast_operation(PLUS, $1, $3);}
  |expr MINUS expr {  $$ = ast_operation(MINUS, $1, $3);}
  |expr DIV expr {  $$ = ast_operation(DIV, $1, $3);}
  |expr MOD expr {  $$ = ast_operation(MOD, $1, $3);}
  |expr MUL expr {  $$ = ast_operation(MUL, $1, $3);}
;
exprlist:
  expr exprlist{$$ = ast_exprlist($1, $2);}
  |{$$=NULL;}
;

boolexpr:
  TRUE {$$ = ast_tf(1);}
  |FALSE {$$ = ast_tf(0);}
  |expr EQUAL expr { $$ = ast_arithmeticBool($1,$3,EQUAL);}
  |expr NOTEQ expr { $$ = ast_arithmeticBool($1,$3,NOTEQ);}
  |expr MORE expr { $$ = ast_arithmeticBool($1,$3,MORE);}
  |expr MOREEQ expr { $$ = ast_arithmeticBool($1,$3,MOREEQ);}
  |expr LESS expr { $$ = ast_arithmeticBool($1,$3,LESS);}
  |expr LESSEQ expr { $$ = ast_arithmeticBool($1,$3,LESSEQ);}
  |boolexpr AND boolexpr{$$ = ast_boolexpr($1,$3,AND);}
  |boolexpr OR boolexpr{$$ = ast_boolexpr($1,$3,OR);}
;
cmdList:
  cmd cmdList{$$ = ast_cmdList($1,$2);}
  |{$$=NULL;}
;

cmd:
  ID EQ expr SC { $$ = ast_assign($1,$3); }
  |IF LP boolexpr RP LB cmdList RB { $$ = ast_if($3,$6);}
  |IF LP boolexpr RP LB cmdList RB ELSE LB cmdList RB { $$ = ast_ifelse($3,$6,$10);}
  |WHILE LP boolexpr RP LB cmdList RB { $$ = ast_while($3,$6);}
  |PRINTF LP STRING RP SC { $$ = ast_printff($3);}
  |PRINTF LP STRING C ID RP SC { $$ = ast_print($3,$5);}
  |SCANF LP STRING  C CO ID  RP SC { $$ = ast_scan($3,$6);}
;
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
