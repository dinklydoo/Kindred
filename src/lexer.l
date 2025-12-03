%option noyywrap

%{
#include <iostream>
#include "ast.hpp"
#include "parser.hpp"

#define YY_DECL yy::parser::symbol_type yylex()

%}

%%

[ \n\t]+ {}
= { return yy::parser::make_ASSGN(); }
\+ { return yy::parser::make_ADD(); }
\* { return yy::parser::make_MUL(); }
- { return yy::parser::make_SUB(); }
\/ { return yy::parser::make_DIV(); }
\% { return yy::parser::make_MOD(); }
\/\/ { return yy::parser::make_FLR(); }
\*\* { return yy::parser::make_POW(); }
& { return yy::parser::make_LAND(); }
\| {return yy::parser::make_LOR(); }
^ {return yy::parser::make_LXOR(); }
! {return yy::parser::make_LNOT(); }
>> {return yy::parser::make_LSR(); }
<< {return yy::parser::make_LSL(); }
> {return yy::parser::make_CGT(); }
< {return yy::parser::make_CLT(); }
>= {return yy::parser::make_CGEQ(); }
<= {return yy::parser::make_CLEQ(); }
== {return yy::parser::make_CEQ(); }
!= {return yy::parser::make_CNEQ(); }
\+\+ {return yy::parser::make_CONCAT(); }
case { return yy::parser::make_CASE(); }
of { return yy::parser::make_OF(); }
=> {return yy::parser::make_ARROW(); }
\[\] {return yy::parser::make_NIL(); }
default {return yy::parser::make_DEFAULT(); }
\#declare {return yy::parser::make_DECLARE(); }
\#include {return yy::parser::make_INCLUDE(); }
func {return yy::parser::make_FUNC(); }
: {return yy::parser::make_TSEP(); }
\( {return yy::parser::make_LBRA(); }
\) {return yy::parser::make_RBRA(); }
\[ {return y::parser::make_SQ_LBRA(); }
\] {return y::parser::make_SQ_RBRA(); }
@ {return yy::parser::make_COM_SING(); }
@\* {return yy::parser::make_COM_LMUL(); }
\*@ {return yy::parser::make_COM_RMUL(); }
lamb {return yy::parser::make_LAMB(); }
bool {return yy::parser::make_T_BOOL(); }
char {return yy::parser::make_T_CHAR(); }
int {return yy::parser::make_T_INT(); }
long {return yy::parser::make_T_LONG(); }
float {return yy::parser::make_T_FLOAT(); }
double {return yy::parser::make_T_DOUBLE(); }
struct {return yy::parser::make_STRUCT(); }
enum {return yy::parser::make_ENUM(); }
true {return yy::parser::make_TRUE(); }
false {return yy::parser::make_FALSE(); }
. {return yy::parser::make_DOT(); }
, {return yy::parser::make_COMMA(); }
' {return yy::parser::make_QUOTE(); }
[0-9]+ { return yy::parser::make_INT(atoi(yytext)); }
[a-zA-Z_][a-zA-Z0-9_]* { return yy::parser::make_LABEL(std::string(yytext)); }

%%
