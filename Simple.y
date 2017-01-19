%{/*************************************************************************
Compiler for the Simple language
***************************************************************************/
/*=========================================================================
C Libraries, Symbol Table, Code Generator & other C code
/=========================================================================*/
#include <stdio.h> /* For I/O */
#include <stdlib.h> /* For malloc here and in symbol table */
#include <string.h> /* For strcmp in symbol table */
#include "Quad.h" /* Quad Code */
#include "ST.h" /* Symbol Table */
#include "branchList.h" /*branch List For backpatching */
#include "numStack.h" /* numStack Code */
#include "tools.h" /* tools Code */
#include "basicBlock.h" /* basicBlock Code */
#include "CodeGenerate.h" /* codeGenerate Code */
// #include "SM.h" /* Stack Machine */
// #include "CG.h" /* Code Generator */
#define YYDEBUG 1 /* For Debugging */
int errors; /* Error Count */

/*-------------------------------------------------------------------------
The following support backpatching
-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
Install identifier & check if previously defined.
-------------------------------------------------------------------------*/

void registerId(char *sym_name, char *type, int width, int height, struct symrec * scope, struct Quad* entry, struct symrec *param) {
  symrec *s;
  s = getsymInScope(sym_name);
  if (s == 0)
    s = putsym(sym_name, type, width, height, scope, entry, param);
  else {
    errors++;
    printf("%s is already defined\n", sym_name);
  }
}
/*-------------------------------------------------------------------------
If identifier is defined, generate code
-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
define the return type for each terminal and nonterminal
-------------------------------------------------------------------------*/

%}
/*=========================================================================
SEMANTIC RECORDS
/=========================================================================*/

%union semrec /* The Semantic Records */
{
  int intval;       /* Integer values */
  int offset;
  char *id;         /* Identifiers */
  struct{
    char* id;
    int width;
    int height;
  } variable;

  struct{
    int valType; /*can be 0:empty, 1:int, 2:temp, 3:id, 4:id reg */
    // int intval;
    int temp;
    char* id;
    int offset; /*3:int 4:reg*/
    struct branchList* trueList;
    struct branchList* falseList;
    struct branchList* nextList;
  } value;

  struct{
    char* id;
    struct symrec *param;
    struct Quad * beforeEntry;
  } funcType;
  /* For backpatching */
  struct Quad * inst;
  struct branchList * nextlist;

  struct{
    struct branchList * nextList;
    int breakCount;
    int continueCount;
    struct branchList * breakList;
    struct branchList * continueList;
  } stmtType;

}
/*=========================================================================
TOKENS
/=========================================================================*/
%start program
%token<intval> INT
%token<id> ID
%token SEMI
%token COMMA

%token DOT
%token BINARYOP_MUL
%token BINARYOP_DIV
%token BINARYOP_MOD
%token BINARYOP_ADD
%token MIN
%token BINARYOP_SHL
%token BINARYOP_SHR
%token BINARYOP_GT
%token BINARYOP_NLT
%token BINARYOP_LT
%token BINARYOP_NGT
%token BINARYOP_EQ
%token BINARYOP_NEQ
%token BINARYOP_BAND
%token BINARYOP_BXOR
%token BINARYOP_BOR
%token BINARYOP_LAND
%token BINARYOP_LOR
%token BINARYOP_ASSIGN
%token BINARYOP_MULA
%token BINARYOP_DIVA
%token BINARYOP_ADDA
%token BINARYOP_MINA
%token BINARYOP_BANDA
%token BINARYOP_BXORA
%token BINARYOP_BORA
%token BINARYOP_SHLA
%token BINARYOP_SHRA

%token UNARYOP_LNOT
%token UNARYOP_INCR
%token UNARYOP_DECR
%token UNARYOP_BNOT

%token TYPE
%token LP
%token RP
%token LB
%token RB
%token LC
%token RC
%token STRUCT
%token RETURN 
%token IF
%token ELSE
%token BREAK
%token CONT
%token FOR
/*=========================================================================
OPERATOR PRECEDENCE
/=========================================================================*/
%right BINARYOP_ASSIGN BINARYOP_MULA BINARYOP_DIVA BINARYOP_ADDA BINARYOP_MINA BINARYOP_BANDA BINARYOP_BXORA BINARYOP_BORA BINARYOP_SHLA BINARYOP_SHRA
%left BINARYOP_LOR
%left BINARYOP_LAND
%left BINARYOP_BOR
%left BINARYOP_BXOR
%left BINARYOP_BAND
%left BINARYOP_NEQ BINARYOP_EQ
%left BINARYOP_NGT BINARYOP_LT BINARYOP_NLT BINARYOP_GT
%left BINARYOP_SHL BINARYOP_SHR
%left MIN BINARYOP_ADD
%left BINARYOP_MOD BINARYOP_DIV BINARYOP_MUL
%right UNARYOP_BNOT UNARYOP_DERE UNARYOP_INCR UNARYOP_LNOT
%left DOT LP RP LB RB
/*=========================================================================
Return type for the terminal and non-terminal
/=========================================================================*/
%type<variable> varArray var
%type<value> exps exp arrs
%type<intval> args
%type<funcType> func
%type<inst> MM 
%type<nextlist> NN 
%type<stmtType> stmt stmts stmtblock
%type<id> stspec
%type<offset> sdefs


/*=========================================================================
GRAMMAR RULES for the Simple language
/=========================================================================*/
%%

program   : extdefs
;

extdefs   : /* empty */
          | {IR = InitR;} extdef extdefs
;

extdef    : TYPE extvars SEMI /*但是这里理论上按照原来的规则也是要补的,但是感觉是元规则错了,c语言中int;这是啥啊*/
          | stspec sextvars SEMI
          | stspec SEMI /*这里是在将sextvars规则转换之后的补充，用于补充empty情况*/
          | TYPE func {
              genIRForLabel($<funcType.id>2);
              IR = InterR;
              genIRForLabel($<funcType.id>2);
              getsym($<funcType.id>2)->entry = $<funcType.beforeEntry>2->next;
              getsym($<funcType.id>2)->param = $<funcType.param>2;
            } stmtblock {
              getsym($<funcType.id>2)->scope = subLevel();
              if($<stmtType.continueList>4 != 0 || $<stmtType.breakList>4 != 0 ) yyerror("lack the for loop!\n");
            }
;

sextvars  : sextvars COMMA ID {
            if(getsym($3) != 0) yyerror("wrong while declaration\n");
            else registerId($3, $<id>0, 0, 0, 0, 0, 0);
          }
          | ID {
            if(getsym($1) != 0) yyerror("wrong while declaration\n");
            else registerId($1, $<id>0, 0, 0, 0, 0, 0);
          }
;

extvars   : extvars COMMA var {
            if(getsym($<variable.id>3) != 0) yyerror("wrong while declaration\n");
            else registerId($<variable.id>3, "int", $<variable.width>3, $<variable.height>3, 0, 0, 0);
          }
          | extvars COMMA ID BINARYOP_ASSIGN exps {
            if(getsym($3) != 0) yyerror("wrong while declaration\n");
            else {
              registerId($3, "int", 1, 1, 0, 0, 0);
              if($<value.valType>5 == 1){
                int temp = newTemp();
                genIR(li, 0, $<value.temp>5, temp);
                genIRForLS(swi, temp, 0, $3);
              } else {
                int temp = normalizeExp((struct NSData *) &$5);
                genIRForLS(swi, temp, 0, $3);
              }
            }
          }
          | ID BINARYOP_ASSIGN exps {
            if(getsym($1) != 0) yyerror("wrong while declaration\n");
            else {
              registerId($1, "int", 1, 1, 0, 0, 0);
              if($<value.valType>3 == 1){
                int temp = newTemp();
                genIR(li, 0, $<value.temp>3, temp);
                genIRForLS(swi, temp, 0, $1);
              } else {
                int temp = normalizeExp((struct NSData *) &$3);
                genIRForLS(swi, temp, 0, $1);
              }
            }
          }
          | extvars COMMA varArray BINARYOP_ASSIGN LC args RC {
            if(getsym($<variable.id>3) != 0) yyerror("wrong while declaration\n");
            else {
              registerId($<variable.id>3, "int", $<variable.width>3, $<variable.height>3, 0, 0, 0);
              int i = 0;
              struct NSData* temp;
              if(($<variable.width>3 * $<variable.height>3) >= $6){
                for(i=$6-1;i >= 0 ;i--){
                  temp = NSPop();
                  if(temp->valType == 1){
                    int tempReg = newTemp();
                    genIR(li, 0, temp->temp, tempReg);
                    genIRForLS(swi, tempReg, i*4, $<variable.id>3);
                  }
                  else{
                    int tempReg = normalizeExp(temp);
                    genIRForLS(swi, tempReg, i*4, $<variable.id>3);
                  }
                }
              }
              else{
                yyerror("wrong while init array!\n");
              }
            }
          }
          | varArray BINARYOP_ASSIGN LC args RC {
            if(getsym($<variable.id>1) != 0) yyerror("wrong while declaration\n");
            else {
              registerId($<variable.id>1, "int", $<variable.width>1, $<variable.height>1, 0, 0, 0);
              int i = 0;
              struct NSData* temp;
              if(($<variable.width>1 * $<variable.height>1) >= $4){
                for(i=$4-1;i >= 0 ;i--){
                  temp = NSPop();
                  if(temp->valType == 1){
                    int tempReg = newTemp();
                    genIR(li, 0, temp->temp, tempReg);
                    genIRForLS(swi, tempReg, i*4, $<variable.id>1);
                  }
                  else{
                    int tempReg = normalizeExp(temp);
                    genIRForLS(swi, tempReg, i*4, $<variable.id>1);
                  }
                }
              }
              else{
                yyerror("wrong while init array!\n");
              }
            }
          }
          | var {
            if(getsym($<variable.id>1) != 0) yyerror("wrong while declaration\n");
            else registerId($<variable.id>1, "int", $<variable.width>1, $<variable.height>1, 0, 0, 0);
          }
;

stspec    : STRUCT ID LC {addLevel();} sdefs RC{
            if(getsym($2) != 0) yyerror("wrong while declaration\n");
            else {
              registerId($2, "struct", $5, 0, subLevel(), 0, 0);
              $$ = $2;
            }
          }
          | STRUCT LC {addLevel();} sdefs RC{
            char * tempID = (char *) malloc(sizeof(char)*9);
            sprintf(tempID, "%d", getRandomNumber());
            if(getsym(tempID) != 0) yyerror("wrong while declaration\n");
            else {
              registerId(tempID, "struct", $4, 0, subLevel(), 0, 0);
              $$ = tempID;
            }
          } /*在没有ID的情况下可能需要随机分配一个?*/
          | STRUCT ID {
            $$ = $2;
          }
;

func      : ID {
            if(getsym($1) != 0) yyerror("wrong while declaration\n");
            else registerId($1, "func", 0, 0, 0, 0, 0);
          } LP {addLevel();} paras RP{
            $<funcType.id>$ = $1;
            $<funcType.param>$ = sym_table;
            $<funcType.beforeEntry>$ = InterR->tail;
          }
;

paras     : TYPE ID COMMA paras{
            if(getsym($2) != 0) yyerror("wrong while declaration\n");
            else registerId($2, "int", 1, 1, 0, 0, 0);
          }
          | TYPE ID {
            if(getsym($2) != 0) yyerror("wrong while declaration\n");
            else registerId($2, "int", 1, 1, 0, 0, 0);
          }
          | /* empty */
;

stmtblock : LC {IR = InitR;} defs {IR = InterR;} stmts RC {
            $<stmtType.nextList>$ = 0;
            $<stmtType.continueCount>$ = $<stmtType.continueCount>5;
            $<stmtType.breakCount>$ = $<stmtType.breakCount>5;
            $<stmtType.continueList>$ = $<stmtType.continueList>5;
            $<stmtType.breakList>$ = $<stmtType.breakList>5;
          }
;

stmts     : /* empty */ {
            $<stmtType.nextList>$ = 0;
            $<stmtType.continueCount>$ = 0;
            $<stmtType.breakCount>$ = 0;
            $<stmtType.continueList>$ = 0;
            $<stmtType.breakList>$ = 0;
          }
          | stmt MM stmts {
            backpatch($<stmtType.nextList>1, $2->next);
            $<stmtType.nextList>$ = 0;
            $<stmtType.continueCount>$ = $<stmtType.continueCount>1 + $<stmtType.continueCount>3;
            $<stmtType.breakCount>$ = $<stmtType.breakCount>1 + $<stmtType.breakCount>3;
            $<stmtType.continueList>$ = merge($<stmtType.continueList>1, $<stmtType.continueList>3);
            $<stmtType.breakList>$ = merge($<stmtType.breakList>1, $<stmtType.breakList>3);
          }
;

NN         : /* empty */{
            $$ = makelist(genIRForBranch(jmp, 0, 0, 0));
          }
;

stmt      : exp SEMI {
            $<stmtType.nextList>$ = 0;
            $<stmtType.continueCount>$ = 0;
            $<stmtType.breakCount>$ = 0;
            $<stmtType.continueList>$ = 0;
            $<stmtType.breakList>$ = 0;
          }
          | stmtblock {
            
            $<stmtType.nextList>$ = 0;
            $<stmtType.continueCount>$ = $<stmtType.continueCount>1;
            $<stmtType.breakCount>$ = $<stmtType.breakCount>1;
            $<stmtType.continueList>$ = $<stmtType.continueList>1;
            $<stmtType.breakList>$ = $<stmtType.breakList>1;
          }
          | RETURN exp SEMI {
            int temp;
            if($<value.valType>2 == 1){
              temp = newTemp();
              genIR(li, 0, $<value.temp>2, temp);
            }
            else{
              temp = normalizeExp((struct NSData *) &$2);
            }
            genIR(ret, temp, 0, 0);
            $<stmtType.continueCount>$ = 0;
            $<stmtType.continueList>$ = 0;
            $<stmtType.breakCount>$ = 0;
            $<stmtType.breakList>$ = 0;
            $<stmtType.nextList>$ = 0;
          }
          | IF LP exp RP MM stmt NN ELSE MM stmt {
            backpatch($<value.trueList>3, $5->next);
            backpatch($<value.falseList>3, $9->next);
            $<stmtType.nextList>$ = merge(merge($<stmtType.nextList>6, $7), $<stmtType.nextList>10);
            $<stmtType.continueCount>$ = $<stmtType.continueCount>6 + $<stmtType.continueCount>10;
            $<stmtType.breakCount>$ = $<stmtType.breakCount>6 + $<stmtType.breakCount>10;
            $<stmtType.continueList>$ = merge($<stmtType.continueList>6, $<stmtType.continueList>10);
            $<stmtType.breakList>$ = merge($<stmtType.breakList>6, $<stmtType.breakList>10);

          }
          | IF LP exp RP MM stmt {
            backpatch($<value.trueList>3, $5->next);
            $<stmtType.nextList>$ = merge($<value.falseList>3, $<stmtType.nextList>6);
            $<stmtType.continueCount>$ = $<stmtType.continueCount>6;
            $<stmtType.breakCount>$ = $<stmtType.breakCount>6;
            $<stmtType.continueList>$ = $<stmtType.continueList>6;
            $<stmtType.breakList>$ = $<stmtType.breakList>6;
          }
          | FOR LP exp SEMI MM exp SEMI MM exp NN RP MM stmt {
            backpatch($<value.trueList>6, $12->next);
            backpatch($10, $5->next);
            genIRForBranch(jmp, 0, 0, $8->next);
            backpatch($<stmtType.continueList>13, $8->next);
            $<stmtType.nextList>$ = merge($<value.falseList>6, $<stmtType.breakList>13);
            $<stmtType.continueCount>$ = 0;
            $<stmtType.continueList>$ = 0;
            $<stmtType.breakCount>$ = 0;
            $<stmtType.breakList>$ = 0;
          }
          | CONT SEMI {
            $<stmtType.continueCount>$ = 1;
            $<stmtType.continueList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            $<stmtType.breakCount>$ = 0;
            $<stmtType.breakList>$ = 0;
            $<stmtType.nextList>$ = 0;
            
          }
          | BREAK SEMI {
            $<stmtType.continueCount>$ = 0;
            $<stmtType.continueList>$ = 0;
            $<stmtType.breakCount>$ = 1;
            $<stmtType.breakList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            $<stmtType.nextList>$ = 0;
          }
;

defs      : /* empty */
          | TYPE decs SEMI defs
          | stspec defsextvars SEMI defs
          | stspec SEMI defs
;

defsextvars  : defsextvars COMMA ID {
            if(getsym($3) != 0) yyerror("wrong while declaration\n");
            else registerId($3, $<id>0, 0, 0, 0, 0, 0);
          }
          | ID {
            if(getsym($1) != 0) yyerror("wrong while declaration\n");
            else registerId($1, $<id>0, 0, 0, 0, 0, 0);
          }
;

sdefs     : sdefs TYPE sdecs SEMI {
            $$ = totalOffset;
          }
          | TYPE sdecs SEMI {
            $$ = totalOffset;
          }
;

sdecs     : sdecs COMMA ID {
            if(getsym($3) != 0) yyerror("wrong while declaration\n");
            else registerId($3, "int", 1, 1, 0, 0, 0);
          }
          | ID {
            if(getsym($1) != 0) yyerror("wrong while declaration\n");
            else registerId($1, "int", 1, 1, 0, 0, 0);
          }
;

decs      : var {
            if(getsym($<variable.id>1) != 0) yyerror("wrong while declaration\n");
            else registerId($<variable.id>1, "int", $<variable.width>1, $<variable.height>1, 0, 0, 0);
          }
          | decs COMMA var {
            if(getsym($<variable.id>3) != 0) yyerror("wrong while declaration\n");
            else registerId($<variable.id>3, "int", $<variable.width>3, $<variable.height>3, 0, 0, 0);
          }
          | decs COMMA ID BINARYOP_ASSIGN exps {
            if(getsym($3) != 0) yyerror("wrong while declaration\n");
            else {
              registerId($3, "int", 1, 1, 0, 0, 0);
              if($<value.valType>5 == 1){
                int temp = newTemp();
                genIR(li, 0, $<value.temp>5, temp);
                genIRForLS(swi, temp, 0, $3);
              } else {
                int temp = normalizeExp((struct NSData *) &$5);
                genIRForLS(swi, temp, 0, $3);
              }
            }
          }
          | ID BINARYOP_ASSIGN exps {
            if(getsym($1) != 0) yyerror("wrong while declaration\n");
            else {
              registerId($1, "int", 1, 1, 0, 0, 0);
              if($<value.valType>3 == 1){
                int temp = newTemp();
                genIR(li, 0, $<value.temp>3, temp);
                genIRForLS(swi, temp, 0, $1);
              } else {
                int temp = normalizeExp((struct NSData *) &$3);
                genIRForLS(swi, temp, 0, $1);
              }
            }
          }
          | decs COMMA varArray BINARYOP_ASSIGN LC args RC {
            if(getsym($<variable.id>3) != 0) yyerror("wrong while declaration\n");
            else {
              registerId($<variable.id>3, "int", $<variable.width>3, $<variable.height>3, 0, 0, 0);
              int i = 0;
              struct NSData* temp;
              if(($<variable.width>3 * $<variable.height>3) >= $6){
                for(i=$6-1;i >= 0 ;i--){
                  temp = NSPop();
                  if(temp->valType == 1){
                    int tempReg = newTemp();
                    genIR(li, 0, temp->temp, tempReg);
                    genIRForLS(swi, tempReg, i*4, $<variable.id>3);
                  }
                  else{
                    int tempReg = normalizeExp(temp);
                    genIRForLS(swi, tempReg, i*4, $<variable.id>3);
                  }
                }
              }
              else{
                yyerror("wrong while init array!\n");
              }
            }
          }
          | varArray BINARYOP_ASSIGN LC args RC {
            if(getsym($<variable.id>1) != 0) yyerror("wrong while declaration\n");
            else {
              registerId($<variable.id>1, "int", $<variable.width>1, $<variable.height>1, 0, 0, 0);
              int i = 0;
              struct NSData* temp;
              if(($<variable.width>1 * $<variable.height>1) >= $4){
                for(i=$4-1;i >= 0 ;i--){
                  temp = NSPop();
                  if(temp->valType == 1){
                    int tempReg = newTemp();
                    genIR(li, 0, temp->temp, tempReg);
                    genIRForLS(swi, tempReg, i*4, $<variable.id>1);
                  }
                  else{
                    int tempReg = normalizeExp(temp);
                    genIRForLS(swi, tempReg, i*4, $<variable.id>1);
                  }
                }
              }
              else{
                yyerror("wrong while init array!\n");
              }
            }
          }
;

var       : ID {
            $<variable.id>$ = $1;
            $<variable.width>$ = 1;
            $<variable.height>$ = 1;
          }
          | varArray{
            $$ = $1;
          }
;

varArray  : ID LB INT RB LB INT RB {
            $<variable.id>$ = $<variable.id>1;
            $<variable.width>$ = $3;
            $<variable.height>$ = $6;
          }
          | ID LB INT RB {
            $<variable.id>$ = $1;
            $<variable.width>$ = $3;
            $<variable.height>$ = 1;
          }
;

exp       : /* empty */{
            $<value.valType>$ = 0;
          }
          | exps {
            $$ = $1;
          }
;

exps      : exps BINARYOP_MUL exps{
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              $<value.valType>$ = 1;
              $<value.temp>$ = $<value.temp>1 * $<value.temp>3;
            }
            else if($<value.valType>1 == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&$3);
              if($<value.temp>1 == 1){
                $<value.valType>$ = 2;
                $<value.temp>$ = temp;
              }
              else if($<value.temp>1 == 0){
                $<value.valType>$ = 1;
                $<value.temp>$ = 0;
              }
              else{
                result = newTemp();
                genIR(muli, temp, $<value.temp>1, result);
                $<value.valType>$ = 2;
                $<value.temp>$ = result;
              }
            }
            else if($<value.valType>3 == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&$1);
              if($<value.temp>3 == 1){
                $<value.valType>$ = 2;
                $<value.temp>$ = temp;
              }
              else if($<value.temp>3 == 0){
                $<value.valType>$ = 1;
                $<value.temp>$ = 0;
              }
              else{
                result = newTemp();
                genIR(muli, temp, $<value.temp>3, result);
                $<value.valType>$ = 2;
                $<value.temp>$ = result;
              }
            }
            else{
              int temp1;
              int temp2;
              int result;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              result = newTemp();
              genIR(mul, temp1, temp2, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
          }
          | exps BINARYOP_DIV exps {
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              $<value.valType>$ = 1;
              $<value.temp>$ = $<value.temp>1 / $<value.temp>3;
            }
            else if($<value.valType>1 == 1){
              int temp;
              int temp2;
              int result;
              temp = normalizeExp((struct NSData *)&$3);
              if($<value.temp>1 == 0){
                $<value.valType>$ = 1;
                $<value.temp>$ = 0;
              }
              else{
                temp2 = newTemp();
                result = newTemp();
                genIR(li, 0, $<value.temp>1, temp2);
                genIR(opdiv, temp2, temp, result);
                $<value.valType>$ = 2;
                $<value.temp>$ = result;
              }
            }
            else if($<value.valType>3 == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&$1);
              if($<value.temp>3 == 1){
                $<value.valType>$ = 2;
                $<value.temp>$ = temp;
              }
              else if($<value.temp>3 == 0){
                yyerror("wrong while do div");
              }
              else{
                result = newTemp();
                genIR(opdivi, temp, $<value.temp>3, result);
                $<value.valType>$ = 2;
                $<value.temp>$ = result;
              }
            }
            else{
              int temp1;
              int temp2;
              int result;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              result = newTemp();
              genIR(opdiv, temp1, temp2, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
          }
          | exps BINARYOP_MOD exps {
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              $<value.valType>$ = 1;
              $<value.temp>$ = $<value.temp>1 % $<value.temp>3;
            }
            else if($<value.valType>1 == 1){
              int temp;
              int temp2;
              int result;
              temp = normalizeExp((struct NSData *)&$3);
              temp2 = newTemp();
              result = newTemp();
              genIR(li, 0, $<value.temp>1, temp2);
              genIR(remi, temp2, temp, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
            else if($<value.valType>3 == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&$1);
              result = newTemp();
              genIR(remi, temp, $<value.temp>3, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
            else{
              int temp1;
              int temp2;
              int result;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              result = newTemp();
              genIR(rem, temp1, temp2, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
          }
          | exps BINARYOP_ADD exps {
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              $<value.valType>$ = 1;
              $<value.temp>$ = $<value.temp>1 + $<value.temp>3;
            }
            else if($<value.valType>1 == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&$3);
              if($<value.temp>1 == 0){
                $<value.valType>$ = 2;
                $<value.temp>$ = temp;
              }
              else{
                result = newTemp();
                genIR(addi, temp, $<value.temp>1, result);
                $<value.valType>$ = 2;
                $<value.temp>$ = result;
              }
            }
            else if($<value.valType>3 == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&$1);
              if($<value.temp>3 == 0){
                $<value.valType>$ = 2;
                $<value.temp>$ = temp;
              }
              else{
                result = newTemp();
                genIR(addi, temp, $<value.temp>3, result);
                $<value.valType>$ = 2;
                $<value.temp>$ = result;
              }
            }
            else{
              int temp1;
              int temp2;
              int result;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              result = newTemp();
              genIR(add, temp1, temp2, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
          }
          | exps MIN exps {
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              $<value.valType>$ = 1;
              $<value.temp>$ = $<value.temp>1 - $<value.temp>3;
            }
            else if($<value.valType>1 == 1){
              int temp;
              int temp2;
              int result;
              temp = normalizeExp((struct NSData *)&$3);
              temp2 = newTemp();
              result = newTemp();
              genIR(li, 0, $<value.temp>1, temp2);
              genIR(subi, temp2, temp, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
            else if($<value.valType>3 == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&$1);
              if($<value.temp>3 == 0){
                $<value.valType>$ = 2;
                $<value.temp>$ = temp;
              }
              else{
                result = newTemp();
                genIR(subi, temp, $<value.temp>3, result);
                $<value.valType>$ = 2;
                $<value.temp>$ = result;
              }
            }
            else{
              int temp1;
              int temp2;
              int result;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              result = newTemp();
              genIR(sub, temp1, temp2, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
          }
          | exps BINARYOP_SHL exps {
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              $<value.valType>$ = 1;
              $<value.temp>$ = $<value.temp>1 << $<value.temp>3;
            }
            else if($<value.valType>1 == 1){
              int temp;
              int temp2;
              int result;
              temp = normalizeExp((struct NSData *)&$3);
              temp2 = newTemp();
              result = newTemp();
              genIR(li, 0, $<value.temp>1, temp2);
              genIR(shli, temp2, temp, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
            else if($<value.valType>3 == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&$1);
              if($<value.temp>3 == 0){
                $<value.valType>$ = 2;
                $<value.temp>$ = temp;
              }
              else{
                result = newTemp();
                genIR(shli, temp, $<value.temp>3, result);
                $<value.valType>$ = 2;
                $<value.temp>$ = result;
              }
            }
            else{
              int temp1;
              int temp2;
              int result;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              result = newTemp();
              genIR(shl, temp1, temp2, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
          }
          | exps BINARYOP_SHR exps {
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              $<value.valType>$ = 1;
              $<value.temp>$ = $<value.temp>1 >> $<value.temp>3;
            }
            else if($<value.valType>1 == 1){
              int temp;
              int temp2;
              int result;
              temp = normalizeExp((struct NSData *)&$3);
              temp2 = newTemp();
              result = newTemp();
              genIR(li, 0, $<value.temp>1, temp2);
              genIR(shri, temp2, temp, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
            else if($<value.valType>3 == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&$1);
              if($<value.temp>3 == 0){
                $<value.valType>$ = 2;
                $<value.temp>$ = temp;
              }
              else{
                result = newTemp();
                genIR(shri, temp, $<value.temp>3, result);
                $<value.valType>$ = 2;
                $<value.temp>$ = result;
              }
            }
            else{
              int temp1;
              int temp2;
              int result;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              result = newTemp();
              genIR(shr, temp1, temp2, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
          }
          | exps BINARYOP_GT exps {
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              if($<value.temp>1 > $<value.temp>3){
                $<value.trueList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
              else{
                $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
            }
            else if($<value.valType>1 == 1){
              int temp;
              int temp2;
              temp = normalizeExp((struct NSData *)&$3);
              temp2 = newTemp();
              genIR(li, 0, $<value.temp>1, temp2);
              $<value.trueList>$ = makelist(genIRForBranch(jgti, temp2, temp, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            else if($<value.valType>3 == 1){
              int temp;
              temp = normalizeExp((struct NSData *)&$1);
              $<value.trueList>$ = makelist(genIRForBranch(jgti, temp, $<value.temp>3, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            else{
              int temp1;
              int temp2;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              $<value.trueList>$ = makelist(genIRForBranch(jgt, temp1, temp2, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
          }
          | exps BINARYOP_NLT exps {
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              if($<value.temp>1 >= $<value.temp>3){
                $<value.trueList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
              else{
                $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
            }
            else if($<value.valType>1 == 1){
              int temp;
              int temp2;
              temp = normalizeExp((struct NSData *)&$3);
              temp2 = newTemp();
              genIR(li, 0, $<value.temp>1, temp2);
              $<value.trueList>$ = makelist(genIRForBranch(jgei, temp2, temp, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            else if($<value.valType>3 == 1){
              int temp;
              temp = normalizeExp((struct NSData *)&$1);
              $<value.trueList>$ = makelist(genIRForBranch(jgei, temp, $<value.temp>3, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            else{
              int temp1;
              int temp2;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              $<value.trueList>$ = makelist(genIRForBranch(jge, temp1, temp2, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
          }
          | exps BINARYOP_LT exps {
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              if($<value.temp>1 < $<value.temp>3){
                $<value.trueList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
              else{
                $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
            }
            else if($<value.valType>1 == 1){
              int temp;
              int temp2;
              temp = normalizeExp((struct NSData *)&$3);
              temp2 = newTemp();
              genIR(li, 0, $<value.temp>1, temp2);
              $<value.trueList>$ = makelist(genIRForBranch(jlti, temp2, temp, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            else if($<value.valType>3 == 1){
              int temp;
              temp = normalizeExp((struct NSData *)&$1);
              $<value.trueList>$ = makelist(genIRForBranch(jlti, temp, $<value.temp>3, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            else{
              int temp1;
              int temp2;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              $<value.trueList>$ = makelist(genIRForBranch(jlt, temp1, temp2, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
          }
          | exps BINARYOP_NGT exps {
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              if($<value.temp>1 <= $<value.temp>3){
                $<value.trueList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
              else{
                $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
            }
            else if($<value.valType>1 == 1){
              int temp;
              int temp2;
              temp = normalizeExp((struct NSData *)&$3);
              temp2 = newTemp();
              genIR(li, 0, $<value.temp>1, temp2);
              $<value.trueList>$ = makelist(genIRForBranch(jlei, temp2, temp, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            else if($<value.valType>3 == 1){
              int temp;
              temp = normalizeExp((struct NSData *)&$1);
              $<value.trueList>$ = makelist(genIRForBranch(jlei, temp, $<value.temp>3, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            else{
              int temp1;
              int temp2;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              $<value.trueList>$ = makelist(genIRForBranch(jle, temp1, temp2, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
          }
          | exps BINARYOP_EQ exps {
            
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              if($<value.temp>1 == $<value.temp>3){
                $<value.trueList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
                $<value.falseList>$ = 0;
              }
              else{
                $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
                $<value.falseList>$ = 0;
              }
            }
            else if($<value.valType>1 == 1){
              int temp;
              temp = normalizeExp((struct NSData *)&$3);
              $<value.trueList>$ = makelist(genIRForBranch(jei, temp, $<value.temp>1, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            else if($<value.valType>3 == 1){
              int temp;
              temp = normalizeExp((struct NSData *)&$1);
              $<value.trueList>$ = makelist(genIRForBranch(jei, temp, $<value.temp>3, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            else{
              int temp1;
              int temp2;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              $<value.trueList>$ = makelist(genIRForBranch(je, temp1, temp2, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            $<value.valType>$ = 0;
          }
          | exps BINARYOP_NEQ exps {
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              if($<value.temp>1 != $<value.temp>3){
                $<value.trueList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
              else{
                $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
            }
            else if($<value.valType>1 == 1){
              int temp;
              temp = normalizeExp((struct NSData *)&$3);
              $<value.trueList>$ = makelist(genIRForBranch(jnei, temp, $<value.temp>1, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            else if($<value.valType>3 == 1){
              int temp;
              temp = normalizeExp((struct NSData *)&$1);
              $<value.trueList>$ = makelist(genIRForBranch(jnei, temp, $<value.temp>3, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            else{
              int temp1;
              int temp2;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              $<value.trueList>$ = makelist(genIRForBranch(jne, temp1, temp2, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            $<value.valType>$ = 0;
          }
          | exps BINARYOP_BAND exps {
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              $<value.valType>$ = 1;
              $<value.temp>$ = $<value.temp>1 & $<value.temp>3;
            }
            else if($<value.valType>1 == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&$3);
              result = newTemp();
              genIR(bandi, temp, $<value.temp>1, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
            else if($<value.valType>3 == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&$1);
              result = newTemp();
              genIR(bandi, temp, $<value.temp>3, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
            else{
              int temp1;
              int temp2;
              int result;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              result = newTemp();
              genIR(band, temp1, temp2, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
          }
          | exps BINARYOP_BXOR exps {
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              $<value.valType>$ = 1;
              $<value.temp>$ = $<value.temp>1 ^ $<value.temp>3;
            }
            else if($<value.valType>1 == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&$3);
              result = newTemp();
              genIR(bxori, temp, $<value.temp>1, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
            else if($<value.valType>3 == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&$1);
              result = newTemp();
              genIR(bxori, temp, $<value.temp>3, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
            else{
              int temp1;
              int temp2;
              int result;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              result = newTemp();
              genIR(bxor, temp1, temp2, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
          }
          | exps BINARYOP_BOR exps {
            if($<value.valType>1 == 1 && $<value.valType>3 == 1){
              $<value.valType>$ = 1;
              $<value.temp>$ = $<value.temp>1 | $<value.temp>3;
            }
            else if($<value.valType>1 == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&$3);
              result = newTemp();
              genIR(bori, temp, $<value.temp>1, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
            else if($<value.valType>3 == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&$1);
              result = newTemp();
              genIR(bori, temp, $<value.temp>3, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
            else{
              int temp1;
              int temp2;
              int result;
              temp1 = normalizeExp((struct NSData *)&$1);
              temp2 = normalizeExp((struct NSData *)&$3);
              result = newTemp();
              genIR(bor, temp1, temp2, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
          }
          | exps BINARYOP_LAND MM exps {
            backpatch($<value.trueList>1, $3->next);
            $<value.trueList>$ = $<value.trueList>4;
            $<value.falseList>$ = merge($<value.falseList>1, $<value.falseList>4);
            $<value.nextList>$ = 0;
            $<value.valType>$ = 0;
          }
          | exps BINARYOP_LOR MM exps {
            backpatch($<value.falseList>1, $3->next);
            $<value.trueList>$ = merge($<value.trueList>1, $<value.trueList>4);
            $<value.falseList>$ = $<value.falseList>4;
            $<value.nextList>$ = 0;
            $<value.valType>$ = 0;
          }
          | exps BINARYOP_ASSIGN exps {
            if($<value.valType>1 == 3 || $<value.valType>1 == 4){
              int temp;
              if($<value.valType>3 == 1){
                temp = newTemp();
                genIR(li, 0, $<value.temp>3, temp);
                if($<value.valType>1 == 3) genIRForLS(swi, temp, $<value.offset>1, $<value.id>1);
                else genIRForLS(sw, temp, $<value.offset>1, $<value.id>1);
                $<value.valType>$ = 1;
                $<value.temp>$ = $<value.temp>3;
              }
              else{
                temp = normalizeExp((struct NSData *) &$3);
                if($<value.valType>1 == 3) genIRForLS(swi, temp, $<value.offset>1, $<value.id>1);
                else genIRForLS(sw, temp, $<value.offset>1, $<value.id>1);
                $<value.valType>$ = 2;
                $<value.temp>$ = temp;
              }
            }
            else {
              yyerror("wrong while assign!\n");
            }
          }
          | exps BINARYOP_MULA exps {
            if($<value.valType>1 == 3 || $<value.valType>1 == 4){
              int temp1;
              int temp2;
              int temp;
              temp1 = normalizeExp((struct NSData *) &$1);
              if($<value.valType>3 == 1){
                temp = newTemp();
                genIR(muli, temp1, $<value.temp>3, temp);
              }
              else{
                temp = newTemp();
                temp2 = normalizeExp((struct NSData *) &$3);
                genIR(mul, temp1, temp2, temp);
              }
              if($<value.valType>1 == 3) genIRForLS(swi, temp, $<value.offset>1, $<value.id>1);
              else genIRForLS(sw, temp, $<value.offset>1, $<value.id>1);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp;
            }
            else {
              yyerror("wrong while assign!\n");
            }
          }
          | exps BINARYOP_DIVA exps {
            if($<value.valType>1 == 3 || $<value.valType>1 == 4){
              int temp1;
              int temp2;
              int temp;
              temp1 = normalizeExp((struct NSData *) &$1);
              if($<value.valType>3 == 1){
                temp = newTemp();
                genIR(opdivi, temp1, $<value.temp>3, temp);
              }
              else{
                temp = newTemp();
                temp2 = normalizeExp((struct NSData *) &$3);
                genIR(opdiv, temp1, temp2, temp);
              }
              if($<value.valType>1 == 3) genIRForLS(swi, temp, $<value.offset>1, $<value.id>1);
              else genIRForLS(sw, temp, $<value.offset>1, $<value.id>1);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp;
            }
            else {
              yyerror("wrong while assign!\n");
            }
          }
          | exps BINARYOP_ADDA exps {
            if($<value.valType>1 == 3 || $<value.valType>1 == 4){
              int temp1;
              int temp2;
              int temp;
              temp1 = normalizeExp((struct NSData *) &$1);
              if($<value.valType>3 == 1){
                temp = newTemp();
                genIR(addi, temp1, $<value.temp>3, temp);
              }
              else{
                temp = newTemp();
                temp2 = normalizeExp((struct NSData *) &$3);
                genIR(add, temp1, temp2, temp);
              }
              if($<value.valType>1 == 3) genIRForLS(swi, temp, $<value.offset>1, $<value.id>1);
              else genIRForLS(sw, temp, $<value.offset>1, $<value.id>1);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp;
            }
            else {
              yyerror("wrong while assign!\n");
            }
          }
          | exps BINARYOP_MINA exps {
            if($<value.valType>1 == 3 || $<value.valType>1 == 4){
              int temp1;
              int temp2;
              int temp;
              temp1 = normalizeExp((struct NSData *) &$1);
              if($<value.valType>3 == 1){
                temp = newTemp();
                genIR(subi, temp1, $<value.temp>3, temp);
              }
              else{
                temp = newTemp();
                temp2 = normalizeExp((struct NSData *) &$3);
                genIR(sub, temp1, temp2, temp);
              }
              if($<value.valType>1 == 3) genIRForLS(swi, temp, $<value.offset>1, $<value.id>1);
              else genIRForLS(sw, temp, $<value.offset>1, $<value.id>1);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp;
            }
            else {
              yyerror("wrong while assign!\n");
            }
          }
          | exps BINARYOP_BANDA exps {
            if($<value.valType>1 == 3 || $<value.valType>1 == 4){
              int temp1;
              int temp2;
              int temp;
              temp1 = normalizeExp((struct NSData *) &$1);
              if($<value.valType>3 == 1){
                temp = newTemp();
                genIR(bandi, temp1, $<value.temp>3, temp);
              }
              else{
                temp = newTemp();
                temp2 = normalizeExp((struct NSData *) &$3);
                genIR(band, temp1, temp2, temp);
              }
              if($<value.valType>1 == 3) genIRForLS(swi, temp, $<value.offset>1, $<value.id>1);
              else genIRForLS(sw, temp, $<value.offset>1, $<value.id>1);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp;
            }
            else {
              yyerror("wrong while assign!\n");
            }
          }
          | exps BINARYOP_BXORA exps {
            if($<value.valType>1 == 3 || $<value.valType>1 == 4){
              int temp1;
              int temp2;
              int temp;
              temp1 = normalizeExp((struct NSData *) &$1);
              if($<value.valType>3 == 1){
                temp = newTemp();
                genIR(bxori, temp1, $<value.temp>3, temp);
              }
              else{
                temp = newTemp();
                temp2 = normalizeExp((struct NSData *) &$3);
                genIR(bxor, temp1, temp2, temp);
              }
              if($<value.valType>1 == 3) genIRForLS(swi, temp, $<value.offset>1, $<value.id>1);
              else genIRForLS(sw, temp, $<value.offset>1, $<value.id>1);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp;
            }
            else {
              yyerror("wrong while assign!\n");
            }
          }
          | exps BINARYOP_BORA exps {
            if($<value.valType>1 == 3 || $<value.valType>1 == 4){
              int temp1;
              int temp2;
              int temp;
              temp1 = normalizeExp((struct NSData *) &$1);
              if($<value.valType>3 == 1){
                temp = newTemp();
                genIR(bori, temp1, $<value.temp>3, temp);
              }
              else{
                temp = newTemp();
                temp2 = normalizeExp((struct NSData *) &$3);
                genIR(bor, temp1, temp2, temp);
              }
              if($<value.valType>1 == 3) genIRForLS(swi, temp, $<value.offset>1, $<value.id>1);
              else genIRForLS(sw, temp, $<value.offset>1, $<value.id>1);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp;
            }
            else {
              yyerror("wrong while assign!\n");
            }
          }
          | exps BINARYOP_SHLA exps {
            if($<value.valType>1 == 3 || $<value.valType>1 == 4){
              int temp1;
              int temp2;
              int temp;
              temp1 = normalizeExp((struct NSData *) &$1);
              if($<value.valType>3 == 1){
                temp = newTemp();
                genIR(shli, temp1, $<value.temp>3, temp);
              }
              else{
                temp = newTemp();
                temp2 = normalizeExp((struct NSData *) &$3);
                genIR(shl, temp1, temp2, temp);
              }
              if($<value.valType>1 == 3) genIRForLS(swi, temp, $<value.offset>1, $<value.id>1);
              else genIRForLS(sw, temp, $<value.offset>1, $<value.id>1);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp;
            }
            else {
              yyerror("wrong while assign!\n");
            }
          }
          | exps BINARYOP_SHRA exps {
            if($<value.valType>1 == 3 || $<value.valType>1 == 4){
              int temp1;
              int temp2;
              int temp;
              temp1 = normalizeExp((struct NSData *) &$1);
              if($<value.valType>3 == 1){
                temp = newTemp();
                genIR(shri, temp1, $<value.temp>3, temp);
              }
              else{
                temp = newTemp();
                temp2 = normalizeExp((struct NSData *) &$3);
                genIR(shr, temp1, temp2, temp);
              }
              if($<value.valType>1 == 3) genIRForLS(swi, temp, $<value.offset>1, $<value.id>1);
              else genIRForLS(sw, temp, $<value.offset>1, $<value.id>1);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp;
            }
            else {
              yyerror("wrong while assign!\n");
            }
          }
          | MIN exps %prec UNARYOP_LNOT {
            if($<value.valType>2 == 1){
              $<value.valType>$ = 1;
              $<value.temp>$ = - $<value.temp>2;
            }
            else {
              int temp;
              int result;
              temp = normalizeExp((struct NSData*) &$2);
              result = newTemp();
              genIR(neg, temp, 0, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
          }
          | UNARYOP_LNOT exps{
            $<value.trueList>$ = $<value.falseList>2;
            $<value.falseList>$ = $<value.trueList>2;
            $<value.nextList>$ = 0;
            $<value.valType>$ = 0;
          }
          | UNARYOP_INCR exps {
            if($<value.valType>2 == 3 || $<value.valType>2 == 4){
              int temp;
              int result;
              temp = normalizeExp((struct NSData*) &$2);
              result = newTemp();
              genIR(addi, temp, 1, result);
              if($<value.valType>2 == 3) genIRForLS(swi, result, $<value.offset>2, $<value.id>2);
              else genIRForLS(sw, result, $<value.offset>2, $<value.id>2);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
            else {
              yyerror("wrong while do ++!\n");
            }
          }
          | UNARYOP_DECR exps {
            if($<value.valType>2 == 3 || $<value.valType>2 == 4){
              int temp;
              int result;
              temp = normalizeExp((struct NSData*) &$2);
              result = newTemp();
              genIR(subi, temp, 1, result);
              if($<value.valType>2 == 3) genIRForLS(swi, result, $<value.offset>2, $<value.id>2);
              else genIRForLS(sw, result, $<value.offset>2, $<value.id>2);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
            else {
              yyerror("wrong while do ++!\n");
            }
          }
          | UNARYOP_BNOT exps {
            if($<value.valType>2 == 1){
              $<value.valType>$ = 1;
              $<value.temp>$ = ~$<value.temp>2;
            }
            else {
              int temp;
              int result;
              temp = normalizeExp((struct NSData*) &$2);
              result = newTemp();
              genIR(bnot, temp, 0, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
          }
          | LP exps RP {
            $$ = $2;
          }
          | ID LP args RP  {
            int i;
            struct NSData* temp;
            if(strcmp($1, "read") == 0){
              int input = newTemp();
              temp = getNSFromBottom();
              if(temp == 0) yyerror("unmatch param\n");
              else {
                genIR(read, 0, 0, input);
                if(temp->valType == 3 || temp->valType == 4){
                  if($<value.valType>1 == 3) genIRForLS(swi, input, temp->offset, temp->id);
                  else genIRForLS(sw, input, temp->offset, temp->id);
                }
                else {
                  yyerror("wrong while read args!\n");
                }
              }
            }
            else if(strcmp($1, "write") == 0){
              int output;
              temp = getNSFromBottom();
              if(temp == 0) yyerror("unmatch param\n");
              else {
                if(temp->valType == 1){
                  output = newTemp();
                  genIR(li, 0, temp->temp, output);
                } 
                else{
                  if(temp->valType == 3 || temp->valType == 3){
                    if(strcmp(getsym(temp->id)->type, "int") != 0) yyerror("wrong while pass parameter\n");
                  }
                  output = normalizeExp(temp);
                } 
                genIR(write, 0, 0, output);
              }
            }
            else{
              struct symrec *fun = getsym($1);
              struct symrec *parameter;
              if(fun != 0){
                if(strcmp(getsym($1)->type, "func") != 0) yyerror("must be func!\n");
                else {
                  parameter = fun->param; 
                  struct symrec *ptr;
                  int paramNumber = 0;
                  for (ptr = parameter; ptr != (struct symrec *)0 && ptr->name != 0; ptr = (struct symrec *)ptr->next){
                    paramNumber++;
                  }
                  if(paramNumber != $3) yyerror("unmatch param\n");
                  else{ 
                    for(i=$3-1;i >= 0 ;i--){
                      temp = getNSFromBottom();
                      if(temp == 0) yyerror("unmatch param\n");
                      else{
                        if(temp->valType == 1){
                          int tempReg = newTemp();
                          genIR(li, 0, temp->temp, tempReg);
                          genIRForLS(param, tempReg, 0, parameter->name);
                        }
                        else{
                          if(temp->valType == 3 || temp->valType == 3){
                            if(strcmp(getsym(temp->id)->type, "int") != 0) yyerror("wrong while pass parameter\n");
                          }
                          int tempReg = normalizeExp(temp);
                          genIRForLS(param, tempReg, 0, parameter->name);
                        }
                        parameter = parameter->next;
                      }
                    }
                  }
                  int tempReg = newTemp();
                  genIRForBranch(call, tempReg, 0, fun->entry);
                  $<value.valType>$ = 2;
                  $<value.temp>$ = tempReg;
                }
              }
              else{
                yyerror("wrong while call func!\n");
              }
            }
            if(!NSIsEmpty()) yyerror("param number unmatch!\n");
          }/*this is func*/
          | ID arrs {
            if(strcmp(getsym($1)->type, "int") != 0) yyerror("must be int array!\n");
            else if($<value.valType>2 == 1){
              $<value.valType>$ = 3;
              $<value.id>$ = $1;
              $<value.offset>$ = $<value.temp>2;
            }
            else if($<value.valType>2 == 2){
              $<value.valType>$ = 4;
              $<value.id>$ = $1;
              $<value.offset>$ = $<value.temp>2;
            }
            else{
              yyerror("wrong while array reference\n");
            }
          }
          | ID DOT ID{
            struct symrec * os;
            $<value.valType>$ = 3;
            struct symrec * structVar = getsym($1);
            if(structVar == 0){
              yyerror("wrong while using struct id!\n");
            }
            else {
              struct symrec * base = getsym(structVar->type);
              if(base == 0) yyerror("wrong while using struct id!\n");
              else if((base->type, "struct") != 0) yyerror("must be struct!\n");
              else {
                os = getsymWithinScope($3, base->scope);
              }
              $<value.id>$ = $1;
              $<value.offset>$ = os->offset;
            }
          }
          | INT {
            $<value.valType>$ = 1;
            $<value.temp>$ = $1;
          }
;

MM         : /* empty */{
            $$ = InterR->tail;
          }
;

arrs      : /* empty */{
            $<value.valType>$ = 1;
            $<value.temp>$ = 0;
          }
          | LB exps RB {
            if($<value.valType>2 == 1){
              $<value.valType>$ = 1;
              $<value.temp>$ = $<value.temp>2*4;
            }
            else{
              $<value.valType>$ = 2;
              int temp = normalizeExp((struct NSData*) &$2);
              int result = newTemp();
              genIR(muli, temp, 4, result);
              $<value.temp>$ = result;
            }
          }
          | LB exps RB LB exps RB {
            struct symrec * array = getsym($<id>0);
            if(array == 0) yyerror("wrong while do arrs\n");
            else if($<value.valType>2 == 1 && $<value.valType>5 == 1){
              $<value.valType>$ = 1;
              $<value.temp>$ = array->width * $<value.temp>2 * 4 + $<value.temp>5 * 4;
            }
            else if($<value.valType>5 == 1){
              int temp = normalizeExp((struct NSData *) &$2);
              int midResult = newTemp();
              int result = newTemp();
              genIR(muli, temp, array->width * 4, midResult);
              genIR(addi, midResult, $<value.temp>5 * 4, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
            else if($<value.valType>2 == 1){
              int temp = normalizeExp((struct NSData *) &$5);
              int midResult = newTemp();
              int result = newTemp();
              genIR(muli, temp, 4, midResult);
              genIR(add, midResult, array->width * 4 * $<value.temp>2, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
            else{
              int temp1 = normalizeExp((struct NSData *) &$2);
              int temp2 = normalizeExp((struct NSData *) &$5);
              int midResult1 = newTemp();
              int midResult2 = newTemp();
              int result = newTemp();
              genIR(muli, temp1, array->width * 4, midResult1);
              genIR(muli, temp2, 4, midResult2);
              genIR(add, midResult1, midResult2, result);
              $<value.valType>$ = 2;
              $<value.temp>$ = result;
            }
          }
;

args      : args COMMA exp{
            NSPush((struct NSData *)&$3);
            $$ = $1 + 1;
          }
          | exp {
            NSPush((struct NSData *)&$1);
            $$ = 1;
          }
;

%%
/*=========================================================================
MAIN
/=========================================================================*/
int main( int argc, char *argv[] )
{
  extern FILE *yyin;
  ++argv;
  --argc;
  yyin = fopen(argv[0], "r");
  ++argv;
  --argc;
  yyout = fopen(argv[0], "w");
  IRout = fopen("InterCode", "w");
  // yydebug = 1;
  errors = 0;
  initInitR();
  initInterR();
  yyparse();
  endIR(InitR);
  endIR(InterR);
  if(checkST() == 0) yyerror("no main function!\n");
  if (errors == 0) {
    printf("Parse Completed\n");
    printST();
    markBasicBlock(InterR);
    printf("%s\n", "===========================================================");
    printIR(InitR);
    printf("%s\n", "===========================================================");
    printIR(InterR);
    printf("%s\n", "===========================================================");
    genData();
    printf("%s\n", "===========================================================");
    patchData();
    printf("%s\n", "===========================================================");
    CodeGenerate();




  }
  
  return 0;
}
/*=========================================================================
YYERROR
/=========================================================================*/
int yyerror ( char *s ) /* Called by yyparse on error */
{
  errors++;
  printf("%s\n", "=========================================================================");
  printf("%s\n", s);
  printf("%d\n", yychar);
  return 0;
}
/**************************** End Grammar File ***************************/