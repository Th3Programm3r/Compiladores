#include <stdio.h>
#include "parser.h"

void printExpr(Expr* exp){
  if(exp->kind==E_INTEGER)
    printf("Result = %d\n",exp->attr.value);
  else if(exp->kind==E_OPERATION){
    if(exp->attr.op.operator == PLUS)
      printf("+\n");
    else if(exp->attr.op.operator == MINUS)
      printf("-\n");
    else if(exp->attr.op.operator == MUL)
      printf("*\n");
    else if(exp->attr.op.operator == DIV)
      printf("/\n");
    else if(exp->attr.op.operator == MOD)
      printf("%% \n");
  }
  printExpr(exp->attr.op.left);
  printExpr(exp->attr.op.right);
}



int eval(Expr* expr) {
  int result = 0;
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  else if (expr->kind == E_INTEGER) {
    result = expr->attr.value;
  }
  else if (expr->kind == E_STRING) {
    result = expr->attr.string;
  }
  else if (expr->kind == E_OPERATION) {
    int vLeft = eval(expr->attr.op.left);
    int vRight = eval(expr->attr.op.right);
    switch (expr->attr.op.operator) {
      case PLUS:
        result = vLeft + vRight;
        break;
      case MINUS:
        result = vLeft - vRight;
        break;
      case MUL:
        result=vLeft * vRight;
        break;
      case DIV:
        result=vLeft / vRight;
        break;
      case MOD:
        result=vLeft % vRight;
        break;

      default: yyerror("Unknown operator!");
    }
  }
  else if (expr->kind == E_BOOL){
    
  }

  return result;
}
int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {
      //printf("Result = %d\n", eval(root));
      printExpr(root);
  }
  return 0;


}
