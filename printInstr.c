#include <stdio.h>
#include "parser.h"
#include "stack.h"
#include <string.h>

//criar uma funçao que gera labels nova exemplo l1 l2 l3
//criar uma funcao que percorre a pilha p code a procura de variaveis

InstrList* r=NULL;//stack
InstrList* pcodeStack=NULL;//tem as instrucoes de pcode na ordem certa
InstrList* pcodeCopy=NULL;//copia a pilha para procurar todas as variaveis no pcode para poder colocar no inicio do mips
char* variables[100];//array que guarda as variaveis para nao haver redeclaracao de variavel iguais no mips
char* asc[100];//guarda frase a imprimir
int vn=0;//guarda a posicao actual da variavel na lista variables
int an=0;//guarda a posicao actual da string na lista asc
char* label[50]={"L1","L2","L3","L4","L5","L6","L7","L8","L9","L10","L11","L12","L13","L14","L15","L16","L17","L18","L19","L20","L21","L22","L23","L24","L25","L26","L27","L28","L29","L30","L31","L32","L33","L34","L35","L36","L37","L38","L39","L40","L41","L42","L43","L44","L45","L46","L47","L48","L49","L50"};
int n=0;//posicao actual da label
char* nome[10]={"n1","n2","n3","n4","n5","n6","n7","n8","n9","n10"};//gerador de nomes para declaracao tipo ascii
int tmp=0;//posicao atual nome
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void compileExpr(Expr* expr){
  if(expr->kind==E_INTEGER){
    Instr* node = (Instr*) malloc(sizeof(Instr));
    node=ldi(expr->attr.value);
    r=push(node,r);
  }
  else if(expr->kind==E_VAR){
    Instr* node = (Instr*) malloc(sizeof(Instr));
    node=lda(expr->attr.var);
    r=push(node,r);
  }
  else if(expr->kind==E_OPERATION){
    compileExpr(expr->attr.op.left);
    compileExpr(expr->attr.op.right);
    if(expr->attr.op.operator == PLUS)
      r=push(adi(),r);
    else if(expr->attr.op.operator == MINUS)
      r=push(sbi(),r);
    else if(expr->attr.op.operator == MUL)
      r=push(mpi(),r);
    else if(expr->attr.op.operator == DIV)
      r=push(dvi(),r);
    else if(expr->attr.op.operator == MOD)
      r=push(mod(),r);
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void compileBoolean(BoolExpr* boo){
  if(boo->kind==E_BOOL){
    compileExpr(boo->uEL.b1.left);
    compileExpr(boo->uEL.b1.right);
    switch(boo->uEL.b1.relop) {
      case EQUAL:
        r=push(equ(),r);
        break;
      case NOTEQ:
        r=push(neq(),r);
        break;
      case LESS:
        r=push(les(),r);
        break;
      case LESSEQ:
        r=push(leq(),r);
        break;
      case MORE:
        r=push(grt(),r);
        break;
      case MOREEQ:
        r=push(geq(),r);
        break;
      default:
        printf("Nope\n");
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void compileCmd(CmdList* c){
  while(c!=NULL){
    if(c->cmd->kind==E_ASSIGN){
      r=push(lda(c->cmd->uC.assign.var),r);
      compileExpr(c->cmd->uC.assign.exp);
      r=push(sto(),r);
    }
    else if(c->cmd->kind==E_IF){
       compileBoolean(c->cmd->uC.iff.bool);
       r=push(fjp(label[n]),r);
       while(c->cmd->uC.iff.cmdlist!=NULL){
         compileCmd(c->cmd->uC.iff.cmdlist);
         c->cmd->uC.iff.cmdlist=c->cmd->uC.iff.cmdlist->next;
       }
      r=push(lbl(label[n]),r);
      n++;
     }

     else if(c->cmd->kind==E_IFELSE){
        compileBoolean(c->cmd->uC.ifelse.bool);
        r=push(fjp(label[n]),r);
        while(c->cmd->uC.ifelse.cmdlistIf!=NULL){
          compileCmd(c->cmd->uC.ifelse.cmdlistIf);
          c->cmd->uC.ifelse.cmdlistIf=c->cmd->uC.ifelse.cmdlistIf->next;
        }
        r=push(ujp(label[n+1]),r);
        r=push(lbl(label[n]),r);

       while(c->cmd->uC.ifelse.cmdlistElse!=NULL){
         compileCmd(c->cmd->uC.ifelse.cmdlistElse);
           c->cmd->uC.ifelse.cmdlistElse=c->cmd->uC.ifelse.cmdlistElse->next;
       }
       r=push(lbl(label[n+1]),r);
       n++;
      }

      else if(c->cmd->kind==E_WHILE){
        r=push(lbl(label[n]),r);
        compileBoolean(c->cmd->uC.whilee.bool);
        r=push(fjp(label[n+1]),r);
        while(c->cmd->uC.whilee.cmdlist!=NULL){
          compileCmd(c->cmd->uC.whilee.cmdlist);
          c->cmd->uC.whilee.cmdlist=c->cmd->uC.whilee.cmdlist->next;
        }
        r=push(ujp(label[n]),r);
        r=push(lbl(label[n+1]),r);
        n++;
      }
      else if(c->cmd->kind==E_PRINTFF){
        r=push(prinT(nome[tmp],c->cmd->uC.printff.str),r);
        tmp++;
      }
      else if(c->cmd->kind==E_PRINT){
        r=push(printt(c->cmd->uC.printt.var,c->cmd->uC.printt.str,nome[tmp]),r);
        tmp++;
      }
      else if(c->cmd->kind==E_SCANFF){
        r=push(scan(c->cmd->uC.scanff.var),r);
      }
    c=c->next;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void print(InstrList* r){//print the p code stack and do the mips
  FILE *file=fopen("mips.asm","w");
  if(file==NULL){
    printf("Erro ao abrir o ficheiro\n");
    exit(1);
  }
  fprintf(file,".data\n");
  findVariable(pcodeCopy);//procura variaveis e coloca na array
  for(int i=0;i<100 && variables[i]!=NULL;i++){
    fprintf(file,"%s: .space 4\n",variables[i]);
  }
  for(int i=0;i<100 && asc[i]!=NULL;i++){
    fprintf(file,"%s: .asciiz %s\n",asc[i+1],asc[i]);
  }
  fprintf(file,".text\n\n");

  while(r!=NULL){
    if(r->instr->kind==LDI){
      printf("LDI %d ",r->instr->attr.value);
      fprintf(file, "li $s1,%d\n",r->instr->attr.value);
      fprintf(file, "sw $s1,0($sp)\n");
      fprintf(file, "addiu $sp,$sp,-4\n\n");
    }
    else if(r->instr->kind==LDA){
      printf("LDA %s ",r->instr->attr.var);
      fprintf(file, "lw $a1,%s\n",r->instr->attr.var);
      fprintf(file, "sw $a1,0($sp)\n");
      fprintf(file, "addiu $sp,$sp,-4\n\n");
    }
    else if(r->instr->kind==ADI){
      printf("ADI ");
      fprintf(file, "lw $s1,0($sp)\n");
      fprintf(file, "lw $s2,4($sp)\n");
      fprintf(file, "addiu $sp,$sp,8\n");
      fprintf(file, "add $s3,$s1,$s2\n");//adciona
      fprintf(file, "sw $s3,0($sp)\n");
      fprintf(file, "addiu $sp,$sp,-4\n\n");
    }
    else if(r->instr->kind==SBI){
      printf("SBI ");
      fprintf(file, "lw $s1,0($sp)\n");
      fprintf(file, "lw $s2,4($sp)\n");
      fprintf(file, "addiu $sp,$sp,8\n");
      fprintf(file, "sub $s3,$s1,$s2\n");//adciona
      fprintf(file, "sw $s3,0($sp)\n");
      fprintf(file, "addiu $sp,$sp,-4\n\n");
    }
    else if(r->instr->kind==DVI){
      printf("DVI ");
      fprintf(file, "lw $s1,0($sp)\n");
      fprintf(file, "lw $s2,4($sp)\n");
      fprintf(file, "addiu $sp,$sp,8\n");
      fprintf(file, "divu $s3,$s1,$s2\n");//adciona
      fprintf(file, "sw $s3,0($sp)\n");
      fprintf(file, "addiu $sp,$sp,-4\n\n");
    }
    else if(r->instr->kind==MPI){
      printf("MPI ");
      fprintf(file, "lw $s1,0($sp)\n");
      fprintf(file, "lw $s2,4($sp)\n");
      fprintf(file, "addiu $sp,$sp,8\n");
      fprintf(file, "mul $s3,$s1,$s2\n");//adciona
      fprintf(file, "sw $s3,0($sp)\n");
      fprintf(file, "addiu $sp,$sp,-4\n\n");
    }
    else if(r->instr->kind==MODI)//temos de saber fazer loop
      printf("MOD ");
    else if(r->instr->kind==EQU){
      printf("EQU ");
      fprintf(file,"lw $s1,0($sp)\n");//le da pilha o valor
      fprintf(file,"lw $s2,4($sp)\n");//le da pilha o valor
      fprintf(file,"addiu $sp,$sp,8\n");//tira da pilha
      fprintf(file,"beq $s1,$s2, ");
    }
    else if(r->instr->kind==GRT){
      printf("GRT ");
      fprintf(file,"lw $s1,0($sp)\n");//le da pilha o valor
      fprintf(file,"lw $s2,4($sp)\n");//le da pilha o valor
      fprintf(file,"addiu $sp,$sp,8\n");//tira da pilha
      fprintf(file,"sgt $s3,$s1,$s2\n");//retorna 1 se s1>s2
      fprintf(file,"beq $s3,$zero, ");
    }
    else if(r->instr->kind==GEQ){
      printf("GEQ ");
      fprintf(file,"lw $s1,0($sp)\n");//le da pilha o valor
      fprintf(file,"lw $s2,4($sp)\n");//le da pilha o valor
      fprintf(file,"addiu $sp,$sp,8\n");//tira da pilha
      fprintf(file,"sge $s3,$s1,$s2\n");//retorna 1 se s1>=s2
      fprintf(file,"beq $s3,$zero, ");
    }
    else if(r->instr->kind==LEQ){
      printf("LEQ ");
      fprintf(file,"lw $s1,0($sp)\n");//le da pilha o valor
      fprintf(file,"lw $s2,4($sp)\n");//le da pilha o valor
      fprintf(file,"addiu $sp,$sp,8\n");//tira da pilha
      fprintf(file,"sle $s3,$s1,$s2\n");//retorna 1 se s1=<s2
      fprintf(file,"beq $s3,$zero, ");

    }
    else if(r->instr->kind==LES){
      printf("LES ");
      fprintf(file,"lw $s1,0($sp)\n");//le da pilha o valor
      fprintf(file,"lw $s2,4($sp)\n");//le da pilha o valor
      fprintf(file,"addiu $sp,$sp,8\n");//tira da pilha
      fprintf(file,"slt $s3,$s1,$s2\n");//retorna 1 se s1<s2
      fprintf(file,"beq $s3,$zero, ");
    }
    else if(r->instr->kind==NEQ){
      printf("NEQ ");
      fprintf(file,"lw $s1,0($sp)\n");//le da pilha o valor
      fprintf(file,"lw $s2,4($sp)\n");//le da pilha o valor
      fprintf(file,"addiu $sp,$sp,8\n");//tira da pilha
      fprintf(file,"bne $s1,$s2, ");
    }
    else if(r->instr->kind==STO){
      printf("STO ");
      fprintf(file,"lw $s1,0($sp)\n");//le da pilha o valor que vai ser o valor da atribuicao
      fprintf(file,"addiu $sp,$sp,4\n");//tira da pilha o valor
      fprintf(file,"lw $s2,0($sp)\n");//le da pilha o valor que vai ser da variavel
      fprintf(file,"addiu $sp,$sp,4\n");//tira da pilha a variavel
      fprintf(file,"add $s3,$s1,$s2\n");//soma os valores lidos da pilha
      fprintf(file,"sw $s3,0($sp)\n");//coloca na pilha o valor de x
      fprintf(file,"addiu $sp,$sp,-4\n\n");//avanca a pilha
    }
    else if(r->instr->kind==FJP){
      printf("FJP %s ",r->instr->attr.var);
      fprintf(file,"%s \n\n",r->instr->attr.var);
    }
    else if(r->instr->kind==UJP){
      printf("UJP %s ",r->instr->attr.var);
      fprintf(file,"j %s \n\n",r->instr->attr.var);
    }
    else if(r->instr->kind==LBL){
        printf("LABEL %s ",r->instr->attr.var);
        fprintf(file,"%s:\n",r->instr->attr.var);
    }
    else if(r->instr->kind==PRINT){
        printf("PRINT ");
        fprintf(file, "li $v0,4\n");
        fprintf(file, "la $a0,%s\n",r->instr->attr.prinT.variavel);
        fprintf(file, "syscall\n\n");
    }
    else if(r->instr->kind==PRINTT){
        printf("PRINT ");
        fprintf(file, "li $v0,4\n");
        fprintf(file, "la $a0,%s\n",r->instr->attr.prinT.variavel);
        fprintf(file, "syscall\n\n");
    }
    else if(r->instr->kind==SCAN){
        printf("SCAN ");
        fprintf(file, "li $v0,5\n");
        fprintf(file, "syscall\n");
        fprintf(file, "move $t0,$v0\n\n");
        fprintf(file, "sw $t0,0($sp)\n");
        fprintf(file, "addiu $sp,$sp,-4\n");
    }
    r=r->next;
  }
}

void reverseStack(){//funcao que reverte a stack que contem instrucoes pcode
  while(r!=NULL){
    pcodeStack=push(r->instr,pcodeStack);
    pcodeCopy=push(r->instr,pcodeCopy);
    r=r->next;
  }
}

void findVariable(InstrList* stack){//procura todas as variaveis guardadas na stack para fazer um lw no assembly
    while(stack!=NULL){
      if(stack->instr->kind==LDA){
        if(existeVariavel(stack->instr->attr.var)==0){//caso a variavel nao estiver guardada na String
          variables[vn]=stack->instr->attr.var;
          vn++;
        }
      }
      if(stack->instr->kind==PRINT){
        asc[an]=stack->instr->attr.prinT.frase;
        asc[an+1]=stack->instr->attr.prinT.variavel;
        an=an+2;
      }
      if(stack->instr->kind==PRINTT){
        if(existeVariavel(stack->instr->attr.printt.var)==0){//caso a variavel nao estiver guardada na String
          variables[vn]=stack->instr->attr.printt.variavel;
          vn++;
        }
      }
      stack=stack->next;
    }
}

int existeVariavel(char* var){//verifica se uma variavel ja existe guardada na lista para nao fazer declaracao de duas variaveis iguais
  for(int i=0;i<100 && variables[i]!=NULL;i++){
    if(strcmp(var,variables[i]) == 0)
      return 1;
  }
  return 0;
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

    compileCmd(root);
    reverseStack();//reverte a stack p code porque as expressoes ficaram ao contrario
    print(pcodeStack);
    printf("\n");


  }
  return 0;


}
