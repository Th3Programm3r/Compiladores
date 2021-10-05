#include <stdio.h>
#include "parser.h"

void space(int n){
  for(int i=0;i<n;i++)
    printf(" ");
}

void printExpr(Expr* exp,int n){
    space(n);
  if(exp->kind==E_INTEGER)
    printf("%d\n",exp->attr.value);

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


    printExpr(exp->attr.op.left,n+1);//print left tree
    printExpr(exp->attr.op.right,n+1);
  }
  else if(exp->kind==E_VAR){
    printf("%s\n",exp->attr.var);
  }
}

void printBool(BoolExpr* boo,int n){
  space(n);
  if(boo->kind==E_BOOL){
    switch(boo->uEL.b1.relop) {
      case EQUAL:
        printf("==\n");
        break;
      case NOTEQ:
        printf("!=\n");
        break;
      case LESS:
        printf("<\n");
        break;
      case LESSEQ:
        printf("<=\n");
        break;
      case MORE:
        printf(">\n");
        break;
      case MOREEQ:
        printf(">=\n");
        break;
      default:
        printf("Nope\n");
    }

      printExpr(boo->uEL.b1.left,n+1);//print left tree
      printExpr(boo->uEL.b1.right,n+1);
  }
    else if(boo->kind==E_ANDOR){
      switch(boo->uEL.b2.relop) {
        case AND:
          printf("&&\n");
          break;
        case OR:
          printf("||\n");
          break;
        default:
          printf("Nope\n");
      }

      printBool(boo->uEL.b2.boolLeft,n+1);//print left tree

      printBool(boo->uEL.b2.boolRight,n+1);
    }
    else{
      if(boo->uEL.bol==1)
        printf("TRUE\n");
      else
        printf("FALSE\n");
    }
}

void printCmd(CmdList* c,int n){
  while(c!=NULL){
    space(n);
    if(c->cmd->kind==E_ASSIGN){
      printf("%s =\n",c->cmd->uC.assign.var);
      printExpr(c->cmd->uC.assign.exp,n+1);
    }
   else if(c->cmd->kind==E_IF){
      printf("if\n");
      printBool(c->cmd->uC.iff.bool,n+1);
      while(c->cmd->uC.iff.cmdlist!=NULL){
        printCmd(c->cmd->uC.iff.cmdlist,n+1);
        c->cmd->uC.iff.cmdlist=c->cmd->uC.iff.cmdlist->next;
      }
    }
    else if(c->cmd->kind==E_IFELSE){
      printf("if\n");
      printBool(c->cmd->uC.ifelse.bool,n+1);

      while(c->cmd->uC.ifelse.cmdlistIf!=NULL){//print cmdlist if
        printCmd(c->cmd->uC.ifelse.cmdlistIf,n+1);
        c->cmd->uC.ifelse.cmdlistIf=c->cmd->uC.ifelse.cmdlistIf->next;
      }

      printf("else\n");


      while(c->cmd->uC.ifelse.cmdlistElse!=NULL){//print cmdlist if else
        printCmd(c->cmd->uC.ifelse.cmdlistElse,n+1);
        c->cmd->uC.ifelse.cmdlistElse=c->cmd->uC.ifelse.cmdlistElse->next;
      }
    }
    else if(c->cmd->kind==E_WHILE){
      printf("while\n");

      printBool(c->cmd->uC.whilee.bool,n+1);
      while(c->cmd->uC.whilee.cmdlist!=NULL){
        printCmd(c->cmd->uC.whilee.cmdlist,n+1);
        c->cmd->uC.whilee.cmdlist=c->cmd->uC.whilee.cmdlist->next;
      }
    }
    else if(c->cmd->kind==E_PRINTFF){
      printf("printf\n");
      printf("%s\n",c->cmd->uC.printff.str);
    }
    else if(c->cmd->kind==E_PRINT){
      printf("printf");
      printf(" %s %s\n",c->cmd->uC.printt.str,c->cmd->uC.printt.var);
    }
    else if(c->cmd->kind==E_SCANFF){
      printf("scanf");
      printf(" %s %s\n",c->cmd->uC.scanff.str,c->cmd->uC.scanff.var);
    }
    c=c->next;
  }
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
      printCmd(root,0);
  }
  return 0;


}
