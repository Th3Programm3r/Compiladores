
// AST definitions
#ifndef __ast_h__
#define __ast_h__

typedef struct _Expr Expr; // Convenience typedef
typedef struct _ExprList ExprList;
typedef struct _BoolExpr BoolExpr;
typedef struct _Cmd Cmd;
typedef struct _CmdList CmdList;

// AST for expressions
struct _Expr {
  enum {
    E_INTEGER,
    E_OPERATION,
    E_VAR
  } kind;
  union {
    int value; // for integer values
    char* var;
    struct {
      int operator; // PLUS, MINUS, etc
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

struct _ExprList{
  Expr* expr;
  ExprList* next;
};

struct _BoolExpr{
  enum {
    E_BOOL, E_ANDOR, E_TF
  } kind;
  union{
    int bol;
    struct{
      Expr* left;
      Expr* right;
      int relop;
    }b1;
    struct{
      BoolExpr* boolLeft;
      BoolExpr* boolRight;
      int relop;
    }b2;
  }uEL;
};

struct _Cmd{
  enum{
    E_ASSIGN,
    E_IF,
    E_IFELSE,
    E_WHILE,
    E_PRINTFF,
    E_PRINT,
    E_SCANFF
  }kind;
  union{
    struct{
      char* var;
      Expr* exp;
    }assign;
    struct{
      BoolExpr* bool;
      CmdList* cmdlist;
    }iff;
    struct{
      BoolExpr* bool;
      CmdList* cmdlistIf;
      CmdList* cmdlistElse;
    }ifelse;
    struct{
      BoolExpr* bool;
      CmdList* cmdlist;
    }whilee;
    struct{
      char* str;
    }printff;
    struct{
      char* str;
      char* var;
    }printt;
    struct{
      char* str;
      char* var;
    }scanff;
  }uC;
};

struct _CmdList{
  Cmd* cmd;
  CmdList* next;
};

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_var(char* c);
Expr* ast_operation(int operator, Expr* left, Expr* right);
ExprList* ast_exprlist(Expr* expr, ExprList* next);
BoolExpr* ast_tf(int v);
BoolExpr* ast_arithmeticBool(Expr* l,Expr* r,int relop);
BoolExpr* ast_boolexpr(BoolExpr* l,BoolExpr* r,int relop);
Cmd* ast_assign(char* v, Expr* e);
CmdList* ast_cmdList(Cmd* cmd,CmdList* next);
Cmd* ast_if(BoolExpr* boolexpr,CmdList* cmdlist);
Cmd* ast_ifelse(BoolExpr* boolexpr,CmdList* cmdlist1,CmdList* cmdlist2);
Cmd* ast_while(BoolExpr* boolexpr,CmdList* cmdList);
Cmd* ast_printff(char* str);
Cmd* ast_print(char* str,char* var);
Cmd* ast_scan(char* str,char* var);



#endif
