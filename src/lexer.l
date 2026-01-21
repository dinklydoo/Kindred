%option noyywrap

%{
#include <iostream>
#include <string>
#include <stdexcept>
#include "parser.hpp"

void error(const std::string &msg) {
    std::string text_snippet(yytext, yyleng);
    throw std::runtime_error(
        "Lexical error at line " + std::to_string(yylineno) +
        ": " + msg + " (near \"" + text_snippet + "\")"
    );
}

std::string strbuf;
char charbuf;

#undef YY_DECL
#define YY_DECL yy::parser::symbol_type yylex()

%}

%x MCOMMENT SCOMMENT STRING CHAR CHAR_END

/* string chars \xHEX */
/* valid escape chars: /' /" /? /t /n */
HEX [0-9a-fA-F]{2}
ESCAPE \\([\\'"?tn]|HEX)

%%
"@*"            { BEGIN(MCOMMENT); }
<MCOMMENT>"*@"  { BEGIN(INITIAL); }
<MCOMMENT>.|\n  { }
<MCOMMENT><<EOF>> { BEGIN(INITIAL); }

"@" { BEGIN(SCOMMENT); }
<SCOMMENT>. { }
<SCOMMENT>\n { BEGIN(INITIAL); }

[ \t\n]+        { }

"//"            { return yy::parser::make_FLR(); }
"**"            { return yy::parser::make_POW(); }
">="            { return yy::parser::make_CGEQ(); }
"<="            { return yy::parser::make_CLEQ(); }
"=="            { return yy::parser::make_CEQ(); }
"!="            { return yy::parser::make_CNEQ(); }
"<<"            { return yy::parser::make_LSL(); }
">>"            { return yy::parser::make_LSR(); }
"=>"            { return yy::parser::make_ARROW(); }
"->"            { return yy::parser::make_PROD(); }
"++"            { return yy::parser::make_CONCAT(); }
"&&"             { return yy::parser::make_BAND(); }
"||"             { return yy::parser::make_BOR(); }

"="             { return yy::parser::make_ASSGN(); }
"+"             { return yy::parser::make_ADD(); }
"-"             { return yy::parser::make_SUB(); }
"*"             { return yy::parser::make_MUL(); }
"/"             { return yy::parser::make_DIV(); }
"%"             { return yy::parser::make_MOD(); }
"&"             { return yy::parser::make_LAND(); }
"|"             { return yy::parser::make_BAR(); }
"^"             { return yy::parser::make_LXOR(); }
"!"             { return yy::parser::make_BNOT(); }
"~"             { return yy::parser::make_LNEG(); }
">"             { return yy::parser::make_CGT(); }
"<"             { return yy::parser::make_CLT(); }

";"             { return yy::parser::make_PEND(); }
":"             { return yy::parser::make_TSEP(); }
"("             { return yy::parser::make_LBRA(); }
")"             { return yy::parser::make_RBRA(); }
"["             { return yy::parser::make_SQ_LBRA(); }
"]"             { return yy::parser::make_SQ_RBRA(); }
","             { return yy::parser::make_COMMA(); }
"."             { return yy::parser::make_DOT(); }

"case"        { return yy::parser::make_CASE(); }
"mark"        { return yy::parser::make_MARK(); }
"of"          { return yy::parser::make_OF(); }
"default"     { return yy::parser::make_DEFAULT(); }
"else"        { return yy::parser::make_ELSE(); }
"func"        { return yy::parser::make_FUNC(); }
"struct"      { return yy::parser::make_STRUCT(); }
"enum"        { return yy::parser::make_ENUM(); }
"true"        { return yy::parser::make_TRUE(); }
"false"       { return yy::parser::make_FALSE(); }
"return"       { return yy::parser::make_RETURN(); }
"read"       { return yy::parser::make_READ(); }
"print"       { return yy::parser::make_PRINT(); }

[0-9]+\.[0-9]+  { return yy::parser::make_FLOAT(std::stod(yytext)); }
[0-9]+          { return yy::parser::make_INT(std::stol(yytext)); }

[a-zA-Z_][a-zA-Z0-9_]* {
    return yy::parser::make_LABEL(yytext);
}

\" { strbuf.clear(); BEGIN(STRING); }
\' { BEGIN(CHAR); }


<STRING>{
    \" { BEGIN(INITIAL); return yy::parser::make_STRING(strbuf); }
    \\n { strbuf += '\n'; }
    \\t { strbuf += '\t'; }
    \\' { strbuf += '\''; }
    \\\" { strbuf += '\"'; }
    \\? { strbuf += '\?'; }
    \\\\ { strbuf += '\\'; }
    \\x{HEX} { strbuf += (char)strtol(yytext+2, NULL, 16); }

    [^\\\"\n]+ {
        strbuf.append(yytext, yyleng);
    }

    \n  { error("newline in string literal"); }
    \\x. {error("invalid hex escape (expected two hex digits)");}
    \\. { error("invalid escape sequence in string"); }
    <<EOF>> { error("unterminated string literal"); }
}

<CHAR>{
    \\n { charbuf = '\n'; BEGIN(CHAR_END); }
    \\t { charbuf = '\t'; BEGIN(CHAR_END); }
    \\' { charbuf = '\''; BEGIN(CHAR_END); }
    \\\" { charbuf = '\"'; BEGIN(CHAR_END); }
    \\? { charbuf = '\?'; BEGIN(CHAR_END); }
    \\\\ { charbuf = '\\'; BEGIN(CHAR_END); }
    \\x{HEX} { charbuf = (char)strtol(yytext+2, NULL, 16); BEGIN(CHAR_END); }
    [^\\\'\n] {
        charbuf = yytext[0]; BEGIN(CHAR_END);
    }
    \' { error("empty character value"); }
    \n  { error("newline in char literal"); }
    \\x. {error("invalid hex escape (expected two hex digits)");}
    \\. { error("invalid escape sequence in char"); }
    <<EOF>> { error("unterminated char literal"); }
}

<CHAR_END>{
    \' { BEGIN(INITIAL); return yy::parser::make_CHAR(charbuf); }
    . { error("expected char closing quotation"); }
}

%%