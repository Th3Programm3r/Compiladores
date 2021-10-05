#include <stdlib.h> // for malloc
#include "ast.h" // AST header

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_var(char* c) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_VAR;
  node->attr.var = c;
  return node;
}

Expr* ast_operation
(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

ExprList* ast_exprlist(Expr* expr, ExprList* next){
  ExprList* node = (ExprList*) malloc(sizeof(ExprList));
  node->expr=expr;
  node->next=next;
  return node;
}

BoolExpr* ast_arithmeticBool(Expr* l,Expr* r,int relop){
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_BOOL;
  node->uEL.b1.left=l;
  node->uEL.b1.right=r;
  node->uEL.b1.relop=relop;
  return node;
}
BoolExpr* ast_boolexpr(BoolExpr* l,BoolExpr* r,int relop){
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_ANDOR;
  node->uEL.b2.boolLeft=l;
  node->uEL.b2.boolRight=r;
  node->uEL.b2.relop=relop;
  return node;
}

BoolExpr* ast_tf(int v){
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_TF;
  node->uEL.bol=v;
  return node;
}

Cmd* ast_assign(char* v, Expr* e){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_ASSIGN;
  node->uC.assign.var=v;
  node->uC.assign.exp=e;
  return node;
}

CmdList* ast_cmdList(Cmd* cmd,CmdList* next){
  CmdList* node = (CmdList*) malloc(sizeof(CmdList));
  node->cmd=cmd;
  node->next=next;
  return node;
}

Cmd* ast_if(BoolExpr* boolexpr,CmdList* cmdlist){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_IF;
  node->uC.iff.bool=boolexpr;
  node->uC.iff.cmdlist=cmdlist;
  return node;
}

Cmd* ast_ifelse(BoolExpr* boolexpr,CmdList* cmdl1,CmdList* cmdl2){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind=E_IFELSE;
  node->uC.ifelse.bool=boolexpr;
  node->uC.ifelse.cmdlistIf=cmdl1;
  node->uC.ifelse.cmdlistElse=cmdl2;
  return node;
}

Cmd* ast_while(BoolExpr* boolexpr,CmdList* cmdList){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind=E_WHILE;
  node->uC.whilee.bool=boolexpr;
  node->uC.whilee.cmdlist=cmdList;
  return node;
}

Cmd* ast_printff(char* str){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind=E_PRINTFF;
  node->uC.printff.str=str;
  return node;
}
Cmd* ast_print(char* str,char* var){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind=E_PRINT;
  node->uC.printt.str=str;
  node->uC.printt.var = var;
  return node;
}

Cmd* ast_scan(char* str,char* var){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind=E_SCANFF;
  node->uC.scanff.str=str;
  node->uC.scanff.var = var;
  return node;
}
