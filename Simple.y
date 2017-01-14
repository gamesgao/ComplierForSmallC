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
#include "numStack.h" /* numStack Code */
// #include "SM.h" /* Stack Machine */
// #include "CG.h" /* Code Generator */
#define YYDEBUG 1 /* For Debugging */
int errors; /* Error Count */
/*-------------------------------------------------------------------------
The following support backpatching
-------------------------------------------------------------------------*/
struct lbs /* Labels for data, if and while */
{
  int for_goto;
  int for_jmp_false;
};

struct lbs *newlblrec() /* Allocate space for the labels */
{
  return (struct lbs *)malloc(sizeof(struct lbs));
}

/*-------------------------------------------------------------------------
Install identifier & check if previously defined.
-------------------------------------------------------------------------*/

void registerId(char *sym_name, char* type, int width, int height, struct symrec * scope, struct Quad* entry) {
  symrec *s;
  s = getsymInScope(sym_name);
  if (s == 0)
    s = putsym(sym_name, type, width, height, scope, entry);
  else {
    errors++;
    printf("%s is already defined\n", sym_name);
  }
}
/*-------------------------------------------------------------------------
If identifier is defined, generate code
-------------------------------------------------------------------------*/
// context_check(enum code_ops operation, char *sym_name) {
//   symrec *identifier;
//   identifier = getsym(sym_name);
//   if (identifier == 0) {
//     errors++;
//     printf("%s", sym_name);
//     printf("%s\n", " is an undeclared identifier");
//   } else
//     gen_code(operation, identifier->offset);
// }

/*-------------------------------------------------------------------------
define the return type for each terminal and nonterminal
-------------------------------------------------------------------------*/
struct name{

};




%}
/*=========================================================================
SEMANTIC RECORDS
=========================================================================*/

%union semrec /* The Semantic Records */
{
  int intval;       /* Integer values */
  char *id;         /* Identifiers */
  struct lbs *lbls; /* For backpatching */
  struct{
    char* id;
    int width;
    int height;
  } variable;

  struct NSData value;
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
%type<value> exps exp
%type<int> args


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
          | TYPE func stmtblock
;

sextvars  : sextvars COMMA ID {
            registerId($3, $0, 0, 0, 0, 0);
          }
          | ID {
            registerId($1, $0, 0, 0, 0, 0);
          }
;

extvars   : extvars COMMA var {
            registerId($<variable.id>3, "int", $<variable.width>3, $<variable.height>3, 0, 0);
          }
          | extvars COMMA ID BINARYOP_ASSIGN exps{
            registerId($3, "int", 1, 1, 0, 0);
            if($<value.valType>5 == 1){
              int temp = newTemp();
              genIR(li, 0, $<value.temp>5, temp);
              genIRForLS(sw, temp, 0, $3);
            } else {
              genIRForLS(sw, $<value.temp>5, 0, $3);
            }
          }
          | ID BINARYOP_ASSIGN exps {
            registerId($1, "int", 1, 1, 0, 0);
            if($<value.valType>3 == 1){
              int temp = newTemp();
              genIR(li, 0, $<value.temp>3, temp);
              genIRForLS(sw, temp, 0, $1);
            } else {
              genIRForLS(sw, $<value.temp>3, 0, $1);
            }
          }
          | extvars COMMA varArray BINARYOP_ASSIGN LC args RC
          | varArray BINARYOP_ASSIGN LC args RC{
            if($<variable.width>1 * $<variable.height>1 >= $4){
              int i = 0;
              for(;i<$4;i++){
                struct NSData* temp = NSPop();
                if(temp->valType == 1){
                  int tempReg = newTemp();
                  genIR(li, 0, temp->temp, tempReg);
                  genIRForLS(sw, tempReg, i*4, $<variable.id>1);
                }
                else if(temp->valType == 2){
                  genIRForLS(sw, temp->temp, i*4, $<variable.id>1);
                }
              }
            }
          }
          | var {
            registerId($<variable.id>1, "int", $<variable.width>1, $<variable.height>1, 0, 0);
          }
;

stspec    : STRUCT ID LC {addLevel();} sdefs RC{
            registerId($2, 'struct', width, 0, subLevel(), 0);
            $$ = $2;
          }
          | STRUCT LC sdefs RC{
            char * tempID = (char *) malloc(sizeof(char)*9);
            itoa(getRandomNumber(), tempID, 10);
            registerId(tempID, 'struct', width, 0, subLevel(), 0);
            $$ = tempID;
          } /*在没有ID的情况下可能需要随机分配一个?*/
          | STRUCT ID {
            $$ = $2;
          }
;

func      : ID LP paras RP
;

paras     : /* empty */
          | TYPE ID COMMA paras
          | TYPE ID
;

stmtblock : LC defs stmts RC
;

stmts     : /* empty */
          | stmt stmts
;

stmt      : exp SEMI
          | stmtblock
          | RETURN exp SEMI
          | IF LP exp RP stmt
          | IF LP exp RP stmt ELSE stmt
          | FOR LP exp SEMI exp SEMI exp RP stmt
          | CONT SEMI
          | BREAK SEMI
;

defs      : /* empty */
          | TYPE decs SEMI defs
          | stspec sdecs SEMI defs
;

sdefs     : sdefs TYPE sdecs SEMI
          | TYPE sdecs SEMI 
;

sdecs     : sdecs COMMA ID  
          | ID
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
            $<variable.width>$ = 1;
            $<variable.height>$ = $3;
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
          | exps BINARYOP_GT exps
          | exps BINARYOP_NLT exps
          | exps BINARYOP_LT exps
          | exps BINARYOP_NGT exps
          | exps BINARYOP_EQ exps
          | exps BINARYOP_NEQ exps
          | exps BINARYOP_BAND exps
          | exps BINARYOP_BXOR exps
          | exps BINARYOP_BOR exps
          | exps BINARYOP_LAND exps
          | exps BINARYOP_LOR exps
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
            if($<value.valType>2 == 1){
              $<value.valType>$ = $<value.valType>2;
              $<value.temp>$ = !$<value.temp>2;
            }
            else{
              int temp = newTemp();
              genIR(bnot, $<value.temp>2, 0, temp);
              $<value.valType>$ = 2;
              $<value.temp>$ = temp;
            }
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
            $<value.temp>$ = newTemp();
            genIR(mov, 1,1,1);
          }
          | ID DOT ID{
            int temp = newTemp();
            $<value.valType>$ = 2;
            $<value.temp>$ = temp;
            struct symrec * structVar = getsym($1);
            struct symrec * base = getsym(structVar->type);
            if(base == 0) printf("not defined type in struct variable!\n");
            else{
              struct symrec * os = getsymWithinScope($3, base->scope);
            }
            // genIRForLS(lw, temp, os->offset, structVar->name);
          }
          | INT {
            $<value.valType>$ = 1;
            $<value.temp>$ = $1;
          }
;

arrs      : /* empty */
          | LB exps RB arrs
;

args      : args COMMA exp{
            NSPush($3);
            $$ = $1 + 1;
          }
          | exp {
            NSPush($1);
            $$ = 1;
          }
;

%%
/*=========================================================================
MAIN
=========================================================================*/
main( int argc, char *argv[] )
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
}
/*=========================================================================
YYERROR
=========================================================================*/
yyerror ( char *s ) /* Called by yyparse on error */
{
  errors++;
  printf("%s\n", "=========================================================================");
  printf("%s\n", s);
  printf("%d\n", yychar);
}
/**************************** End Grammar File ***************************/