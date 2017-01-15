%{/*************************************************************************
Compiler for the Simple language
***************************************************************************/
/*=========================================================================
C Libraries, Symbol Table, Code Generator & other C code
=========================================================================*/
#include <stdio.h> /* For I/O */
#include <stdlib.h> /* For malloc here and in symbol table */
#include <string.h> /* For strcmp in symbol table */
#include "ST.h" /* Symbol Table */
#include "Quad.h" /* Quad Code */
#include "branchList.h" /*branch List For backpatching */
#include "numStack.h" /* numStack Code */
#include "tools.h" /* tools Code */
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
=========================================================================*/

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
    int valType; /*can be 0:empty, 1:int, 2:temp*/
    // int intval;
    int temp;
    // char* id;
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

}
/*=========================================================================
TOKENS
=========================================================================*/
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
%token BINARYOP_MODA
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
=========================================================================*/
%right BINARYOP_ASSIGN BINARYOP_MULA BINARYOP_DIVA BINARYOP_MODA BINARYOP_ADDA BINARYOP_MINA BINARYOP_BANDA BINARYOP_BXORA BINARYOP_BORA BINARYOP_SHLA BINARYOP_SHRA
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
=========================================================================*/
%type<variable> varArray var
%type<value> exps exp arrs
%type<intval> args
%type<funcType> func
%type<inst> MM 
%type<nextlist> NN stmt
%type<id> stspec
%type<offset> sdefs


/*=========================================================================
GRAMMAR RULES for the Simple language
=========================================================================*/
%%

program   : extdefs
;

extdefs   : /* empty */
          | extdef extdefs
;

extdef    : TYPE extvars SEMI /*但是这里理论上按照原来的规则也是要补的,但是感觉是元规则错了,c语言中int;这是啥啊*/
          | stspec sextvars SEMI
          | stspec SEMI /*这里是在将sextvars规则转换之后的补充，用于补充empty情况*/
          | TYPE func stmtblock {
            registerId($<funcType.id>2, "func", 0, 0, subLevel(), $<funcType.beforeEntry>2->next, $<funcType.param>2);
          }
;

sextvars  : sextvars COMMA ID {
            registerId($3, $<id>0, 0, 0, 0, 0, 0);
          }
          | ID {
            registerId($1, $<id>0, 0, 0, 0, 0, 0);
          }
;

extvars   : extvars COMMA var {
            registerId($<variable.id>3, "int", $<variable.width>3, $<variable.height>3, 0, 0, 0);
          }
          | extvars COMMA ID BINARYOP_ASSIGN exps{
            registerId($3, "int", 1, 1, 0, 0, 0);
            if($<value.valType>5 == 1){
              int temp = newTemp();
              genIR(li, 0, $<value.temp>5, temp);
              genIRForLS(sw, temp, 0, $3);
            } else {
              genIRForLS(sw, $<value.temp>5, 0, $3);
            }
          }
          | ID BINARYOP_ASSIGN exps {
            registerId($1, "int", 1, 1, 0, 0, 0);
            if($<value.valType>3 == 1){
              int temp = newTemp();
              genIR(li, 0, $<value.temp>3, temp);
              genIRForLS(swi, temp, 0, $1);
            } else {
              genIRForLS(swi, $<value.temp>3, 0, $1);
            }
          }
          | extvars COMMA varArray BINARYOP_ASSIGN LC args RC
          | varArray BINARYOP_ASSIGN LC args RC {
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
                else if(temp->valType == 2){
                  genIRForLS(swi, temp->temp, i*4, $<variable.id>1);
                }
              }
            }
          }
          | var {
            registerId($<variable.id>1, "int", $<variable.width>1, $<variable.height>1, 0, 0, 0);
          }
;

stspec    : STRUCT ID LC {addLevel();} sdefs RC{
            registerId($2, "struct", $5, 0, subLevel(), 0, 0);
            $$ = $2;
          }
          | STRUCT LC {addLevel();} sdefs RC{
            char * tempID = (char *) malloc(sizeof(char)*9);
            sprintf(tempID, "%d", getRandomNumber());
            registerId(tempID, "struct", $4, 0, subLevel(), 0, 0);
            $$ = tempID;
          } /*在没有ID的情况下可能需要随机分配一个?*/
          | STRUCT ID {
            $$ = $2;
          }
;

func      : ID LP {addLevel();} paras RP{
            $<funcType.id>$ = $1;
            $<funcType.param>$ = sym_table;
            $<funcType.beforeEntry>$ = IR->tail;
          }
;

paras     : /* empty */
          | TYPE ID COMMA paras {
            registerId($2, "int", 1, 1, 0, 0, 0);
          }
          | TYPE ID {
            registerId($2, "int", 1, 1, 0, 0, 0);
          }
;

stmtblock : LC defs stmts RC
;

stmts     : /* empty */
          | stmt stmts
;

stmt      : exp SEMI
          | stmtblock
          | RETURN exp SEMI
          | IF LP exp RP MM stmt {
            backpatch($<value.trueList>3, $5->next);
            $$ = merge($<value.falseList>3, $6);
          }
          | IF LP exp RP MM stmt NN ELSE MM stmt {
            backpatch($<value.trueList>3, $5->next);
            backpatch($<value.trueList>3, $9->next);
            $$ = merge(merge($6, $7), $10);
          }
          | FOR LP exp SEMI exp SEMI exp RP stmt
          | CONT SEMI
          | BREAK SEMI
;

defs      : /* empty */
          | TYPE decs SEMI defs
          | stspec sdecs SEMI defs
;

sdefs     : sdefs TYPE sdecs SEMI {
            $$ = totalOffset;
          }
          | TYPE sdecs SEMI {
            $$ = totalOffset;
          }
;

sdecs     : sdecs COMMA ID {
            registerId($3, "int", 1, 1, 0, 0, 0);
          }
          | ID {
            registerId($1, "int", 1, 1, 0, 0, 0);
          }
;

decs      : var
          | decs COMMA var  
          | decs COMMA ID BINARYOP_ASSIGN exps 
          | ID BINARYOP_ASSIGN exps
          | decs COMMA varArray BINARYOP_ASSIGN LC args RC  
          | varArray BINARYOP_ASSIGN LC args RC
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
            else if($<value.valType>1 == 2 && $<value.valType>3 == 2){
              int temp = newTemp();
              genIR(mul, $<value.temp>1, $<value.temp>3, temp);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp;
            }else{
              int temp = newTemp();
              if($<value.valType>1 == 2) genIR(muli, $<value.temp>1, $<value.temp>3, temp);
              else genIR(muli, $<value.temp>3, $<value.temp>1, temp);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp;
            }
          }
          | exps BINARYOP_DIV exps
          | exps BINARYOP_MOD exps
          | exps BINARYOP_ADD exps
          | exps MIN exps
          | exps BINARYOP_SHL exps
          | exps BINARYOP_SHR exps
          | exps BINARYOP_GT exps {
            if($<value.valType>1 == 1 && $<value.valType>2 == 1){
              if($<value.temp>1 > $<value.temp>2){
                $<value.trueList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
              else{
                $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
            }
            else if($<value.valType>1 == 2 && $<value.valType>2 == 2){
              $<value.trueList>$ = makelist(genIRForBranch(jgt, $<value.temp>1, $<value.temp>2, 0));
              $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            else{
              if($<value.valType>1 == 2){
                $<value.trueList>$ = makelist(genIRForBranch(jgt, $<value.temp>1, $<value.temp>2, 0));
                $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
              else if($<value.valType>2 == 2){
                $<value.trueList>$ = makelist(genIRForBranch(jgt, $<value.temp>2, $<value.temp>1, 0));
                $<value.falseList>$ = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
              else{
                printf("wrong while do NOT");
              }
            }
          }
          | exps BINARYOP_NLT exps
          | exps BINARYOP_LT exps
          | exps BINARYOP_NGT exps
          | exps BINARYOP_EQ exps
          | exps BINARYOP_NEQ exps
          | exps BINARYOP_BAND exps
          | exps BINARYOP_BXOR exps
          | exps BINARYOP_BOR exps
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
          | exps BINARYOP_ASSIGN exps 
          | exps BINARYOP_MULA exps
          | exps BINARYOP_DIVA exps
          | exps BINARYOP_MODA exps
          | exps BINARYOP_ADDA exps
          | exps BINARYOP_MINA exps
          | exps BINARYOP_BANDA exps
          | exps BINARYOP_BXORA exps
          | exps BINARYOP_BORA exps
          | exps BINARYOP_SHLA exps
          | exps BINARYOP_SHRA exps
          | MIN exps %prec UNARYOP_LNOT
          | UNARYOP_LNOT exps{
            $<value.trueList>$ = $<value.falseList>2;
            $<value.falseList>$ = $<value.trueList>2;
            $<value.nextList>$ = 0;
            $<value.valType>$ = 0;
          }
          | UNARYOP_INCR exps{
            if($<value.valType>2 == 1){
              $<value.valType>$ = $<value.valType>2;
              $<value.temp>$ = $<value.temp>2 - 1;
            }
            else{
              int temp = newTemp();
              genIR(subi, $<value.temp>2, 1, temp);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp;
            }
          }
          | UNARYOP_DECR exps{
            if($<value.valType>2 == 1){
              $<value.valType>$ = $<value.valType>2;
              $<value.temp>$ = $<value.temp>2 + 1;
            }
            else{
              int temp = newTemp();
              genIR(addi, $<value.temp>2, 1, temp);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp;
            }
          }
          | UNARYOP_BNOT exps{
            if($<value.valType>2 == 1){
              $<value.valType>$ = $<value.valType>2;
              $<value.temp>$ = ~$<value.temp>2;
            }
            else{
              int temp = newTemp();
              genIR(bnot, $<value.temp>2, 0, temp);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp;
            }
          }
          | LP exps RP {
            $$ = $2;
          }
          | ID LP args RP /*this is func*/
          | ID arrs {
            $<value.valType>$ = 2;
            int temp = newTemp();
            if($<value.valType>2 == 1){
              genIRForLS(lwi, temp, $<value.temp>2, $1);
            }
            else if($<value.valType>2 == 2){
              genIRForLS(lw, temp, $<value.temp>2, $1);
            }
            else{
              printf("wrong while array reference\n");
            }
            $<value.temp>$ = temp;
          }
          | ID DOT ID{
            struct symrec * os;
            int temp = newTemp();
            $<value.valType>$ = 2;
            $<value.temp>$ = temp;
            struct symrec * structVar = getsym($1);
            struct symrec * base = getsym(structVar->type);
            if(base == 0) printf("not defined type in struct variable!\n");
            else{
              os = getsymWithinScope($3, base->scope);
            }
            genIRForLS(lwi, temp, os->offset, structVar->name);
          }
          | INT {
            $<value.valType>$ = 1;
            $<value.temp>$ = $1;
          }
;

MM         : /* empty */{
            $$ = IR->tail;
          }
;

NN         : /* empty */{
            $$ = makelist(genIRForBranch(jmp, 0, 0, 0));
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
            else if($<value.valType>2 == 2){
              $<value.valType>$ = 2;
              int temp = newTemp();
              genIR(muli, $<value.temp>2, 4, temp);
              $<value.temp>$ = temp;
            }
            else{
              printf("wrong! while arrs 2\n");
            }
          }
          | LB exps RB LB exps RB {
            struct symrec * array = getsym($<id>0);
            if($<value.valType>2 == 1 && $<value.valType>5 == 1){
              $<value.valType>$ = 1;
              $<value.temp>$ = array->width * $<value.temp>2 * 4 + $<value.temp>5 * 4;
            }
            else if($<value.valType>2 == 2 && $<value.valType>5 == 2){
              int temp1 = newTemp();
              int temp2 = newTemp();
              int temp3 = newTemp();
              genIR(muli, $<value.temp>2, array->width * 4, temp1);
              genIR(muli, $<value.temp>5, 4, temp2);
              genIR(add, temp1, temp2, temp3);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp3;
            }
            else{
              if($<value.valType>2 == 2){
                int temp1 = newTemp();
                int temp3 = newTemp();
                genIR(muli, $<value.temp>2, array->width * 4, temp1);
                genIR(addi, temp1, $<value.temp>5 * 4, temp3);
                $<value.valType>$ = 2;
                $<value.temp>$ = temp3;
              }
              else{
                int temp2 = newTemp();
                int temp3 = newTemp();
                genIR(muli, $<value.temp>5, 4, temp2);
                genIR(add, temp2, array->width * 4 * $<value.temp>2, temp3);
                $<value.valType>$ = 2;
                $<value.temp>$ = temp3;
              }
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
=========================================================================*/
int main( int argc, char *argv[] )
{
  extern FILE *yyin;
  ++argv;
  --argc;
  yyin = fopen(argv[0], "r");
  // yydebug = 1;
  errors = 0;
  yyparse();
  // printf("%s\n", getsym("x")->type);
  printf("Parse Completed\n");
  printIR();
  // if (errors == 0) {
  //   print_code();
  //   fetch_execute_cycle();
  // }
  return 0;
}
/*=========================================================================
YYERROR
=========================================================================*/
int yyerror ( char *s ) /* Called by yyparse on error */
{
  errors++;
  printf("%s\n", "=========================================================================");
  printf("%s\n", s);
  printf("%d\n", yychar);
  return 0;
}
/**************************** End Grammar File ***************************/