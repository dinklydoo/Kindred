%option noyywrap
%option c++

%x MCOMMENT

%{
#include <iostream>
#include "tokens.hpp"

#undef YY_DECL
#define YY_DECL Token yyFlexLexer::yylex()
%}

%%
"@"[^\n]* {}
"@*" { BEGIN(MCOMMENT) }
<MCOMMENT>"*@" { BEGIN(INITIAL); }
<MCOMMENT>\n   {}
<MCOMMENT>.    {}
<MCOMMENT><<EOF>> {
    /* optional: report error */
    BEGIN(INITIAL);
}

[ \n\t]+ {}
= { return make_token(TokenType::ASSGN); }
\+ { return make_token(TokenType::ADD); }
\* { return make_token(TokenType::MUL); }
- { return make_token(TokenType::SUB); }
\/ { return make_token(TokenType::DIV); }
\% { return make_token(TokenType::MOD); }
\/\/ { return make_token(TokenType::FLR); }
\*\* { return make_token(TokenType::POW); }
& { return make_token(TokenType::LAND); }
\| { return make_token(TokenType::LOR); }
>= { return make_token(TokenType::CGEQ); }
\<= { return make_token(TokenType::CLEQ); }
== { return make_token(TokenType::CEQ); }
!= { return make_token(TokenType::CNEQ); }
\^ { return make_token(TokenType::LXOR); }
! { return make_token(TokenType::LNOT); }
~ { return make_token(TokenType::LNEG); }
>> { return make_token(TokenType::LSR); }
\<< { return make_token(TokenType::LSL); }
> { return make_token(TokenType::CGT); }
\< { return make_token(TokenType::CLT); }
\+\+ { return make_token(TokenType::CONCAT); }
case { return make_token(TokenType::CASE); }
of { return make_token(TokenType::OF); }
=> { return make_token(TokenType::ARROW); }
\[\] { return make_token(TokenType::EMPTY); }
default { return make_token(TokenType::DEFAULT); }
\#declare { return make_token(TokenType::DECLARE); }
\#include { return make_token(TokenType::INCLUDE); }
func { return make_token(TokenType::FUNC); }
: { return make_token(TokenType::TSEP); }
\( { return make_token(TokenType::LBRA); }
\) { return make_token(TokenType::RBRA); }
\[ { return make_token(TokenType::SQ_LBRA); }
\] { return make_token(TokenType::SQ_RBRA); }
main { return make_token(TokenType::MAIN); }
lamb { return make_token(TokenType::LAMB); }
bool { return make_token(TokenType::T_BOOL); }
char { return make_token(TokenType::T_CHAR); }
int { return make_token(TokenType::T_INT); }
long { return make_token(TokenType::T_LONG); }
float { return make_token(TokenType::T_FLOAT); }
double { return make_token(TokenType::T_DOUBLE); }
nil { return make_token(TokenType::NIL); }
struct { return make_token(TokenType::STRUCT); }
enum { return make_token(TokenType::ENUM); }
true { return make_token(TokenType::TRUE); }
false { return make_token(TokenType::FALSE); }
read { return make_token(TokenType::READ); }
print { return make_token(TokenType::PRINT); }
\. { return make_token(TokenType::DOT); }
, { return make_token(TokenType::COMMA); }
\'([^']*)\' {
    std::string s(yytext + 1, yyleng - 2);
    return make_token(TokenType::STRING, s);
}
[0-9]+ { return make_token(TokenType::INT, atol(yytext) ); }
[0-9]*\.[0-9]+ { return make_token(TokenType::FLOAT, atof(yytext) ); }
[a-zA-Z_][a-zA-Z0-9_]* { return make_token(TokenType::LABEL, std::string(yytext) ); }
<<EOF>>                  { return make_token(TokenType::EOF); }

%%