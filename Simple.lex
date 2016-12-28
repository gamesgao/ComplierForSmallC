/***************************************************************************
Scanner for the SmallC language
***************************************************************************/

%{

/*=========================================================================
C-libraries and Token definitions
=========================================================================*/

#include <string.h> /* for strdup */
/*#include <stdlib.h> */ /* for atoi */
#include "Simple.tab.h" /* for token definitions and yylval */

%}

/*=========================================================================
TOKEN Definitions
=========================================================================*/

NONDIGIT    ([_A-Za-z])
DIGIT       [0-9]
INTEGER     (({DIGIT}+)|(0x|0X|0)[0-9a-fA-F]+)
IDENTIFIER          ({NONDIGIT}({NONDIGIT}|{DIGIT})*)

/*=========================================================================
REGULAR EXPRESSIONS defining the tokens for the Simple language
=========================================================================*/

%%
INTEGER     {
    return INT;
}

IDENTIFIER  {
    return ID;
}

;           {
    return SEMI;
}

\.          {
    return COMMA;
}

\*          {
    return BINARYOP_MUL;
}

\/          {
    return BINARYOP_DIV;
}

\%          {
    return BINARYOP_MOD;
}

\+          {
    return BINARYOP_ADD;
}              

\-          {
    return BINARYOP_MIN;
}

<<          {
    return BINARYOP_SHL;
}

>>          {
    return BINARYOP_SHR;
}

>           {
    return BINARYOP_GT;
}

>=          {
    return BINARYOP_NLT;
}

<           {
    return BINARYOP_LT;
}

<=          {
    return BINARYOP_NGT;
}

==          {
    return BINARYOP_EQ;
}

!=          {
    return BINARYOP_NEQ
}

&           {
    return BINARYOP_BAND;
}

\^          {
    return BINARYOP_BXOR;
}

\|          {
    return BINARYOP_BOR;
}

&&          {
    return BINARYOP_LAND;
}

\|\|        {
    return BINARYOP_LOR;
}

=           {
    return BINARYOP_ASSIGN;
}

\+=         {
    return BINARYOP_ADDA;
}

-=          {
    return BINARYOP_MINA;
}

\*=         {
    return BINARYOP_MULA;
}

\/=         {
    return BINARYOP_DIVA;
}

&=          {
    return BINARYOP_BANDA;
}

\^=         {
    return BINARYOP_BXORA;
}

\|=         {
    return BINARYOP_BORA;
}

<<=         {
    return BINARYOP_SHLA;
}

>>=         {
    return BINARYOP_SHRA;
}

-           {
    return UNARYOP_NEG;
}

!           {
    return UNARYOP_LNOT;
}

\+\+        {
    return UNARYOP_INCR;
}

--          {
    return UNARYOP_DECR;
}

~           {
    return UNARYOP_BNOT;
}

int         {
    return TYPE;
}

\(          {
    return LP;
}

\)          {
    return RP;
}

\[          {
    return LB;
}

\]          {
    return RB;
}

\{          {
    return LC;
}

\}          {
    return RC;
}

struct      {
    return STRUCT;
}

return      {
    return RETURN;
}

if          {
    return IF;
}

else        {
    return ELSE;
}

break       {
    return BREAK;
}

continue    {
    return CONT;
}

for         {
    return FOR;
}


{DIGIT}+ { yylval.intval = atoi( yytext );return(NUMBER); }
{ID} { yylval.id = (char *) strdup(yytext);return(IDENTIFIER); }

[ \t\n]+ /* eat up whitespace */
. { return(yytext[0]);}
%%
int yywrap(void){}
/************************** End Scanner File *****************************/