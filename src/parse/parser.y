%code requires {
    #include <string>
    #include "ast.hpp"
}

%{
    #include <iostream>
    #include "parser.hpp"

    static TypeSystem& type_s = TypeSystem::instance();

    expr_ptr str_to_chlist(std::string s){
        std::vector<expr_ptr> chars;
        for (char c : s){
            auto temp = std::make_unique<CharLit>();
            temp->value = c;
            chars.push_back(std::move(temp));
        }
        auto list = std::make_unique<ListNode>();
        list->elems = std::move(chars);
        return list;
    }

    Source floc_to_loc(yy::location floc){
        Source loc;
        loc.line = floc.begin.line;
        loc.col = floc.begin.column;
        return loc;
    }

    module_ptr module_node;
    extern yy::parser::symbol_type yylex();
%}

%language "c++"
%require "3.2"
%define api.value.type variant
%define api.token.constructor
%define api.namespace {yy}
%define api.parser.class {parser}
%locations

/* literals / identifiers */
%token <uint64_t> INT
%token <double> FLOAT
%token <char> CHAR
%token <std::string> STRING
%token <std::string> LABEL

/* keywords */
%token CASE OF DEFAULT FUNC LAMB MARK ELSE
%token STRUCT ENUM
%token TRUE FALSE NIL
%token READ PRINT
%token RETURN
%token T_INT T_LONG T_FLOAT T_DOUBLE T_CHAR T_BOOL

/* punctuation */
%token LBRA RBRA 
%token SQ_LBRA SQ_RBRA
%token C_LBRA C_RBRA
%token COMMA DOT TSEP
%token EMPTY
%token KEOF 0
%token PEND

/* operators */
%token ASSGN
%token ADD SUB MUL DIV MOD
%token POW
%token FLR
%token LAND BAR LXOR
%token LNEG
%token CGT CLT CGEQ CLEQ CEQ CNEQ
%token LSL LSR
%token BAND BOR BNOT
%token CONCAT
%token ARROW
%token PROD

%type <module_ptr> module
%type <prog_ptr> program

/* Type Patterns */
%type <type_ptr> type
%type <type_ptr> non_function_type
%type <std::vector<type_ptr>> opt_types
%type <std::vector<type_ptr>> types
%type <type_ptr> literal_type
%type <type_ptr> list_type
%type <type_ptr> func_type
%type <type_ptr> nominal_type
%type <type_ptr> int_lit_type
%type <type_ptr> float_lit_type

%type <decl_ptr> definition
%type <std::vector<decl_ptr>> definitions

/* Func Patterns */
%type <Param> param;
%type <std::vector<Param>> opt_params
%type <std::vector<Param>> params
%type <func_decl_ptr> function_def

/* Struct Patterns */
%type <Field> field;
%type <std::vector<Field>> fields;
%type <struct_decl_ptr> struct_def

/* Enum Patterns */
%type <std::string> evar;
%type <std::vector<std::string>> evars;
%type <enum_decl_ptr> enum_def

/* Control Flow Expressions */
%type <std::vector<decl_ptr>> helpers;
%type <decl_ptr> helper_expr;
%type <print_ptr> print_expr;
%type <decl_ptr> assign_expr;

%type <expr_ptr> branch_expr;

%type <case_ptr> case_expr;
%type <std::vector<c_branch_ptr>> patterns;
%type <c_branch_ptr> pattern_branch;
%type <literal_ptr> literal;
%type <literal_ptr> pattern;
%type <literal_ptr> list_pattern;
%type <literal_ptr> list_size_pattern;
%type <literal_ptr> size_pattern
%type <std::vector<std::string>> list_vars;

%type <literal_ptr> struct_size_pattern
%type <std::vector<std::string>> struct_vars;

%type <guard_ptr> guard_expr;
%type <std::vector<g_branch_ptr>> guards
%type <g_branch_ptr> guard

%type <expr_ptr> return_expr;

/* Literal Expressions */
%type <literal_ptr> int_lit;
%type <literal_ptr> float_lit;
%type <literal_ptr> bool_lit;
%type <literal_ptr> char_lit;
%type <literal_ptr> enum_lit;

%type <BinaryOp> bitwise_op;
%type <BinaryOp> shift_op;
%type <BinaryOp> additive_op;
%type <BinaryOp> mult_op;
%type <UnaryOp> unary_op;
%type <BinaryOp> comp_op;
%type <BinaryOp> bool_op;

/* List Expression Patterns */
%type <expr_ptr> list_expr;
%type <expr_ptr> string_expr;
%type <list_ptr> empty_list
%type <list_ptr> list_con;
%type <std::vector<expr_ptr>> expr_list;

/* Operational Expressions */
%type <expr_ptr> assign_val_expr;
%type <expr_ptr> value_expr;
%type <expr_ptr> bool_expr;
%type <expr_ptr> comp_expr;
%type <expr_ptr> bitwise_expr;
%type <expr_ptr> shift_expr;
%type <expr_ptr> additive_expr;
%type <expr_ptr> mult_expr;
%type <expr_ptr> pow_expr;
%type <expr_ptr> unary_expr;
%type <expr_ptr> postfix_expr;
%type <expr_ptr> literal_expr;
%type <expr_ptr> struct_expr;
%type <expr_ptr> nominal_expr;

%start module

%%

module
    : definitions KEOF
        { 
            $$ = std::make_unique<ModuleNode>();
            $$->decl = std::move($1);
            module_node = std::move($$);
        }
    ;

definitions
    : %empty
        { $$ = std::vector<decl_ptr>{}; }
    | definitions definition
        { 
            $1.push_back(std::move($2));
            $$ = std::move($1);
        }
    ;

definition
    : function_def{ $$ = std::move($1); }
    | struct_def{ $$ = std::move($1); }
    | enum_def{ $$ = std::move($1); };

opt_types
    : %empty { $$ = std::vector<type_ptr>{}; }
    | types { $$ = std::move($1); };

types
    : type { $$ = std::vector<type_ptr>{$1}; }
    | types COMMA type {
        $1.push_back(std::move($3));
        $$ = std::move($1);
    };

non_function_type
    : literal_type { $$ = std::move($1); }
    | list_type { $$ = std::move($1); }
    | nominal_type { $$ = std::move($1); }
    ;

type
    : non_function_type { $$ = std::move($1); }
    | func_type { $$ = std::move($1); }
    ;

literal_type
    : T_CHAR { $$ = type_s.char_type(); }
    | T_BOOL { $$ = type_s.bool_type(); }
    | int_lit_type { $$ = std::move($1); }
    | float_lit_type { $$ = std::move($1); }
    ;

int_lit_type
    : T_INT { $$ = type_s.int_type(); }
    | T_LONG { $$ = type_s.long_type(); };

float_lit_type
    : T_FLOAT { $$ = type_s.float_type(); }
    | T_DOUBLE { $$ = type_s.double_type(); };

list_type
    : SQ_LBRA type SQ_RBRA { $$ = type_s.list_type($2); };

func_type
    : LBRA opt_types RBRA PROD type { $$ = type_s.func_type($2, $5); }; 

nominal_type
    : LABEL { $$ = type_s.nominal_type($1); };

opt_params
    : TSEP { $$ = std::vector<Param>{}; }
    | params { $$ = std::move($1); };

params
    : param { $$ = std::vector<Param>{$1}; }
    | params COMMA param
        {
            $1.push_back(std::move($3));
            $$ = std::move($1);
        };

param
    : LABEL TSEP type
        { 
            $$ = Param(); 
            $$.name = std::move($1);
            $$.type = std::move($3);
            $$.location = floc_to_loc(@1);
        }
    ;

function_def
    : FUNC LABEL LBRA opt_params RBRA TSEP type program
        {   
            $$ = std::make_unique<FuncDecl>();
            $$->name = std::move($2);
            $$->params = std::move($4);
            $$->ret = std::move($7);
            $$->body = std::move($8);

            $$->location = floc_to_loc(@1);
        }
    ;

fields
    : field
        {   $$ = std::vector<Field>{}; $$.push_back(std::move($1)); }
    | fields COMMA field
        { 
            $1.push_back(std::move($3));
            $$ = std::move($1);
        }
    ;

field
    : LABEL TSEP type
        {
            $$ = Field();
            $$.name = std::move($1);
            $$.type = std::move($3);

            $$.location = floc_to_loc(@1);
        };

struct_def
    : STRUCT LABEL LBRA fields RBRA
        {
            $$ = std::make_unique<StructDecl>();
            $$->name = std::move($2);
            $$->fields = std::move($4);

            $$->location = floc_to_loc(@1);
        }
    ;

evar
    : LABEL { $$ = std::move($1); };

evars
    : evar { $$ = std::vector<std::string>{$1}; }
    | evars COMMA evar 
        {
            $1.push_back(std::move($3));
            $$ = std::move($1);
        }
    ;

enum_def
    : ENUM LABEL LBRA evars RBRA
        { 
            $$ = std::make_unique<EnumDecl>(); 
            $$->name = std::move($2);
            $$->evar = std::move($4);

            $$->location = floc_to_loc(@1);
        }
    ;

program
    : helpers branch_expr
        {
            $$ = std::make_unique<ProgramNode>();
            $$->decl = std::move($1);
            $$->body = std::move($2);
        }   
    ;

branch_expr
    : return_expr { $$ = std::move($1); }
    | guard_expr { $$ = std::move($1); }
    | case_expr { $$ = std::move($1); }
    ;

guard_expr
    : CASE OF TSEP guards PEND
        {
            $$ = std::make_unique<GuardNode>();
            $$->branches = std::move($4);

            $$->location = floc_to_loc(@3);
        }
    ;

guards
    : guard
        { 
            $$ = std::vector<g_branch_ptr>{}; 
            $$.push_back(std::move($1));
        }
    | guards COMMA guard
        {
            $1.push_back(std::move($3));
            $$ = std::move($1);
        }
    ;

guard
    : BAR value_expr ARROW program
        {
            $$ = std::make_unique<GuardBranchNode>();
            $$->match = std::move($2);
            $$->body = std::move($4);

            $$->location = floc_to_loc(@3);
        }
    | BAR ELSE ARROW program
        {
            $$ = std::make_unique<GuardBranchNode>();
            //auto temp = std::make_unique<BoolLit>();
            //temp->value = true;
            //$$->match = std::move(temp);

            auto temp = std::make_unique<ElseLit>();
            $$->match = std::move(temp);
            $$->body = std::move($4);

            $$->location = floc_to_loc(@3);
        }
    ;

case_expr
    : MARK value_expr OF TSEP patterns PEND
        {
            $$ = std::make_unique<CaseNode>();
            $$->target = std::move($2);
            $$->patterns = std::move($5);

            $$->location = floc_to_loc(@3);
        }
    ;

patterns
    : pattern_branch 
        { 
            $$ = std::vector<c_branch_ptr>{}; 
            $$.push_back(std::move($1)); 
        }
    | patterns COMMA pattern_branch
        {
            $1.push_back(std::move($3));
            $$ = std::move($1);
        }
    ;

pattern_branch
    : pattern ARROW program
        {
            $$ = std::make_unique<CaseBranchNode>();
            $$->pattern = std::move($1);
            $$->pattern_type = false;
            $$->body = std::move($3);

            $$->location = floc_to_loc(@1);
        }
    | size_pattern ARROW program
        {
            $$ = std::make_unique<CaseBranchNode>();
            $$->pattern = std::move($1);
            $$->pattern_type = true;
            $$->body = std::move($3);

            $$->location = floc_to_loc(@1);
        }
    ;

literal
    : char_lit { $$ = std::move($1); }
    | int_lit { $$ = std::move($1); }
    | float_lit { $$ = std::move($1); }
    | bool_lit { $$ = std::move($1); }
    | enum_lit { $$ = std::move($1); }
    | list_pattern { $$ = std::move($1); }
    ;

size_pattern
    : list_size_pattern { $$ = std::move($1); }
    | struct_size_pattern { $$ = std::move($1); }

pattern
    : literal { $$ = std::move($1); }
    | DEFAULT { $$ = std::make_unique<DefaultLit>(); $$->location = floc_to_loc(@1);}
    | NIL { $$ = std::make_unique<NilLit>(); $$->location = floc_to_loc(@1);}
    ;

enum_lit
    : LABEL 
        { 
            auto temp = std::make_unique<EnumLit>();
            temp->elem = std::move($1); 
            $$ = std::move(temp);

            $$->location = floc_to_loc(@1);
        };

list_pattern
    : SQ_LBRA SQ_RBRA 
        { 
            $$ = std::make_unique<EmptyLit>();

            $$->location = floc_to_loc(@1);
        }
    ;

string_expr
    : STRING {$$ = str_to_chlist($1); $$->location = floc_to_loc(@1); };


list_size_pattern
    : list_vars
        {
            auto temp = std::make_unique<ListPatternLit>(); 
            temp->patterns = std::move($1);
            $$ = std::move(temp);

            $$->location = floc_to_loc(@1);
        }
    ;

list_vars
    : LABEL TSEP LABEL 
        { 
            $$ = std::vector<std::string>{};
            $$.push_back(std::move($1));
            $$.push_back(std::move($3)); 
        }
    | list_vars TSEP LABEL 
        {
            $1.push_back(std::move($3));
            $$ = std::move($1);
        }
    ;

struct_size_pattern
    : LABEL C_LBRA struct_vars C_RBRA
        {
            auto temp = std::make_unique<StructPatternLit>();
            temp->name = std::move($1);
            temp->patterns = std::move($3);
            $$ = std::move(temp);

            $$->location = floc_to_loc(@1);
        }
    ;

struct_vars
    : LABEL{ $$ = std::vector<std::string>{}; $$.push_back(std::move($1));}
    | NIL{ $$ = std::vector<std::string>{}; $$.push_back("@nil");}
    | struct_vars COMMA LABEL { $1.push_back(std::move($3)); $$ = std::move($1); }
    | struct_vars COMMA NIL { $1.push_back("@nil"); $$ = std::move($1); }
    ;

return_expr
    : RETURN value_expr 
        { 
            auto temp = std::make_unique<ReturnNode>();
            temp->rexp = std::move($2); 
            $$ = std::move(temp);

            $$->location = floc_to_loc(@1);
        }
    ;

helpers
    : %empty { $$ = std::vector<decl_ptr>{}; }
    | helpers helper_expr
        {
            $1.push_back(std::move($2));
            $$ = std::move($1);
        }
    ;

helper_expr
    : assign_expr { $$ = std::move($1); }
    | print_expr { $$ = std::move($1); }
    ;

print_expr
    : PRINT LBRA value_expr RBRA 
        { 
            $$ = std::make_unique<PrintNode>();
            $$->msg = std::move($3);

            $$->location = floc_to_loc(@1);
        }
    ;

assign_val_expr
    : value_expr { $$ = std::move($1); }
    | READ LBRA RBRA {
        $$ = std::make_unique<ReadNode>(); 
        $$->location = floc_to_loc(@1);
    }

assign_expr
    : LABEL TSEP LBRA opt_params RBRA PROD type LBRA program RBRA 
        { 
            auto temp = std::make_unique<FuncDecl>();
            temp->name = std::move($1);
            temp->params = std::move($4);
            temp->ret = std::move($7);
            temp->body = std::move($9);
            $$ = std::move(temp);

            $$->location = floc_to_loc(@1);
        }
    | LABEL TSEP type ASSGN assign_val_expr
        {
            auto temp = std::make_unique<VarDecl>();
            temp->name = std::move($1);
            temp->type = std::move($3);
            temp->r_val = std::move($5);
            $$ = std::move(temp);
            $$->location = floc_to_loc(@5);
        }
    ;

int_lit
    : INT 
        { 
            auto temp = std::make_unique<IntLit>();
            temp->value = $1;
            $$ = std::move(temp);

            $$->location = floc_to_loc(@1);
        };

float_lit
    : FLOAT 
        {
            auto temp = std::make_unique<FloatLit>();
            temp->value = $1;
            $$ = std::move(temp);

            $$->location = floc_to_loc(@1);
        };

bool_lit
    : TRUE 
        { 
            auto temp = std::make_unique<BoolLit>();
            temp->value = true;
            $$ = std::move(temp);

            $$->location = floc_to_loc(@1);
        }
    | FALSE
        { 
            auto temp = std::make_unique<BoolLit>();
            temp->value = false;
            $$ = std::move(temp);

            $$->location = floc_to_loc(@1);
        }
    ;

char_lit
    : CHAR 
        { 
            auto temp = std::make_unique<CharLit>();
            temp->value = $1;
            $$ = std::move(temp);

            $$->location = floc_to_loc(@1);
        }

bool_op
    : BOR { $$ = BinaryOp::BOR; }
    | BAND { $$ = BinaryOp::BAND; }
    ;

comp_op
    : CEQ { $$ = BinaryOp::CEQ; }
    | CNEQ { $$ = BinaryOp::CNEQ; }
    | CGT { $$ = BinaryOp::CGT; }
    | CLT { $$ = BinaryOp::CLT; }
    | CGEQ { $$ = BinaryOp::CGEQ; } 
    | CLEQ { $$ = BinaryOp::CLEQ; }
    ;

bitwise_op
    : LAND { $$ = BinaryOp::LAND; }
    | BAR { $$ = BinaryOp::LOR; }
    | LXOR { $$ = BinaryOp::LXOR; };

shift_op
    : LSL { $$ = BinaryOp::LSL; }
    | LSR { $$ = BinaryOp::LSR; };

additive_op
    : ADD { $$ = BinaryOp::ADD; }
    | SUB { $$ = BinaryOp::SUB; }
    | CONCAT { $$ = BinaryOp::CONCAT; }
    ;

mult_op
    : MUL { $$ = BinaryOp::MUL; }
    | DIV { $$ = BinaryOp::DIV; }
    | MOD { $$ = BinaryOp::MOD; }
    | FLR { $$ = BinaryOp::FLR; }
    ;

unary_op
    : BNOT { $$ = UnaryOp::BNOT; }
    | LNEG { $$ = UnaryOp::LNEG; }
    | SUB { $$ = UnaryOp::MINUS; }
    ;

nominal_expr
    : LABEL 
        { 
            auto temp = std::make_unique<NominalNode>();
            temp->label = std::move($1); 
            $$ = std::move(temp);
            $$->location = floc_to_loc(@1);
        };

list_expr
    : empty_list { $$ = std::move($1); }
    | list_con { $$ = std::move($1); }
    | string_expr { $$ = std::move($1); }
    ;

empty_list
    : SQ_LBRA SQ_RBRA 
        { 
            $$ = std::make_unique<ListNode>(); 
            $$->elems = std::vector<expr_ptr>{}; 
            $$->location = floc_to_loc(@1);
        }
    ;

list_con
    : SQ_LBRA expr_list SQ_RBRA
        { 
            $$ = std::make_unique<ListNode>(); 
            $$->elems = std::move($2); 
            $$->location = floc_to_loc(@1);
        }
    ;

expr_list
    : value_expr 
        { 
            $$ = std::vector<expr_ptr>{};
            $$.push_back(std::move($1)); 
        }
    | expr_list COMMA value_expr
        {
            $1.push_back(std::move($3));
            $$ = std::move($1);
        }
    ;

struct_expr
    : LABEL C_LBRA expr_list C_RBRA
        {
            auto temp = std::make_unique<StructNode>();
            temp->name = std::move($1);
            temp->fields = std::move($3);
            $$ = std::move(temp);

            $$->location = floc_to_loc(@1);
        }
    | NIL
        {
            $$ = std::make_unique<NilLit>();
            $$->location = floc_to_loc(@1);
        }

value_expr
    : bool_expr { $$ = std::move($1); }

bool_expr
    : comp_expr { $$ = std::move($1); }
    | bool_expr bool_op comp_expr
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = $2;
            temp->l_exp = std::move($1);
            temp->r_exp = std::move($3);
            $$ = std::move(temp);

            $$->location = floc_to_loc(@2);
        }
    ;

comp_expr
    : bitwise_expr { $$ = std::move($1); }
    | bitwise_expr comp_op bitwise_expr
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = $2;
            temp->l_exp = std::move($1);
            temp->r_exp = std::move($3);
            $$ = std::move(temp);

            $$->location = floc_to_loc(@2);
        }
    ;

bitwise_expr
    : shift_expr { $$ = std::move($1); }
    | bitwise_expr bitwise_op shift_expr
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = $2;
            temp->l_exp = std::move($1);
            temp->r_exp = std::move($3);
            $$ = std::move(temp);

            $$->location = floc_to_loc(@2);
        }
    ;

shift_expr
    : additive_expr { $$ = std::move($1); }
    | shift_expr shift_op additive_expr
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = $2;
            temp->l_exp = std::move($1);
            temp->r_exp = std::move($3);
            $$ = std::move(temp);

            $$->location = floc_to_loc(@2);
        }
    ;

additive_expr
    : mult_expr { $$ = std::move($1); }
    | additive_expr additive_op mult_expr
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = $2;
            temp->l_exp = std::move($1);
            temp->r_exp = std::move($3);
            $$ = std::move(temp);

            $$->location = floc_to_loc(@2);
        }
    ;

mult_expr
    : pow_expr { $$ = std::move($1); }
    | mult_expr mult_op pow_expr
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = $2;
            temp->l_exp = std::move($1);
            temp->r_exp = std::move($3);
            $$ = std::move(temp);

            $$->location = floc_to_loc(@2);
        }
    ;

pow_expr
    : unary_expr { $$ = std::move($1); }
    | unary_expr POW pow_expr
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = BinaryOp::POW;
            temp->l_exp = std::move($1);
            temp->r_exp = std::move($3);
            $$ = std::move(temp);

            $$->location = floc_to_loc(@2);
        }
    ;

unary_expr
    : postfix_expr { $$ = std::move($1); }
    | unary_op postfix_expr
        {
            auto temp = std::make_unique<UnaryNode>();
            temp->op = $1;
            temp->exp = std::move($2);
            $$ = std::move(temp);

            $$->location = floc_to_loc(@1);
        }
    ;

postfix_expr
    : literal_expr { $$ = std::move($1); }
    | postfix_expr SQ_LBRA value_expr SQ_RBRA
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = BinaryOp::INDEX;
            temp->l_exp = std::move($1);
            temp->r_exp = std::move($3);
            $$ = std::move(temp);

            $$->location = floc_to_loc(@2);
        }
    | postfix_expr DOT LABEL
        {
            auto temp = std::make_unique<AccessNode>();
            temp->field = std::move($3);
            temp->struct_expr = std::move($1);
            $$ = std::move(temp);

            $$->location = floc_to_loc(@2);
        }
    | postfix_expr LBRA RBRA
        {
            auto temp = std::make_unique<CallNode>();
            temp->f_exp = std::move($1);
            temp->params = std::vector<expr_ptr>{};
            $$ = std::move(temp);

            $$->location = floc_to_loc(@1);
        }
    | postfix_expr LBRA expr_list RBRA
        {
            auto temp = std::make_unique<CallNode>(); 
            temp->f_exp = std::move($1);
            temp->params = std::move($3);
            $$ = std::move(temp);

            $$->location = floc_to_loc(@1);
        }
    ;

literal_expr
    : int_lit { $$ = std::move($1); }
    | float_lit { $$ = std::move($1); }
    | char_lit { $$ = std::move($1); }
    | bool_lit { $$ = std::move($1); }
    | list_expr { $$ = std::move($1); }
    | nominal_expr { $$ = std::move($1); }
    | struct_expr { $$ = std::move($1); }
    | LBRA value_expr RBRA { $$ = std::move($2); }
    ;