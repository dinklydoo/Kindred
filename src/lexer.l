%option noyywrap
%option yylineno

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

    int yycolno = 1;

    #undef YY_DECL
    #define YY_DECL yy::parser::symbol_type yylex()

    yy::location make_location(int length){
        yy::location loc;

        yy::position beg(YY_NULLPTR, yylineno, yycolno);
        yycolno += length;
        yy::position end(YY_NULLPTR, yylineno, yycolno);

        loc.begin = beg;
        loc.end = end;
        return loc;
    }
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

[ \t]+          { }
\n              { yycolno = 1; }

"//"            { return yy::parser::make_FLR(make_location(yyleng)); }
"**"            { return yy::parser::make_POW(make_location(yyleng)); }
">="            { return yy::parser::make_CGEQ(make_location(yyleng)); }
"<="            { return yy::parser::make_CLEQ(make_location(yyleng)); }
"=="            { return yy::parser::make_CEQ(make_location(yyleng)); }
"!="            { return yy::parser::make_CNEQ(make_location(yyleng)); }
"<<"            { return yy::parser::make_LSL(make_location(yyleng)); }
">>"            { return yy::parser::make_LSR(make_location(yyleng)); }
"=>"            { return yy::parser::make_ARROW(make_location(yyleng)); }
"->"            { return yy::parser::make_PROD(make_location(yyleng)); }
"++"            { return yy::parser::make_CONCAT(make_location(yyleng)); }
"&&"             { return yy::parser::make_BAND(make_location(yyleng)); }
"||"             { return yy::parser::make_BOR(make_location(yyleng)); }

"="             { return yy::parser::make_ASSGN(make_location(yyleng)); }
"+"             { return yy::parser::make_ADD(make_location(yyleng)); }
"-"             { return yy::parser::make_SUB(make_location(yyleng)); }
"*"             { return yy::parser::make_MUL(make_location(yyleng)); }
"/"             { return yy::parser::make_DIV(make_location(yyleng)); }
"%"             { return yy::parser::make_MOD(make_location(yyleng)); }
"&"             { return yy::parser::make_LAND(make_location(yyleng)); }
"|"             { return yy::parser::make_BAR(make_location(yyleng)); }
"^"             { return yy::parser::make_LXOR(make_location(yyleng)); }
"!"             { return yy::parser::make_BNOT(make_location(yyleng)); }
"~"             { return yy::parser::make_LNEG(make_location(yyleng)); }
">"             { return yy::parser::make_CGT(make_location(yyleng)); }
"<"             { return yy::parser::make_CLT(make_location(yyleng)); }

";"             { return yy::parser::make_PEND(make_location(yyleng)); }
":"             { return yy::parser::make_TSEP(make_location(yyleng)); }
"("             { return yy::parser::make_LBRA(make_location(yyleng)); }
")"             { return yy::parser::make_RBRA(make_location(yyleng)); }
"["             { return yy::parser::make_SQ_LBRA(make_location(yyleng)); }
"]"             { return yy::parser::make_SQ_RBRA(make_location(yyleng)); }
"{"             { return yy::parser::make_C_LBRA(make_location(yyleng)); }
"}"             { return yy::parser::make_C_RBRA(make_location(yyleng)); }
","             { return yy::parser::make_COMMA(make_location(yyleng)); }
"."             { return yy::parser::make_DOT(make_location(yyleng)); }

"nil"         { return yy::parser::make_NIL(make_location(yyleng)); }
"case"        { return yy::parser::make_CASE(make_location(yyleng)); }
"mark"        { return yy::parser::make_MARK(make_location(yyleng)); }
"of"          { return yy::parser::make_OF(make_location(yyleng)); }
"default"     { return yy::parser::make_DEFAULT(make_location(yyleng)); }
"else"        { return yy::parser::make_ELSE(make_location(yyleng)); }
"func"        { return yy::parser::make_FUNC(make_location(yyleng)); }
"struct"      { return yy::parser::make_STRUCT(make_location(yyleng)); }
"enum"        { return yy::parser::make_ENUM(make_location(yyleng)); }
"true"        { return yy::parser::make_TRUE(make_location(yyleng)); }
"false"       { return yy::parser::make_FALSE(make_location(yyleng)); }
"return"       { return yy::parser::make_RETURN(make_location(yyleng)); }
"read"       { return yy::parser::make_READ(make_location(yyleng)); }
"print"       { return yy::parser::make_PRINT(make_location(yyleng)); }

[0-9]+\.[0-9]+  { return yy::parser::make_FLOAT(std::stod(yytext), make_location(yyleng)); }
[0-9]+          { return yy::parser::make_INT(std::stol(yytext), make_location(yyleng)); }

[a-zA-Z_][a-zA-Z0-9_]* {
    return yy::parser::make_LABEL(yytext, make_location(yyleng));
}

\" { strbuf.clear(); BEGIN(STRING); }
\' { BEGIN(CHAR); }


<STRING>{
    \" { BEGIN(INITIAL); return yy::parser::make_STRING(strbuf, make_location(yyleng)); }
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
    \' { BEGIN(INITIAL); return yy::parser::make_CHAR(charbuf, make_location(yyleng)); }
    . { error("expected char closing quotation"); }
}

<<EOF>> { return yy::parser::make_KEOF(make_location(yyleng)); }

%%