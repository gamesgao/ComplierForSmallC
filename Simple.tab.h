/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 61 "Simple.y" /* yacc.c:1909  */
union semrec
{
#line 62 "Simple.y" /* yacc.c:1909  */

  int intval;       /* Integer values */
  char *id;         /* Identifiers */
  struct lbs *lbls; /* For backpatching */

#line 116 "Simple.tab.h" /* yacc.c:1909  */
};
#line 61 "Simple.y" /* yacc.c:1909  */
typedef union semrec YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SIMPLE_TAB_H_INCLUDED  */
