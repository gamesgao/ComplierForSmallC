/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "Simple.y" /* yacc.c:339  */
/*************************************************************************
Compiler for the Simple language
***************************************************************************/
/*=========================================================================
C Libraries, Symbol Table, Code Generator & other C code
=========================================================================*/
#include <stdio.h> /* For I/O */
#include <stdlib.h> /* For malloc here and in symbol table */
#include <string.h> /* For strcmp in symbol table */
#include "Quad.h" /* Quad Code */
#include "ST.h" /* Symbol Table */
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


#line 111 "Simple.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "Simple.tab.h".  */
#ifndef YY_YY_SIMPLE_TAB_H_INCLUDED
# define YY_YY_SIMPLE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    ID = 259,
    SEMI = 260,
    COMMA = 261,
    DOT = 262,
    BINARYOP_MUL = 263,
    BINARYOP_DIV = 264,
    BINARYOP_MOD = 265,
    BINARYOP_ADD = 266,
    MIN = 267,
    BINARYOP_SHL = 268,
    BINARYOP_SHR = 269,
    BINARYOP_GT = 270,
    BINARYOP_NLT = 271,
    BINARYOP_LT = 272,
    BINARYOP_NGT = 273,
    BINARYOP_EQ = 274,
    BINARYOP_NEQ = 275,
    BINARYOP_BAND = 276,
    BINARYOP_BXOR = 277,
    BINARYOP_BOR = 278,
    BINARYOP_LAND = 279,
    BINARYOP_LOR = 280,
    BINARYOP_ASSIGN = 281,
    BINARYOP_MULA = 282,
    BINARYOP_DIVA = 283,
    BINARYOP_MODA = 284,
    BINARYOP_ADDA = 285,
    BINARYOP_MINA = 286,
    BINARYOP_BANDA = 287,
    BINARYOP_BXORA = 288,
    BINARYOP_BORA = 289,
    BINARYOP_SHLA = 290,
    BINARYOP_SHRA = 291,
    UNARYOP_LNOT = 292,
    UNARYOP_INCR = 293,
    UNARYOP_DECR = 294,
    UNARYOP_BNOT = 295,
    TYPE = 296,
    LP = 297,
    RP = 298,
    LB = 299,
    RB = 300,
    LC = 301,
    RC = 302,
    STRUCT = 303,
    RETURN = 304,
    IF = 305,
    ELSE = 306,
    BREAK = 307,
    CONT = 308,
    FOR = 309,
    UNARYOP_DERE = 310
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
#line 49 "Simple.y" /* yacc.c:355  */
union semrec
{
#line 50 "Simple.y" /* yacc.c:355  */

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


#line 247 "Simple.tab.c" /* yacc.c:355  */
};
#line 49 "Simple.y" /* yacc.c:355  */
typedef union semrec YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SIMPLE_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 264 "Simple.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   434

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  228

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   310

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   183,   183,   186,   187,   190,   191,   192,   193,   198,
     201,   206,   209,   219,   229,   230,   250,   255,   255,   259,
     259,   265,   270,   270,   277,   278,   281,   286,   295,   302,
     312,   317,   324,   331,   347,   357,   365,   376,   383,   392,
     393,   394,   397,   400,   405,   408,   413,   414,   415,   416,
     417,   418,   421,   426,   431,   436,   443,   446,   451,   486,
     487,   488,   489,   490,   491,   492,   522,   523,   524,   525,
     526,   527,   528,   529,   530,   537,   544,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   589,
     590,   591,   592,   595,   619,   638,   651,   657,   662,   666,
     681,   718,   722
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "ID", "SEMI", "COMMA", "DOT",
  "BINARYOP_MUL", "BINARYOP_DIV", "BINARYOP_MOD", "BINARYOP_ADD", "MIN",
  "BINARYOP_SHL", "BINARYOP_SHR", "BINARYOP_GT", "BINARYOP_NLT",
  "BINARYOP_LT", "BINARYOP_NGT", "BINARYOP_EQ", "BINARYOP_NEQ",
  "BINARYOP_BAND", "BINARYOP_BXOR", "BINARYOP_BOR", "BINARYOP_LAND",
  "BINARYOP_LOR", "BINARYOP_ASSIGN", "BINARYOP_MULA", "BINARYOP_DIVA",
  "BINARYOP_MODA", "BINARYOP_ADDA", "BINARYOP_MINA", "BINARYOP_BANDA",
  "BINARYOP_BXORA", "BINARYOP_BORA", "BINARYOP_SHLA", "BINARYOP_SHRA",
  "UNARYOP_LNOT", "UNARYOP_INCR", "UNARYOP_DECR", "UNARYOP_BNOT", "TYPE",
  "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN", "IF", "ELSE",
  "BREAK", "CONT", "FOR", "UNARYOP_DERE", "$accept", "program", "extdefs",
  "extdef", "sextvars", "extvars", "stspec", "$@1", "$@2", "func", "$@3",
  "paras", "stmtblock", "stmts", "NN", "stmt", "defs", "sdefs", "sdecs",
  "decs", "var", "varArray", "exp", "exps", "MM", "arrs", "args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310
};
# endif

#define YYPACT_NINF -200

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-200)))

#define YYTABLE_NINF -57

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -38,     9,    27,    24,  -200,   -38,    29,   -21,   140,    15,
    -200,    76,    79,  -200,  -200,  -200,  -200,  -200,   151,    92,
    -200,   119,  -200,   129,    53,  -200,    91,  -200,   107,  -200,
     149,  -200,    70,    92,    92,    92,    92,    92,    92,   323,
     122,   114,    -1,  -200,   153,   173,   177,   112,    92,   107,
     177,   -12,  -200,   186,    92,    92,  -200,  -200,  -200,  -200,
     323,  -200,   287,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,  -200,
    -200,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,   187,   150,   152,    92,   148,    16,   169,  -200,
     171,  -200,   179,    92,   156,   190,   194,   158,  -200,   160,
    -200,   200,   323,  -200,    31,    72,   181,   177,  -200,  -200,
      -2,   211,  -200,  -200,  -200,  -200,    89,    89,   161,   161,
      97,    97,    97,    97,    75,    75,   414,   400,   385,    92,
      92,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   202,  -200,   206,   323,    92,    92,    53,   207,
     166,    53,   244,   210,    92,  -200,  -200,    92,  -200,   112,
    -200,    92,  -200,  -200,  -200,   183,  -200,   205,   369,   352,
     122,   208,    32,   323,  -200,    56,  -200,   224,    92,  -200,
    -200,  -200,   209,   246,  -200,  -200,  -200,    92,  -200,  -200,
    -200,    92,   240,    33,  -200,  -200,   249,   323,    92,  -200,
     164,    92,  -200,    34,   203,   250,  -200,   236,  -200,  -200,
      92,   164,  -200,  -200,   245,  -200,   164,  -200
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     0,     2,     3,     0,    52,     0,     0,
      16,    53,    21,    19,     1,     4,    10,     7,     0,     0,
      22,     0,     5,     0,    39,     8,     0,    17,     0,     6,
       0,    96,    98,     0,     0,     0,     0,     0,     0,    13,
      24,     0,    52,    11,    53,     0,     0,    28,    56,     0,
       0,     0,     9,     0,    56,     0,    94,    87,    88,    89,
      90,    91,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    97,
      97,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    55,     0,     0,    52,     0,    46,
      53,    45,     0,    56,     0,     0,     0,     0,    32,     0,
      97,     0,    57,   102,     0,     0,     0,     0,    20,    95,
       0,     0,    92,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,     0,
       0,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    26,    23,     0,    12,    56,     0,    39,     0,
       0,    39,     0,     0,    56,    38,    37,    56,    27,    28,
      31,    56,    15,    18,    43,     0,    93,    99,    74,    75,
      24,     0,     0,    49,    40,    52,    47,    53,    56,    41,
      44,    33,     0,     0,    29,   101,    42,     0,    25,    54,
      14,     0,     0,     0,    97,    97,     0,    48,    56,    51,
      56,    56,   100,     0,    35,     0,    50,     0,    97,    97,
      56,    56,    30,    34,     0,    97,    56,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -200,  -200,   284,  -200,  -200,  -200,   118,  -200,  -200,  -200,
    -200,   110,   282,   123,    71,  -199,  -149,   275,   -43,  -200,
     -17,   -15,   -28,   -19,   -78,  -200,   -53
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    18,     8,    46,    49,    28,     9,
      40,    93,   108,   109,   217,   110,    47,    51,   102,    98,
      10,    11,   111,   112,   139,    56,   114
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      39,   120,   140,     1,   171,    19,    43,   116,    44,   184,
       2,   214,   189,     7,    57,    58,    59,    60,    61,    62,
     113,    20,   223,    21,    14,    95,   113,   227,    99,   117,
     100,    12,   169,    16,    17,   118,   121,   171,   171,   171,
     171,   176,   157,    21,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
      21,    24,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,    13,   175,   163,   155,    53,   172,   200,
     209,   216,   201,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    45,    31,    32,    63,    64,    65,
      21,     2,    26,   182,    33,    63,    64,    65,    66,    67,
      68,    69,    54,   117,    55,    31,    32,   -56,     6,   173,
     178,   179,    41,     6,    33,    27,   210,   211,   113,    34,
      35,    36,    37,    42,    38,   203,   192,    48,   183,   193,
     220,   221,   186,   195,   187,    22,    23,   226,    50,    34,
      35,    36,    37,    52,    38,   213,    29,    30,    24,    94,
     113,   103,   104,    92,   105,   106,   107,    31,    32,    63,
      64,    65,    66,    67,   158,   159,    33,    97,   206,    96,
     113,   101,   207,   215,   161,   162,   174,   162,   196,   162,
     119,   152,   222,   153,   156,   165,   154,   160,   164,   166,
     167,    34,    35,    36,    37,   170,    38,   168,   180,   181,
      24,   185,   188,   103,   104,   191,   105,   106,   107,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,   190,   197,
     202,   205,   204,   199,   -30,   218,   177,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,   208,   219,   225,    15,
     198,    25,   194,   224,   212,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,   115,     0,     0,     0,     0,     0,
     122,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75
};

static const yytype_int16 yycheck[] =
{
      19,    54,    80,    41,     6,    26,    23,    50,    23,   158,
      48,   210,   161,     4,    33,    34,    35,    36,    37,    38,
      48,    42,   221,    44,     0,    26,    54,   226,    45,    41,
      45,     4,   110,     4,     5,    47,    55,     6,     6,     6,
       6,    43,    26,    44,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      44,    46,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    46,   117,   103,    95,     7,    47,    47,
      47,    47,    26,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    41,     3,     4,     8,     9,    10,
      44,    48,    26,   156,    12,     8,     9,    10,    11,    12,
      13,    14,    42,    41,    44,     3,     4,     5,     0,    47,
     139,   140,     3,     5,    12,    46,   204,   205,   156,    37,
      38,    39,    40,     4,    42,   188,   164,    46,   157,   167,
     218,   219,   159,   171,   159,     5,     6,   225,    41,    37,
      38,    39,    40,     4,    42,   208,     5,     6,    46,    45,
     188,    49,    50,    41,    52,    53,    54,     3,     4,     8,
       9,    10,    11,    12,     5,     6,    12,     4,   197,    26,
     208,     4,   201,   211,     5,     6,     5,     6,     5,     6,
       4,     4,   220,    43,    46,     5,    44,    26,    42,     5,
      42,    37,    38,    39,    40,     5,    42,    47,     6,     3,
      46,     4,    46,    49,    50,     5,    52,    53,    54,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,     4,    44,
      26,     5,    43,    45,    51,     5,    45,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    46,    51,    43,     5,
     180,     9,   169,   222,    45,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    49,    -1,    -1,    -1,    -1,    -1,
      43,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    41,    48,    57,    58,    59,    62,     4,    61,    65,
      76,    77,     4,    46,     0,    58,     4,     5,    60,    26,
      42,    44,     5,     6,    46,    68,    26,    46,    64,     5,
       6,     3,     4,    12,    37,    38,    39,    40,    42,    79,
      66,     3,     4,    76,    77,    41,    62,    72,    46,    63,
      41,    73,     4,     7,    42,    44,    81,    79,    79,    79,
      79,    79,    79,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    41,    67,    45,    26,    26,     4,    75,    76,
      77,     4,    74,    49,    50,    52,    53,    54,    68,    69,
      71,    78,    79,    78,    82,    73,    74,    41,    47,     4,
      82,    79,    43,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    80,
      80,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,     4,    43,    44,    79,    46,    26,     5,     6,
      26,     5,     6,    78,    42,     5,     5,    42,    47,    80,
       5,     6,    47,    47,     5,    74,    43,    45,    79,    79,
       6,     3,    82,    79,    72,     4,    76,    77,    46,    72,
       4,     5,    78,    78,    69,    78,     5,    44,    67,    45,
      47,    26,    26,    82,    43,     5,    79,    79,    46,    47,
      80,    80,    45,    82,    71,    78,    47,    70,     5,    51,
      80,    80,    78,    71,    70,    43,    80,    71
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    59,    59,    60,
      60,    61,    61,    61,    61,    61,    61,    63,    62,    64,
      62,    62,    66,    65,    67,    67,    67,    68,    69,    69,
      70,    71,    71,    71,    71,    71,    71,    71,    71,    72,
      72,    72,    73,    73,    74,    74,    75,    75,    75,    75,
      75,    75,    76,    76,    77,    77,    78,    78,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    80,    81,    81,
      81,    82,    82
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     3,     2,     3,     3,
       1,     3,     5,     3,     7,     5,     1,     0,     6,     0,
       5,     2,     0,     5,     0,     4,     2,     4,     0,     3,
       0,     2,     1,     3,    10,     6,    13,     2,     2,     0,
       4,     4,     4,     3,     3,     1,     1,     3,     5,     3,
       7,     5,     1,     1,     7,     4,     0,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       2,     2,     3,     4,     2,     3,     1,     0,     0,     3,
       6,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 8:
#line 193 "Simple.y" /* yacc.c:1646  */
    {
            registerId((yyvsp[-1].funcType.id), "func", 0, 0, (yyvsp[-1].funcType.param), (yyvsp[-1].funcType.beforeEntry)->next, subLevel());
          }
#line 1540 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 198 "Simple.y" /* yacc.c:1646  */
    {
            registerId((yyvsp[0].id), (yyvsp[-3].id), 0, 0, 0, 0, 0);
          }
#line 1548 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 201 "Simple.y" /* yacc.c:1646  */
    {
            registerId((yyvsp[0].id), (yyvsp[-1].id), 0, 0, 0, 0, 0);
          }
#line 1556 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 206 "Simple.y" /* yacc.c:1646  */
    {
            registerId((yyvsp[0].variable.id), "int", (yyvsp[0].variable.width), (yyvsp[0].variable.height), 0, 0, 0);
          }
#line 1564 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 209 "Simple.y" /* yacc.c:1646  */
    {
            registerId((yyvsp[-2].id), "int", 1, 1, 0, 0, 0);
            if((yyvsp[0].value.valType) == 1){
              int temp = newTemp();
              genIR(li, 0, (yyvsp[0].value.temp), temp);
              genIRForLS(sw, temp, 0, (yyvsp[-2].id));
            } else {
              genIRForLS(sw, (yyvsp[0].value.temp), 0, (yyvsp[-2].id));
            }
          }
#line 1579 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 219 "Simple.y" /* yacc.c:1646  */
    {
            registerId((yyvsp[-2].id), "int", 1, 1, 0, 0, 0);
            if((yyvsp[0].value.valType) == 1){
              int temp = newTemp();
              genIR(li, 0, (yyvsp[0].value.temp), temp);
              genIRForLS(swi, temp, 0, (yyvsp[-2].id));
            } else {
              genIRForLS(swi, (yyvsp[0].value.temp), 0, (yyvsp[-2].id));
            }
          }
#line 1594 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 230 "Simple.y" /* yacc.c:1646  */
    {
            int i = 0;
            struct NSData* temp;
            if(((yyvsp[-4].variable.width) * (yyvsp[-4].variable.height)) >= (yyvsp[-1].intval)){
              for(i=(yyvsp[-1].intval)-1;i >= 0 ;i--){
                temp = NSPop();
                if(temp->valType == 1){
                  int tempReg = newTemp();
                  genIR(li, 0, temp->temp, tempReg);
                  genIRForLS(swi, tempReg, i*4, (yyvsp[-4].variable.id));
                }
                else if(temp->valType == 2){
                  genIRForLS(swi, temp->temp, i*4, (yyvsp[-4].variable.id));
                }
              }
            }
            else{
              printf("wrong while init array!\n");
            }
          }
#line 1619 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 250 "Simple.y" /* yacc.c:1646  */
    {
            registerId((yyvsp[0].variable.id), "int", (yyvsp[0].variable.width), (yyvsp[0].variable.height), 0, 0, 0);
          }
#line 1627 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 255 "Simple.y" /* yacc.c:1646  */
    {addLevel();}
#line 1633 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 255 "Simple.y" /* yacc.c:1646  */
    {
            registerId((yyvsp[-4].id), "struct", (yyvsp[-1].offset), 0, subLevel(), 0, 0);
            (yyval.id) = (yyvsp[-4].id);
          }
#line 1642 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 259 "Simple.y" /* yacc.c:1646  */
    {addLevel();}
#line 1648 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 259 "Simple.y" /* yacc.c:1646  */
    {
            char * tempID = (char *) malloc(sizeof(char)*9);
            sprintf(tempID, "%d", getRandomNumber());
            registerId(tempID, "struct", (yyvsp[-1].offset), 0, subLevel(), 0, 0);
            (yyval.id) = tempID;
          }
#line 1659 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 265 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.id) = (yyvsp[0].id);
          }
#line 1667 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 270 "Simple.y" /* yacc.c:1646  */
    {addLevel();}
#line 1673 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 270 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.funcType.id) = (yyvsp[-4].id);
            (yyval.funcType.param) = sym_table;
            (yyval.funcType.beforeEntry) = IR->tail;
          }
#line 1683 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 278 "Simple.y" /* yacc.c:1646  */
    {
            registerId((yyvsp[-2].id), "int", 1, 1, 0, 0, 0);
          }
#line 1691 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 281 "Simple.y" /* yacc.c:1646  */
    {
            registerId((yyvsp[0].id), "int", 1, 1, 0, 0, 0);
          }
#line 1699 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 286 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.stmtType.nextList) = 0;
            (yyval.stmtType.continueCount) = (yyvsp[-1].stmtType.continueCount);
            (yyval.stmtType.breakCount) = (yyvsp[-1].stmtType.breakCount);
            (yyval.stmtType.continueList) = (yyvsp[-1].stmtType.continueList);
            (yyval.stmtType.breakList) = (yyvsp[-1].stmtType.breakList);
          }
#line 1711 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 295 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.stmtType.nextList) = 0;
            (yyval.stmtType.continueCount) = 0;
            (yyval.stmtType.breakCount) = 0;
            (yyval.stmtType.continueList) = 0;
            (yyval.stmtType.breakList) = 0;
          }
#line 1723 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 302 "Simple.y" /* yacc.c:1646  */
    {
            backpatch((yyvsp[-2].stmtType.nextList), (yyvsp[-1].inst)->next);
            (yyval.stmtType.nextList) = 0;
            (yyval.stmtType.continueCount) = (yyvsp[-2].stmtType.continueCount) + (yyvsp[0].stmtType.continueCount);
            (yyval.stmtType.breakCount) = (yyvsp[-2].stmtType.breakCount) + (yyvsp[0].stmtType.breakCount);
            (yyval.stmtType.continueList) = merge((yyvsp[-2].stmtType.continueList), (yyvsp[0].stmtType.continueList));
            (yyval.stmtType.breakList) = merge((yyvsp[-2].stmtType.breakList), (yyvsp[0].stmtType.breakList));
          }
#line 1736 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 312 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.nextlist) = makelist(genIRForBranch(jmp, 0, 0, 0));
          }
#line 1744 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 317 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.stmtType.nextList) = 0;
            (yyval.stmtType.continueCount) = 0;
            (yyval.stmtType.breakCount) = 0;
            (yyval.stmtType.continueList) = 0;
            (yyval.stmtType.breakList) = 0;
          }
#line 1756 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 324 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.stmtType.nextList) = 0;
            (yyval.stmtType.continueCount) = (yyvsp[0].stmtType.continueCount);
            (yyval.stmtType.breakCount) = (yyvsp[0].stmtType.breakCount);
            (yyval.stmtType.continueList) = (yyvsp[0].stmtType.continueList);
            (yyval.stmtType.breakList) = (yyvsp[0].stmtType.breakList);
          }
#line 1768 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 331 "Simple.y" /* yacc.c:1646  */
    {
            int temp;
            if((yyvsp[-1].value.valType) == 1){
              temp = newTemp();
              genIR(li, 0, (yyvsp[-1].value.temp), temp);
            }
            else{
              temp = normalizeExp((struct NSData *) &(yyvsp[-1].value));
            }
            genIR(ret, temp, 0, 0);
            (yyval.stmtType.continueCount) = 0;
            (yyval.stmtType.continueList) = 0;
            (yyval.stmtType.breakCount) = 0;
            (yyval.stmtType.breakList) = 0;
            (yyval.stmtType.nextList) = 0;
          }
#line 1789 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 347 "Simple.y" /* yacc.c:1646  */
    {
            backpatch((yyvsp[-7].value.trueList), (yyvsp[-5].inst)->next);
            backpatch((yyvsp[-7].value.falseList), (yyvsp[-1].inst)->next);
            (yyval.stmtType.nextList) = merge(merge((yyvsp[-4].stmtType.nextList), (yyvsp[-3].nextlist)), (yyvsp[0].stmtType.nextList));
            (yyval.stmtType.continueCount) = (yyvsp[-4].stmtType.continueCount) + (yyvsp[0].stmtType.continueCount);
            (yyval.stmtType.breakCount) = (yyvsp[-4].stmtType.breakCount) + (yyvsp[0].stmtType.breakCount);
            (yyval.stmtType.continueList) = merge((yyvsp[-4].stmtType.continueList), (yyvsp[0].stmtType.continueList));
            (yyval.stmtType.breakList) = merge((yyvsp[-4].stmtType.breakList), (yyvsp[0].stmtType.breakList));

          }
#line 1804 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 357 "Simple.y" /* yacc.c:1646  */
    {
            backpatch((yyvsp[-3].value.trueList), (yyvsp[-1].inst)->next);
            (yyval.stmtType.nextList) = merge((yyvsp[-3].value.falseList), (yyvsp[0].stmtType.nextList));
            (yyval.stmtType.continueCount) = (yyvsp[0].stmtType.continueCount);
            (yyval.stmtType.breakCount) = (yyvsp[0].stmtType.breakCount);
            (yyval.stmtType.continueList) = (yyvsp[0].stmtType.continueList);
            (yyval.stmtType.breakList) = (yyvsp[0].stmtType.breakList);
          }
#line 1817 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 365 "Simple.y" /* yacc.c:1646  */
    {
            backpatch((yyvsp[-7].value.trueList), (yyvsp[-1].inst)->next);
            backpatch((yyvsp[-3].nextlist), (yyvsp[-8].inst)->next);
            genIRForBranch(jmp, 0, 0, (yyvsp[-5].inst)->next);
            backpatch((yyvsp[0].stmtType.continueList), (yyvsp[-8].inst)->next);
            (yyval.stmtType.nextList) = merge((yyvsp[-7].value.falseList), (yyvsp[0].stmtType.breakList));
            (yyval.stmtType.continueCount) = 0;
            (yyval.stmtType.continueList) = 0;
            (yyval.stmtType.breakCount) = 0;
            (yyval.stmtType.breakList) = 0;
          }
#line 1833 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 376 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.stmtType.continueCount) = 1;
            (yyval.stmtType.continueList) = makelist(genIRForBranch(jmp, 0, 0, 0));
            (yyval.stmtType.breakCount) = 0;
            (yyval.stmtType.breakList) = 0;
            (yyval.stmtType.nextList) = 0;
          }
#line 1845 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 383 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.stmtType.continueCount) = 0;
            (yyval.stmtType.continueList) = 0;
            (yyval.stmtType.breakCount) = 1;
            (yyval.stmtType.breakList) = makelist(genIRForBranch(jmp, 0, 0, 0));
            (yyval.stmtType.nextList) = 0;
          }
#line 1857 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 397 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.offset) = totalOffset;
          }
#line 1865 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 400 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.offset) = totalOffset;
          }
#line 1873 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 405 "Simple.y" /* yacc.c:1646  */
    {
            registerId((yyvsp[0].id), "int", 1, 1, 0, 0, 0);
          }
#line 1881 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 408 "Simple.y" /* yacc.c:1646  */
    {
            registerId((yyvsp[0].id), "int", 1, 1, 0, 0, 0);
          }
#line 1889 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 421 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.variable.id) = (yyvsp[0].id);
            (yyval.variable.width) = 1;
            (yyval.variable.height) = 1;
          }
#line 1899 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 426 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.variable) = (yyvsp[0].variable);
          }
#line 1907 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 431 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.variable.id) = (yyvsp[-6].variable.id);
            (yyval.variable.width) = (yyvsp[-4].intval);
            (yyval.variable.height) = (yyvsp[-1].intval);
          }
#line 1917 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 436 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.variable.id) = (yyvsp[-3].id);
            (yyval.variable.width) = (yyvsp[-1].intval);
            (yyval.variable.height) = 1;
          }
#line 1927 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 443 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.value.valType) = 0;
          }
#line 1935 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 446 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.value) = (yyvsp[0].value);
          }
#line 1943 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 451 "Simple.y" /* yacc.c:1646  */
    {
            if((yyvsp[-2].value.valType) == 1 && (yyvsp[0].value.valType) == 1){
              (yyval.value.valType) = 1;
              (yyval.value.temp) = (yyvsp[-2].value.temp) * (yyvsp[0].value.temp);
            }
            else if((yyvsp[-2].value.valType) == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&(yyvsp[0].value));
              result = newTemp();
              genIR(muli, temp, (yyvsp[-2].value.temp), result);
              (yyval.value.valType) = 2;
              (yyval.value.temp) = result;
            }
            else if((yyvsp[0].value.valType) == 1){
              int temp;
              int result;
              temp = normalizeExp((struct NSData *)&(yyvsp[-2].value));
              result = newTemp();
              genIR(muli, temp, (yyvsp[0].value.temp), result);
              (yyval.value.valType) = 2;
              (yyval.value.temp) = result;
            }
            else{
              int temp1;
              int temp2;
              int result;
              temp1 = normalizeExp((struct NSData *)&(yyvsp[-2].value));
              temp2 = normalizeExp((struct NSData *)&(yyvsp[0].value));
              result = newTemp();
              genIR(mul, temp1, temp2, result);
              (yyval.value.valType) = 2;
              (yyval.value.temp) = result;
            }
          }
#line 1983 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 492 "Simple.y" /* yacc.c:1646  */
    {
            if((yyvsp[-2].value.valType) == 1 && (yyvsp[0].value.valType) == 1){
              if((yyvsp[-2].value.temp) > (yyvsp[0].value.temp)){
                (yyval.value.trueList) = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
              else{
                (yyval.value.falseList) = makelist(genIRForBranch(jmp, 0, 0, 0));
              }
            }
            else if((yyvsp[-2].value.valType) == 1){
              int temp;
              temp = normalizeExp((struct NSData *)&(yyvsp[0].value));
              (yyval.value.trueList) = makelist(genIRForBranch(jgti, temp, (yyvsp[-2].value.temp), 0));
              (yyval.value.falseList) = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            else if((yyvsp[0].value.valType) == 1){
              int temp;
              temp = normalizeExp((struct NSData *)&(yyvsp[-2].value));
              (yyval.value.trueList) = makelist(genIRForBranch(jgti, temp, (yyvsp[0].value.temp), 0));
              (yyval.value.falseList) = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
            else{
              int temp1;
              int temp2;
              temp1 = normalizeExp((struct NSData *)&(yyvsp[-2].value));
              temp2 = normalizeExp((struct NSData *)&(yyvsp[0].value));
              (yyval.value.trueList) = makelist(genIRForBranch(jgt, temp1, temp2, 0));
              (yyval.value.falseList) = makelist(genIRForBranch(jmp, 0, 0, 0));
            }
          }
#line 2018 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 530 "Simple.y" /* yacc.c:1646  */
    {
            backpatch((yyvsp[-3].value.trueList), (yyvsp[-1].inst)->next);
            (yyval.value.trueList) = (yyvsp[0].value.trueList);
            (yyval.value.falseList) = merge((yyvsp[-3].value.falseList), (yyvsp[0].value.falseList));
            (yyval.value.nextList) = 0;
            (yyval.value.valType) = 0;
          }
#line 2030 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 537 "Simple.y" /* yacc.c:1646  */
    {
            backpatch((yyvsp[-3].value.falseList), (yyvsp[-1].inst)->next);
            (yyval.value.trueList) = merge((yyvsp[-3].value.trueList), (yyvsp[0].value.trueList));
            (yyval.value.falseList) = (yyvsp[0].value.falseList);
            (yyval.value.nextList) = 0;
            (yyval.value.valType) = 0;
          }
#line 2042 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 544 "Simple.y" /* yacc.c:1646  */
    {
            if((yyvsp[-2].value.valType) == 3 || (yyvsp[-2].value.valType) == 4){
              int temp;
              if((yyvsp[0].value.valType) == 3){
                temp = newTemp();
                genIRForLS(lwi, temp, (yyvsp[0].value.offset), (yyvsp[0].value.id));
              }
              else if((yyvsp[0].value.valType) == 4){
                temp = newTemp();
                genIRForLS(lw, temp, (yyvsp[0].value.offset), (yyvsp[0].value.id));
              }
              else if((yyvsp[0].value.valType) == 2){
                temp = (yyvsp[0].value.temp);
              }
              else if((yyvsp[0].value.valType) == 1){
                temp = newTemp();
                genIR(li, 0, (yyvsp[0].value.temp), temp);
              }
              else{
                printf("should not enter here!\n");
              }
              if((yyvsp[-2].value.valType) == 3) genIRForLS(swi, temp, (yyvsp[-2].value.offset), (yyvsp[-2].value.id));
              else genIRForLS(sw, temp, (yyvsp[-2].value.offset), (yyvsp[-2].value.id));
            }
            else {
              printf("wrong while assign!\n");
            }
          }
#line 2075 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 583 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.value.trueList) = (yyvsp[0].value.falseList);
            (yyval.value.falseList) = (yyvsp[0].value.trueList);
            (yyval.value.nextList) = 0;
            (yyval.value.valType) = 0;
          }
#line 2086 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 592 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.value) = (yyvsp[-1].value);
          }
#line 2094 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 595 "Simple.y" /* yacc.c:1646  */
    {
            int i;
            struct NSData* temp;
            struct symrec *fun = getsym((yyvsp[-3].id));
            if(fun != 0){
              for(i=(yyvsp[-1].intval)-1;i >= 0 ;i--){
                temp = NSPop();
                if(temp->valType == 1){
                  int tempReg = newTemp();
                  genIR(li, 0, temp->temp, tempReg);
                  genIRForLS(param, tempReg, 0, 0);
                }
                else if(temp->valType == 2){
                  genIRForLS(param, temp->temp, 0, 0);
                }
              }
              genIRForBranch(call, 0, 0, fun->entry);
              (yyval.value.valType) = 2;
              (yyval.value.temp) = newTemp();
            }
            else{
              printf("wrong while call func!\n");
            }
          }
#line 2123 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 619 "Simple.y" /* yacc.c:1646  */
    {
            // $<value.valType>$ = 2;
            if((yyvsp[0].value.valType) == 1){
              (yyval.value.valType) = 3;
              (yyval.value.id) = (yyvsp[-1].id);
              (yyval.value.offset) = (yyvsp[0].value.temp);
              // genIRForLS(lwi, temp, $<value.temp>2, $1);
            }
            else if((yyvsp[0].value.valType) == 2){
              (yyval.value.valType) = 4;
              (yyval.value.id) = (yyvsp[-1].id);
              (yyval.value.offset) = (yyvsp[0].value.temp);
              // genIRForLS(lw, temp, $<value.temp>2, $1);
            }
            else{
              printf("wrong while array reference\n");
            }
            // $<value.temp>$ = temp;
          }
#line 2147 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 638 "Simple.y" /* yacc.c:1646  */
    {
            struct symrec * os;
            (yyval.value.valType) = 3;
            struct symrec * structVar = getsym((yyvsp[-2].id));
            struct symrec * base = getsym(structVar->type);
            if(base == 0) printf("not defined type in struct variable!\n");
            else{
              os = getsymWithinScope((yyvsp[0].id), base->scope);
            }
            (yyval.value.id) = (yyvsp[-2].id);
            (yyval.value.offset) = os->offset;
            // genIRForLS(lwi, temp, os->offset, structVar->name);
          }
#line 2165 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 651 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.value.valType) = 1;
            (yyval.value.temp) = (yyvsp[0].intval);
          }
#line 2174 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 657 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.inst) = IR->tail;
          }
#line 2182 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 662 "Simple.y" /* yacc.c:1646  */
    {
            (yyval.value.valType) = 1;
            (yyval.value.temp) = 0;
          }
#line 2191 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 666 "Simple.y" /* yacc.c:1646  */
    {
            if((yyvsp[-1].value.valType) == 1){
              (yyval.value.valType) = 1;
              (yyval.value.temp) = (yyvsp[-1].value.temp)*4;
            }
            else if((yyvsp[-1].value.valType) == 2){
              (yyval.value.valType) = 2;
              int temp = newTemp();
              genIR(muli, (yyvsp[-1].value.temp), 4, temp);
              (yyval.value.temp) = temp;
            }
            else{
              printf("wrong! while arrs 2\n");
            }
          }
#line 2211 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 681 "Simple.y" /* yacc.c:1646  */
    {
            struct symrec * array = getsym((yyvsp[-6].id));
            if((yyvsp[-4].value.valType) == 1 && (yyvsp[-1].value.valType) == 1){
              (yyval.value.valType) = 1;
              (yyval.value.temp) = array->width * (yyvsp[-4].value.temp) * 4 + (yyvsp[-1].value.temp) * 4;
            }
            else if((yyvsp[-4].value.valType) == 2 && (yyvsp[-1].value.valType) == 2){
              int temp1 = newTemp();
              int temp2 = newTemp();
              int temp3 = newTemp();
              genIR(muli, (yyvsp[-4].value.temp), array->width * 4, temp1);
              genIR(muli, (yyvsp[-1].value.temp), 4, temp2);
              genIR(add, temp1, temp2, temp3);
              (yyval.value.valType) = 2;
              (yyval.value.temp) = temp3;
            }
            else{
              if((yyvsp[-4].value.valType) == 2){
                int temp1 = newTemp();
                int temp3 = newTemp();
                genIR(muli, (yyvsp[-4].value.temp), array->width * 4, temp1);
                genIR(addi, temp1, (yyvsp[-1].value.temp) * 4, temp3);
                (yyval.value.valType) = 2;
                (yyval.value.temp) = temp3;
              }
              else{
                int temp2 = newTemp();
                int temp3 = newTemp();
                genIR(muli, (yyvsp[-1].value.temp), 4, temp2);
                genIR(add, temp2, array->width * 4 * (yyvsp[-4].value.temp), temp3);
                (yyval.value.valType) = 2;
                (yyval.value.temp) = temp3;
              }
            }
          }
#line 2251 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 718 "Simple.y" /* yacc.c:1646  */
    {
            NSPush((struct NSData *)&(yyvsp[0].value));
            (yyval.intval) = (yyvsp[-2].intval) + 1;
          }
#line 2260 "Simple.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 722 "Simple.y" /* yacc.c:1646  */
    {
            NSPush((struct NSData *)&(yyvsp[0].value));
            (yyval.intval) = 1;
          }
#line 2269 "Simple.tab.c" /* yacc.c:1646  */
    break;


#line 2273 "Simple.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 728 "Simple.y" /* yacc.c:1906  */

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
  initIR();
  yyparse();
  endIR();
  printf("Parse Completed\n");
  printST();
  printf("%s\n", "=========================================================================");
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
