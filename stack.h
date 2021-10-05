#ifndef __stack_h__
#define __stack_h__

typedef struct _Instr Instr; // Convenience typedef
typedef struct _InstrList InstrList;

struct _Instr {
  enum {
    LDI,
    LDA,
    ADI,
    SBI,
    MPI,
    MODI,
    DVI,
    EQU,//==
    GRT,//>
    GEQ,//>=
    LEQ,//<=
    LES,//<
    NEQ,//!=
    //NOT,//boolean not
    STO,
    RDI,
    WRI,//do pop of stack then write to the stack
    FJP,//false jump which requieres a boolean value at the top of stack and pop of value
    LBL,
    UJP,
    PRINT,
    PRINTT,
    SCAN
  } kind;
  union {
      int value; // for integer values
      char* var;
      struct{
        char* variavel;
        char* frase;
      }prinT;
      struct{
        char* variavel;
        char* frase;
        char* var;
      }printt;
    } attr;
};

struct _InstrList{
  Instr* instr;
  InstrList* next;
};

//expression
Instr* ldi(int v);
Instr* lda(char* var);

Instr* adi();
Instr* sbi();
Instr* dvi();
Instr* mpi();
Instr* mod();


Instr* sto();
Instr* head(InstrList* instrl);
Instr* fjp(char* label);
Instr* lbl(char* label);
Instr* ujp(char* label);

//boolean
Instr* equ();
Instr* grt();
Instr* geq();
Instr* leq();
Instr* les();
Instr* neq();

//lista
InstrList* tail(InstrList* instrl);
Instr* pop(InstrList* instrl); //tirar um valor na stack
InstrList* push(Instr* instr,InstrList* instrl); //colocar um valor na stack
InstrList* createList(Instr* instr,InstrList* instrl);
InstrList* append(InstrList* instrl,InstrList* instrl2);

Instr* prinT(char* v,char* f);
Instr* printt(char* v,char* f,char* v2);
Instr* scan(char* label);

//capitulo 8


#endif
