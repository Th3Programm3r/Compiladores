#include <stdio.h>
#include "stack.h" // AST header
#include <stdlib.h> // for malloc

Instr* ldi(int v){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = LDI;
  node->attr.value = v;
  return node;
}
Instr* lda(char* var){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = LDA;
  node->attr.var = var;
  return node;
}

Instr* adi(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = ADI;

  return node;
}


Instr* sbi(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = SBI;

  return node;
}

Instr* dvi(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = DVI;

  return node;
}

Instr* mpi(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = MPI;

  return node;
}
Instr* mod(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = MODI;

  return node;
}



Instr* lbl(char* label){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = LBL;
  node->attr.var=label;
  return node;
}

Instr* fjp(char* label){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = FJP;
  node->attr.var=label;
  return node;
}

Instr* ujp(char* label){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = UJP;
  node->attr.var=label;
  return node;
}


Instr* sto(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = STO;
  return node;
}

Instr* equ(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = EQU;
  return node;
}

Instr* grt(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = GRT;
  return node;
}
Instr* geq(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = GEQ;
  return node;
}
Instr* leq(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = LEQ;
  return node;
}
Instr* les(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = LES;
  return node;
}
Instr* neq(){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = NEQ;
  return node;
}


Instr* head(InstrList* instrl){
  return instrl->instr;
}

InstrList* tail(InstrList* instrl){
  return instrl->next;
}

/*Instr* pop(InstrList* instrl){ //tirar um valor na stack
    Instr* node = (Instr*) malloc(sizeof(Instr));
    node=instr;

}*/

InstrList* push(Instr* instr,InstrList* instrl){ //colocar um valor na stack
  InstrList* node = (InstrList*) malloc(sizeof(InstrList));
  //node=createList(instr,instrl);
  node->instr=instr;
  node->next=instrl;
  return node;
}

InstrList* createList(Instr* instr,InstrList* instrl){
    InstrList* node = (InstrList*) malloc(sizeof(InstrList));
    node->instr=instr;
    node->next=instrl;
    return node;
}

Instr* prinT(char* v,char* f){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = PRINT;
  node->attr.prinT.variavel=v;
  node->attr.prinT.frase=f;
  return node;
}
Instr* printt(char* v,char* f,char* v2){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = PRINTT;
  node->attr.printt.variavel=v;
  node->attr.printt.frase=f;
  node->attr.printt.var=v2;
  return node;
}
Instr* scan(char* label){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = SCAN;
  node->attr.var=label;
  return node;
}
/*
InstrList* append(InstrList* instrl,InstrList* instrl2){
  if(instrl==NULL)
    return instrl2;

}*/
