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
#include "SM.h" /* Stack Machine */
#include "CG.h" /* Code Generator */
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

void registerId(char *sym_name, char *type) {
  symrec *s;
  s = getsym(sym_name);
  if (s == 0)
    s = putsym(sym_name, type);
  else {
    errors++;
    printf("%s is already defined\n", sym_name);
  }
}
/*-------------------------------------------------------------------------
If identifier is defined, generate code
-------------------------------------------------------------------------*/
context_check(enum code_ops operation, char *sym_name) {
  symrec *identifier;
  identifier = getsym(sym_name);
  if (identifier == 0) {
    errors++;
    printf("%s", sym_name);
    printf("%s\n", " is an undeclared identifier");
  } else
    gen_code(operation, identifier->offset);
}

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

}
/*=========================================================================
TOKENS
=========================================================================*/
%start program
%token INT
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
%type<id> var
%type<id> decs
%type<id> extvars


/*=========================================================================
GRAMMAR RULES for the Simple language
=========================================================================*/

%%

program   : extdefs
;

extdefs   : /* empty */
          | extdef extdefs
;

extdef    : TYPE extvars SEMI{
            registerId($2, "int");
          }
          | stspec sextvars SEMI
          | TYPE func stmtblock
;

sextvars  : /* empty */
          | ID
          | ID COMMA sextvars
;

extvars   : /* empty */
          | var {
            $$ = $1;
          }
          | var BINARYOP_ASSIGN init
          | var COMMA extvars
          | var BINARYOP_ASSIGN init COMMA extvars
;

stspec    : STRUCT ID LC sdefs RC
          | STRUCT LC sdefs RC
          | STRUCT ID
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
          | TYPE decs SEMI defs {
            registerId($2, "int");
          }
          | stspec sdecs SEMI defs
;

sdefs     : /* empty */
          | TYPE sdecs SEMI sdefs
;

sdecs     : ID COMMA sdecs
          | ID
;

decs      : var {
            $$ = $1;
          }
          | var COMMA decs
          | var BINARYOP_ASSIGN init COMMA decs
          | var BINARYOP_ASSIGN init
;

var       : ID {
            $$ = $1;
          }
          | var LB INT RB {
            //TODO
          }
;

init      : exp
          | LC args RC
;

exp       : /* empty */
          | exps
;

exps      : exps BINARYOP_MUL exps
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
          | UNARYOP_LNOT exps
          | UNARYOP_INCR exps
          | UNARYOP_DECR exps
          | UNARYOP_BNOT exps
          | LP exps RP
          | ID LP args RP
          | ID arrs
          | ID DOT ID
          | INT
;

arrs      : /* empty */
          | LB exp RB arrs
;

args      : exp COMMA args
          | exp
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
  yydebug = 1;
  errors = 0;
  yyparse();
  printf("Parse Completed\n");
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