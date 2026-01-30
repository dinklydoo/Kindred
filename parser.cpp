// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 6 "src/parser.y"

    #include <iostream>
    #include "parser.hpp"

    TypeSystem& type_s = TypeSystem::instance();

    literal_ptr str_to_chlist(std::string s){
        std::vector<literal_ptr> chars;
        for (char c : s){
            auto temp = std::make_unique<CharLit>();
            temp->value = c;
            chars.push_back(std::move(temp));
        }
        auto list = std::make_unique<ListLit>();
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

#line 70 "parser.cpp"


#include "parser.hpp"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 39 "src/parser.y"
namespace yy {
#line 168 "parser.cpp"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_bool_op: // bool_op
      case symbol_kind::S_comp_op: // comp_op
      case symbol_kind::S_bitwise_op: // bitwise_op
      case symbol_kind::S_shift_op: // shift_op
      case symbol_kind::S_additive_op: // additive_op
      case symbol_kind::S_mult_op: // mult_op
        value.YY_MOVE_OR_COPY< BinaryOp > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field: // field
        value.YY_MOVE_OR_COPY< Field > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.YY_MOVE_OR_COPY< Param > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.YY_MOVE_OR_COPY< UnaryOp > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_pattern_branch: // pattern_branch
        value.YY_MOVE_OR_COPY< c_branch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.YY_MOVE_OR_COPY< case_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.YY_MOVE_OR_COPY< char > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
      case symbol_kind::S_helper_expr: // helper_expr
      case symbol_kind::S_assign_expr: // assign_expr
        value.YY_MOVE_OR_COPY< decl_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_def: // enum_def
        value.YY_MOVE_OR_COPY< enum_decl_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_branch_expr: // branch_expr
      case symbol_kind::S_return_expr: // return_expr
      case symbol_kind::S_nominal_expr: // nominal_expr
      case symbol_kind::S_list_expr: // list_expr
      case symbol_kind::S_call_expr: // call_expr
      case symbol_kind::S_struct_expr: // struct_expr
      case symbol_kind::S_value_expr: // value_expr
      case symbol_kind::S_bool_expr: // bool_expr
      case symbol_kind::S_comp_expr: // comp_expr
      case symbol_kind::S_bitwise_expr: // bitwise_expr
      case symbol_kind::S_shift_expr: // shift_expr
      case symbol_kind::S_additive_expr: // additive_expr
      case symbol_kind::S_mult_expr: // mult_expr
      case symbol_kind::S_pow_expr: // pow_expr
      case symbol_kind::S_unary_expr: // unary_expr
      case symbol_kind::S_postfix_expr: // postfix_expr
      case symbol_kind::S_literal_expr: // literal_expr
        value.YY_MOVE_OR_COPY< expr_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_def: // function_def
        value.YY_MOVE_OR_COPY< func_decl_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_guard: // guard
        value.YY_MOVE_OR_COPY< g_branch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_guard_expr: // guard_expr
        value.YY_MOVE_OR_COPY< guard_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_empty_list: // empty_list
      case symbol_kind::S_list_con: // list_con
        value.YY_MOVE_OR_COPY< list_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_literal: // literal
      case symbol_kind::S_pattern: // pattern
      case symbol_kind::S_enum_lit: // enum_lit
      case symbol_kind::S_list_pattern: // list_pattern
      case symbol_kind::S_string_lit: // string_lit
      case symbol_kind::S_list_lit: // list_lit
      case symbol_kind::S_int_lit: // int_lit
      case symbol_kind::S_float_lit: // float_lit
      case symbol_kind::S_bool_lit: // bool_lit
      case symbol_kind::S_char_lit: // char_lit
        value.YY_MOVE_OR_COPY< literal_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_module: // module
        value.YY_MOVE_OR_COPY< module_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_print_expr: // print_expr
        value.YY_MOVE_OR_COPY< print_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< prog_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_read_expr: // read_expr
        value.YY_MOVE_OR_COPY< read_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_LABEL: // LABEL
      case symbol_kind::S_evar: // evar
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fields: // fields
        value.YY_MOVE_OR_COPY< std::vector<Field> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_params: // opt_params
      case symbol_kind::S_params: // params
        value.YY_MOVE_OR_COPY< std::vector<Param> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_patterns: // patterns
        value.YY_MOVE_OR_COPY< std::vector<c_branch_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definitions: // definitions
      case symbol_kind::S_helpers: // helpers
        value.YY_MOVE_OR_COPY< std::vector<decl_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.YY_MOVE_OR_COPY< std::vector<expr_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_guards: // guards
        value.YY_MOVE_OR_COPY< std::vector<g_branch_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_list_pattern_lit: // list_pattern_lit
        value.YY_MOVE_OR_COPY< std::vector<literal_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_evars: // evars
      case symbol_kind::S_size_patterns: // size_patterns
        value.YY_MOVE_OR_COPY< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_types: // opt_types
      case symbol_kind::S_types: // types
        value.YY_MOVE_OR_COPY< std::vector<type_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_def: // struct_def
        value.YY_MOVE_OR_COPY< struct_decl_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_non_function_type: // non_function_type
      case symbol_kind::S_type: // type
      case symbol_kind::S_literal_type: // literal_type
      case symbol_kind::S_int_lit_type: // int_lit_type
      case symbol_kind::S_float_lit_type: // float_lit_type
      case symbol_kind::S_list_type: // list_type
      case symbol_kind::S_func_type: // func_type
      case symbol_kind::S_nominal_type: // nominal_type
        value.YY_MOVE_OR_COPY< type_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.YY_MOVE_OR_COPY< uint64_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_bool_op: // bool_op
      case symbol_kind::S_comp_op: // comp_op
      case symbol_kind::S_bitwise_op: // bitwise_op
      case symbol_kind::S_shift_op: // shift_op
      case symbol_kind::S_additive_op: // additive_op
      case symbol_kind::S_mult_op: // mult_op
        value.move< BinaryOp > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field: // field
        value.move< Field > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.move< Param > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.move< UnaryOp > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_pattern_branch: // pattern_branch
        value.move< c_branch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.move< case_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.move< char > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
      case symbol_kind::S_helper_expr: // helper_expr
      case symbol_kind::S_assign_expr: // assign_expr
        value.move< decl_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_def: // enum_def
        value.move< enum_decl_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_branch_expr: // branch_expr
      case symbol_kind::S_return_expr: // return_expr
      case symbol_kind::S_nominal_expr: // nominal_expr
      case symbol_kind::S_list_expr: // list_expr
      case symbol_kind::S_call_expr: // call_expr
      case symbol_kind::S_struct_expr: // struct_expr
      case symbol_kind::S_value_expr: // value_expr
      case symbol_kind::S_bool_expr: // bool_expr
      case symbol_kind::S_comp_expr: // comp_expr
      case symbol_kind::S_bitwise_expr: // bitwise_expr
      case symbol_kind::S_shift_expr: // shift_expr
      case symbol_kind::S_additive_expr: // additive_expr
      case symbol_kind::S_mult_expr: // mult_expr
      case symbol_kind::S_pow_expr: // pow_expr
      case symbol_kind::S_unary_expr: // unary_expr
      case symbol_kind::S_postfix_expr: // postfix_expr
      case symbol_kind::S_literal_expr: // literal_expr
        value.move< expr_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_def: // function_def
        value.move< func_decl_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_guard: // guard
        value.move< g_branch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_guard_expr: // guard_expr
        value.move< guard_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_empty_list: // empty_list
      case symbol_kind::S_list_con: // list_con
        value.move< list_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_literal: // literal
      case symbol_kind::S_pattern: // pattern
      case symbol_kind::S_enum_lit: // enum_lit
      case symbol_kind::S_list_pattern: // list_pattern
      case symbol_kind::S_string_lit: // string_lit
      case symbol_kind::S_list_lit: // list_lit
      case symbol_kind::S_int_lit: // int_lit
      case symbol_kind::S_float_lit: // float_lit
      case symbol_kind::S_bool_lit: // bool_lit
      case symbol_kind::S_char_lit: // char_lit
        value.move< literal_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_module: // module
        value.move< module_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_print_expr: // print_expr
        value.move< print_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< prog_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_read_expr: // read_expr
        value.move< read_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_LABEL: // LABEL
      case symbol_kind::S_evar: // evar
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fields: // fields
        value.move< std::vector<Field> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_params: // opt_params
      case symbol_kind::S_params: // params
        value.move< std::vector<Param> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_patterns: // patterns
        value.move< std::vector<c_branch_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definitions: // definitions
      case symbol_kind::S_helpers: // helpers
        value.move< std::vector<decl_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< std::vector<expr_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_guards: // guards
        value.move< std::vector<g_branch_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_list_pattern_lit: // list_pattern_lit
        value.move< std::vector<literal_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_evars: // evars
      case symbol_kind::S_size_patterns: // size_patterns
        value.move< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_types: // opt_types
      case symbol_kind::S_types: // types
        value.move< std::vector<type_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_def: // struct_def
        value.move< struct_decl_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_non_function_type: // non_function_type
      case symbol_kind::S_type: // type
      case symbol_kind::S_literal_type: // literal_type
      case symbol_kind::S_int_lit_type: // int_lit_type
      case symbol_kind::S_float_lit_type: // float_lit_type
      case symbol_kind::S_list_type: // list_type
      case symbol_kind::S_func_type: // func_type
      case symbol_kind::S_nominal_type: // nominal_type
        value.move< type_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< uint64_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_bool_op: // bool_op
      case symbol_kind::S_comp_op: // comp_op
      case symbol_kind::S_bitwise_op: // bitwise_op
      case symbol_kind::S_shift_op: // shift_op
      case symbol_kind::S_additive_op: // additive_op
      case symbol_kind::S_mult_op: // mult_op
        value.copy< BinaryOp > (that.value);
        break;

      case symbol_kind::S_field: // field
        value.copy< Field > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.copy< Param > (that.value);
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.copy< UnaryOp > (that.value);
        break;

      case symbol_kind::S_pattern_branch: // pattern_branch
        value.copy< c_branch_ptr > (that.value);
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.copy< case_ptr > (that.value);
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.copy< char > (that.value);
        break;

      case symbol_kind::S_definition: // definition
      case symbol_kind::S_helper_expr: // helper_expr
      case symbol_kind::S_assign_expr: // assign_expr
        value.copy< decl_ptr > (that.value);
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_enum_def: // enum_def
        value.copy< enum_decl_ptr > (that.value);
        break;

      case symbol_kind::S_branch_expr: // branch_expr
      case symbol_kind::S_return_expr: // return_expr
      case symbol_kind::S_nominal_expr: // nominal_expr
      case symbol_kind::S_list_expr: // list_expr
      case symbol_kind::S_call_expr: // call_expr
      case symbol_kind::S_struct_expr: // struct_expr
      case symbol_kind::S_value_expr: // value_expr
      case symbol_kind::S_bool_expr: // bool_expr
      case symbol_kind::S_comp_expr: // comp_expr
      case symbol_kind::S_bitwise_expr: // bitwise_expr
      case symbol_kind::S_shift_expr: // shift_expr
      case symbol_kind::S_additive_expr: // additive_expr
      case symbol_kind::S_mult_expr: // mult_expr
      case symbol_kind::S_pow_expr: // pow_expr
      case symbol_kind::S_unary_expr: // unary_expr
      case symbol_kind::S_postfix_expr: // postfix_expr
      case symbol_kind::S_literal_expr: // literal_expr
        value.copy< expr_ptr > (that.value);
        break;

      case symbol_kind::S_function_def: // function_def
        value.copy< func_decl_ptr > (that.value);
        break;

      case symbol_kind::S_guard: // guard
        value.copy< g_branch_ptr > (that.value);
        break;

      case symbol_kind::S_guard_expr: // guard_expr
        value.copy< guard_ptr > (that.value);
        break;

      case symbol_kind::S_empty_list: // empty_list
      case symbol_kind::S_list_con: // list_con
        value.copy< list_ptr > (that.value);
        break;

      case symbol_kind::S_literal: // literal
      case symbol_kind::S_pattern: // pattern
      case symbol_kind::S_enum_lit: // enum_lit
      case symbol_kind::S_list_pattern: // list_pattern
      case symbol_kind::S_string_lit: // string_lit
      case symbol_kind::S_list_lit: // list_lit
      case symbol_kind::S_int_lit: // int_lit
      case symbol_kind::S_float_lit: // float_lit
      case symbol_kind::S_bool_lit: // bool_lit
      case symbol_kind::S_char_lit: // char_lit
        value.copy< literal_ptr > (that.value);
        break;

      case symbol_kind::S_module: // module
        value.copy< module_ptr > (that.value);
        break;

      case symbol_kind::S_print_expr: // print_expr
        value.copy< print_ptr > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< prog_ptr > (that.value);
        break;

      case symbol_kind::S_read_expr: // read_expr
        value.copy< read_ptr > (that.value);
        break;

      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_LABEL: // LABEL
      case symbol_kind::S_evar: // evar
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_fields: // fields
        value.copy< std::vector<Field> > (that.value);
        break;

      case symbol_kind::S_opt_params: // opt_params
      case symbol_kind::S_params: // params
        value.copy< std::vector<Param> > (that.value);
        break;

      case symbol_kind::S_patterns: // patterns
        value.copy< std::vector<c_branch_ptr> > (that.value);
        break;

      case symbol_kind::S_definitions: // definitions
      case symbol_kind::S_helpers: // helpers
        value.copy< std::vector<decl_ptr> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.copy< std::vector<expr_ptr> > (that.value);
        break;

      case symbol_kind::S_guards: // guards
        value.copy< std::vector<g_branch_ptr> > (that.value);
        break;

      case symbol_kind::S_list_pattern_lit: // list_pattern_lit
        value.copy< std::vector<literal_ptr> > (that.value);
        break;

      case symbol_kind::S_evars: // evars
      case symbol_kind::S_size_patterns: // size_patterns
        value.copy< std::vector<std::string> > (that.value);
        break;

      case symbol_kind::S_opt_types: // opt_types
      case symbol_kind::S_types: // types
        value.copy< std::vector<type_ptr> > (that.value);
        break;

      case symbol_kind::S_struct_def: // struct_def
        value.copy< struct_decl_ptr > (that.value);
        break;

      case symbol_kind::S_non_function_type: // non_function_type
      case symbol_kind::S_type: // type
      case symbol_kind::S_literal_type: // literal_type
      case symbol_kind::S_int_lit_type: // int_lit_type
      case symbol_kind::S_float_lit_type: // float_lit_type
      case symbol_kind::S_list_type: // list_type
      case symbol_kind::S_func_type: // func_type
      case symbol_kind::S_nominal_type: // nominal_type
        value.copy< type_ptr > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.copy< uint64_t > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_bool_op: // bool_op
      case symbol_kind::S_comp_op: // comp_op
      case symbol_kind::S_bitwise_op: // bitwise_op
      case symbol_kind::S_shift_op: // shift_op
      case symbol_kind::S_additive_op: // additive_op
      case symbol_kind::S_mult_op: // mult_op
        value.move< BinaryOp > (that.value);
        break;

      case symbol_kind::S_field: // field
        value.move< Field > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.move< Param > (that.value);
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.move< UnaryOp > (that.value);
        break;

      case symbol_kind::S_pattern_branch: // pattern_branch
        value.move< c_branch_ptr > (that.value);
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.move< case_ptr > (that.value);
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.move< char > (that.value);
        break;

      case symbol_kind::S_definition: // definition
      case symbol_kind::S_helper_expr: // helper_expr
      case symbol_kind::S_assign_expr: // assign_expr
        value.move< decl_ptr > (that.value);
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.move< double > (that.value);
        break;

      case symbol_kind::S_enum_def: // enum_def
        value.move< enum_decl_ptr > (that.value);
        break;

      case symbol_kind::S_branch_expr: // branch_expr
      case symbol_kind::S_return_expr: // return_expr
      case symbol_kind::S_nominal_expr: // nominal_expr
      case symbol_kind::S_list_expr: // list_expr
      case symbol_kind::S_call_expr: // call_expr
      case symbol_kind::S_struct_expr: // struct_expr
      case symbol_kind::S_value_expr: // value_expr
      case symbol_kind::S_bool_expr: // bool_expr
      case symbol_kind::S_comp_expr: // comp_expr
      case symbol_kind::S_bitwise_expr: // bitwise_expr
      case symbol_kind::S_shift_expr: // shift_expr
      case symbol_kind::S_additive_expr: // additive_expr
      case symbol_kind::S_mult_expr: // mult_expr
      case symbol_kind::S_pow_expr: // pow_expr
      case symbol_kind::S_unary_expr: // unary_expr
      case symbol_kind::S_postfix_expr: // postfix_expr
      case symbol_kind::S_literal_expr: // literal_expr
        value.move< expr_ptr > (that.value);
        break;

      case symbol_kind::S_function_def: // function_def
        value.move< func_decl_ptr > (that.value);
        break;

      case symbol_kind::S_guard: // guard
        value.move< g_branch_ptr > (that.value);
        break;

      case symbol_kind::S_guard_expr: // guard_expr
        value.move< guard_ptr > (that.value);
        break;

      case symbol_kind::S_empty_list: // empty_list
      case symbol_kind::S_list_con: // list_con
        value.move< list_ptr > (that.value);
        break;

      case symbol_kind::S_literal: // literal
      case symbol_kind::S_pattern: // pattern
      case symbol_kind::S_enum_lit: // enum_lit
      case symbol_kind::S_list_pattern: // list_pattern
      case symbol_kind::S_string_lit: // string_lit
      case symbol_kind::S_list_lit: // list_lit
      case symbol_kind::S_int_lit: // int_lit
      case symbol_kind::S_float_lit: // float_lit
      case symbol_kind::S_bool_lit: // bool_lit
      case symbol_kind::S_char_lit: // char_lit
        value.move< literal_ptr > (that.value);
        break;

      case symbol_kind::S_module: // module
        value.move< module_ptr > (that.value);
        break;

      case symbol_kind::S_print_expr: // print_expr
        value.move< print_ptr > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< prog_ptr > (that.value);
        break;

      case symbol_kind::S_read_expr: // read_expr
        value.move< read_ptr > (that.value);
        break;

      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_LABEL: // LABEL
      case symbol_kind::S_evar: // evar
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_fields: // fields
        value.move< std::vector<Field> > (that.value);
        break;

      case symbol_kind::S_opt_params: // opt_params
      case symbol_kind::S_params: // params
        value.move< std::vector<Param> > (that.value);
        break;

      case symbol_kind::S_patterns: // patterns
        value.move< std::vector<c_branch_ptr> > (that.value);
        break;

      case symbol_kind::S_definitions: // definitions
      case symbol_kind::S_helpers: // helpers
        value.move< std::vector<decl_ptr> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< std::vector<expr_ptr> > (that.value);
        break;

      case symbol_kind::S_guards: // guards
        value.move< std::vector<g_branch_ptr> > (that.value);
        break;

      case symbol_kind::S_list_pattern_lit: // list_pattern_lit
        value.move< std::vector<literal_ptr> > (that.value);
        break;

      case symbol_kind::S_evars: // evars
      case symbol_kind::S_size_patterns: // size_patterns
        value.move< std::vector<std::string> > (that.value);
        break;

      case symbol_kind::S_opt_types: // opt_types
      case symbol_kind::S_types: // types
        value.move< std::vector<type_ptr> > (that.value);
        break;

      case symbol_kind::S_struct_def: // struct_def
        value.move< struct_decl_ptr > (that.value);
        break;

      case symbol_kind::S_non_function_type: // non_function_type
      case symbol_kind::S_type: // type
      case symbol_kind::S_literal_type: // literal_type
      case symbol_kind::S_int_lit_type: // int_lit_type
      case symbol_kind::S_float_lit_type: // float_lit_type
      case symbol_kind::S_list_type: // list_type
      case symbol_kind::S_func_type: // func_type
      case symbol_kind::S_nominal_type: // nominal_type
        value.move< type_ptr > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.move< uint64_t > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_bool_op: // bool_op
      case symbol_kind::S_comp_op: // comp_op
      case symbol_kind::S_bitwise_op: // bitwise_op
      case symbol_kind::S_shift_op: // shift_op
      case symbol_kind::S_additive_op: // additive_op
      case symbol_kind::S_mult_op: // mult_op
        yylhs.value.emplace< BinaryOp > ();
        break;

      case symbol_kind::S_field: // field
        yylhs.value.emplace< Field > ();
        break;

      case symbol_kind::S_param: // param
        yylhs.value.emplace< Param > ();
        break;

      case symbol_kind::S_unary_op: // unary_op
        yylhs.value.emplace< UnaryOp > ();
        break;

      case symbol_kind::S_pattern_branch: // pattern_branch
        yylhs.value.emplace< c_branch_ptr > ();
        break;

      case symbol_kind::S_case_expr: // case_expr
        yylhs.value.emplace< case_ptr > ();
        break;

      case symbol_kind::S_CHAR: // CHAR
        yylhs.value.emplace< char > ();
        break;

      case symbol_kind::S_definition: // definition
      case symbol_kind::S_helper_expr: // helper_expr
      case symbol_kind::S_assign_expr: // assign_expr
        yylhs.value.emplace< decl_ptr > ();
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_enum_def: // enum_def
        yylhs.value.emplace< enum_decl_ptr > ();
        break;

      case symbol_kind::S_branch_expr: // branch_expr
      case symbol_kind::S_return_expr: // return_expr
      case symbol_kind::S_nominal_expr: // nominal_expr
      case symbol_kind::S_list_expr: // list_expr
      case symbol_kind::S_call_expr: // call_expr
      case symbol_kind::S_struct_expr: // struct_expr
      case symbol_kind::S_value_expr: // value_expr
      case symbol_kind::S_bool_expr: // bool_expr
      case symbol_kind::S_comp_expr: // comp_expr
      case symbol_kind::S_bitwise_expr: // bitwise_expr
      case symbol_kind::S_shift_expr: // shift_expr
      case symbol_kind::S_additive_expr: // additive_expr
      case symbol_kind::S_mult_expr: // mult_expr
      case symbol_kind::S_pow_expr: // pow_expr
      case symbol_kind::S_unary_expr: // unary_expr
      case symbol_kind::S_postfix_expr: // postfix_expr
      case symbol_kind::S_literal_expr: // literal_expr
        yylhs.value.emplace< expr_ptr > ();
        break;

      case symbol_kind::S_function_def: // function_def
        yylhs.value.emplace< func_decl_ptr > ();
        break;

      case symbol_kind::S_guard: // guard
        yylhs.value.emplace< g_branch_ptr > ();
        break;

      case symbol_kind::S_guard_expr: // guard_expr
        yylhs.value.emplace< guard_ptr > ();
        break;

      case symbol_kind::S_empty_list: // empty_list
      case symbol_kind::S_list_con: // list_con
        yylhs.value.emplace< list_ptr > ();
        break;

      case symbol_kind::S_literal: // literal
      case symbol_kind::S_pattern: // pattern
      case symbol_kind::S_enum_lit: // enum_lit
      case symbol_kind::S_list_pattern: // list_pattern
      case symbol_kind::S_string_lit: // string_lit
      case symbol_kind::S_list_lit: // list_lit
      case symbol_kind::S_int_lit: // int_lit
      case symbol_kind::S_float_lit: // float_lit
      case symbol_kind::S_bool_lit: // bool_lit
      case symbol_kind::S_char_lit: // char_lit
        yylhs.value.emplace< literal_ptr > ();
        break;

      case symbol_kind::S_module: // module
        yylhs.value.emplace< module_ptr > ();
        break;

      case symbol_kind::S_print_expr: // print_expr
        yylhs.value.emplace< print_ptr > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< prog_ptr > ();
        break;

      case symbol_kind::S_read_expr: // read_expr
        yylhs.value.emplace< read_ptr > ();
        break;

      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_LABEL: // LABEL
      case symbol_kind::S_evar: // evar
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_fields: // fields
        yylhs.value.emplace< std::vector<Field> > ();
        break;

      case symbol_kind::S_opt_params: // opt_params
      case symbol_kind::S_params: // params
        yylhs.value.emplace< std::vector<Param> > ();
        break;

      case symbol_kind::S_patterns: // patterns
        yylhs.value.emplace< std::vector<c_branch_ptr> > ();
        break;

      case symbol_kind::S_definitions: // definitions
      case symbol_kind::S_helpers: // helpers
        yylhs.value.emplace< std::vector<decl_ptr> > ();
        break;

      case symbol_kind::S_expr_list: // expr_list
        yylhs.value.emplace< std::vector<expr_ptr> > ();
        break;

      case symbol_kind::S_guards: // guards
        yylhs.value.emplace< std::vector<g_branch_ptr> > ();
        break;

      case symbol_kind::S_list_pattern_lit: // list_pattern_lit
        yylhs.value.emplace< std::vector<literal_ptr> > ();
        break;

      case symbol_kind::S_evars: // evars
      case symbol_kind::S_size_patterns: // size_patterns
        yylhs.value.emplace< std::vector<std::string> > ();
        break;

      case symbol_kind::S_opt_types: // opt_types
      case symbol_kind::S_types: // types
        yylhs.value.emplace< std::vector<type_ptr> > ();
        break;

      case symbol_kind::S_struct_def: // struct_def
        yylhs.value.emplace< struct_decl_ptr > ();
        break;

      case symbol_kind::S_non_function_type: // non_function_type
      case symbol_kind::S_type: // type
      case symbol_kind::S_literal_type: // literal_type
      case symbol_kind::S_int_lit_type: // int_lit_type
      case symbol_kind::S_float_lit_type: // float_lit_type
      case symbol_kind::S_list_type: // list_type
      case symbol_kind::S_func_type: // func_type
      case symbol_kind::S_nominal_type: // nominal_type
        yylhs.value.emplace< type_ptr > ();
        break;

      case symbol_kind::S_INT: // INT
        yylhs.value.emplace< uint64_t > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // module: definitions KEOF
#line 184 "src/parser.y"
        { 
            yylhs.value.as < module_ptr > () = std::make_unique<ModuleNode>();
            yylhs.value.as < module_ptr > ()->decl = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
            module_node = std::move(yylhs.value.as < module_ptr > ());
        }
#line 1455 "parser.cpp"
    break;

  case 3: // definitions: %empty
#line 193 "src/parser.y"
        { yylhs.value.as < std::vector<decl_ptr> > () = std::vector<decl_ptr>{}; }
#line 1461 "parser.cpp"
    break;

  case 4: // definitions: definitions definition
#line 195 "src/parser.y"
        { 
            yystack_[1].value.as < std::vector<decl_ptr> > ().push_back(std::move(yystack_[0].value.as < decl_ptr > ()));
            yylhs.value.as < std::vector<decl_ptr> > () = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
        }
#line 1470 "parser.cpp"
    break;

  case 5: // definition: function_def
#line 202 "src/parser.y"
                  { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < func_decl_ptr > ()); }
#line 1476 "parser.cpp"
    break;

  case 6: // definition: struct_def
#line 203 "src/parser.y"
                { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < struct_decl_ptr > ()); }
#line 1482 "parser.cpp"
    break;

  case 7: // definition: enum_def
#line 204 "src/parser.y"
              { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < enum_decl_ptr > ()); }
#line 1488 "parser.cpp"
    break;

  case 8: // opt_types: %empty
#line 207 "src/parser.y"
             { yylhs.value.as < std::vector<type_ptr> > () = std::vector<type_ptr>{}; }
#line 1494 "parser.cpp"
    break;

  case 9: // opt_types: types
#line 208 "src/parser.y"
            { yylhs.value.as < std::vector<type_ptr> > () = std::move(yystack_[0].value.as < std::vector<type_ptr> > ()); }
#line 1500 "parser.cpp"
    break;

  case 10: // types: type
#line 211 "src/parser.y"
           { yylhs.value.as < std::vector<type_ptr> > () = std::vector<type_ptr>{yystack_[0].value.as < type_ptr > ()}; }
#line 1506 "parser.cpp"
    break;

  case 11: // types: types COMMA type
#line 212 "src/parser.y"
                       {
        yystack_[2].value.as < std::vector<type_ptr> > ().push_back(std::move(yystack_[0].value.as < type_ptr > ()));
        yylhs.value.as < std::vector<type_ptr> > () = std::move(yystack_[2].value.as < std::vector<type_ptr> > ());
    }
#line 1515 "parser.cpp"
    break;

  case 12: // non_function_type: literal_type
#line 218 "src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1521 "parser.cpp"
    break;

  case 13: // non_function_type: list_type
#line 219 "src/parser.y"
                { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1527 "parser.cpp"
    break;

  case 14: // non_function_type: nominal_type
#line 220 "src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1533 "parser.cpp"
    break;

  case 15: // type: non_function_type
#line 224 "src/parser.y"
                        { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1539 "parser.cpp"
    break;

  case 16: // type: func_type
#line 225 "src/parser.y"
                { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1545 "parser.cpp"
    break;

  case 17: // literal_type: T_CHAR
#line 229 "src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.char_type(); }
#line 1551 "parser.cpp"
    break;

  case 18: // literal_type: T_BOOL
#line 230 "src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.bool_type(); }
#line 1557 "parser.cpp"
    break;

  case 19: // literal_type: int_lit_type
#line 231 "src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1563 "parser.cpp"
    break;

  case 20: // literal_type: float_lit_type
#line 232 "src/parser.y"
                     { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1569 "parser.cpp"
    break;

  case 21: // int_lit_type: T_INT
#line 236 "src/parser.y"
            { yylhs.value.as < type_ptr > () = type_s.int_type(); }
#line 1575 "parser.cpp"
    break;

  case 22: // int_lit_type: T_LONG
#line 237 "src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.long_type(); }
#line 1581 "parser.cpp"
    break;

  case 23: // float_lit_type: T_FLOAT
#line 240 "src/parser.y"
              { yylhs.value.as < type_ptr > () = type_s.float_type(); }
#line 1587 "parser.cpp"
    break;

  case 24: // float_lit_type: T_DOUBLE
#line 241 "src/parser.y"
               { yylhs.value.as < type_ptr > () = type_s.double_type(); }
#line 1593 "parser.cpp"
    break;

  case 25: // list_type: SQ_LBRA type SQ_RBRA
#line 244 "src/parser.y"
                           { yylhs.value.as < type_ptr > () = type_s.list_type(yystack_[1].value.as < type_ptr > ()); }
#line 1599 "parser.cpp"
    break;

  case 26: // func_type: LBRA opt_types RBRA PROD type
#line 247 "src/parser.y"
                                    { yylhs.value.as < type_ptr > () = type_s.func_type(yystack_[3].value.as < std::vector<type_ptr> > (), yystack_[0].value.as < type_ptr > ()); }
#line 1605 "parser.cpp"
    break;

  case 27: // nominal_type: LABEL
#line 250 "src/parser.y"
            { yylhs.value.as < type_ptr > () = type_s.nominal_type(yystack_[0].value.as < std::string > ()); }
#line 1611 "parser.cpp"
    break;

  case 28: // opt_params: %empty
#line 253 "src/parser.y"
             { yylhs.value.as < std::vector<Param> > () = std::vector<Param>{}; }
#line 1617 "parser.cpp"
    break;

  case 29: // opt_params: params
#line 254 "src/parser.y"
             { yylhs.value.as < std::vector<Param> > () = std::move(yystack_[0].value.as < std::vector<Param> > ()); }
#line 1623 "parser.cpp"
    break;

  case 30: // params: param
#line 257 "src/parser.y"
            { yylhs.value.as < std::vector<Param> > () = std::vector<Param>{yystack_[0].value.as < Param > ()}; }
#line 1629 "parser.cpp"
    break;

  case 31: // params: params COMMA param
#line 259 "src/parser.y"
        {
            yystack_[2].value.as < std::vector<Param> > ().push_back(std::move(yystack_[0].value.as < Param > ()));
            yylhs.value.as < std::vector<Param> > () = std::move(yystack_[2].value.as < std::vector<Param> > ());
        }
#line 1638 "parser.cpp"
    break;

  case 32: // param: LABEL TSEP type
#line 266 "src/parser.y"
        { 
            yylhs.value.as < Param > () = Param(); 
            yylhs.value.as < Param > ().name = std::move(yystack_[2].value.as < std::string > ());
            yylhs.value.as < Param > ().type = std::move(yystack_[0].value.as < type_ptr > ());
            yylhs.value.as < Param > ().location = floc_to_loc(yystack_[2].location);
        }
#line 1649 "parser.cpp"
    break;

  case 33: // function_def: FUNC LABEL LBRA opt_params RBRA TSEP type program
#line 276 "src/parser.y"
        {   
            yylhs.value.as < func_decl_ptr > () = std::make_unique<FuncDecl>();
            yylhs.value.as < func_decl_ptr > ()->name = std::move(yystack_[6].value.as < std::string > ());
            yylhs.value.as < func_decl_ptr > ()->params = std::move(yystack_[4].value.as < std::vector<Param> > ());
            yylhs.value.as < func_decl_ptr > ()->ret = std::move(yystack_[1].value.as < type_ptr > ());
            yylhs.value.as < func_decl_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());

            yylhs.value.as < func_decl_ptr > ()->location = floc_to_loc(yystack_[7].location);
        }
#line 1663 "parser.cpp"
    break;

  case 34: // fields: field
#line 289 "src/parser.y"
        {   yylhs.value.as < std::vector<Field> > () = std::vector<Field>{}; yylhs.value.as < std::vector<Field> > ().push_back(std::move(yystack_[0].value.as < Field > ())); }
#line 1669 "parser.cpp"
    break;

  case 35: // fields: fields COMMA field
#line 291 "src/parser.y"
        { 
            yystack_[2].value.as < std::vector<Field> > ().push_back(std::move(yystack_[0].value.as < Field > ()));
            yylhs.value.as < std::vector<Field> > () = std::move(yystack_[2].value.as < std::vector<Field> > ());
        }
#line 1678 "parser.cpp"
    break;

  case 36: // field: LABEL TSEP type
#line 299 "src/parser.y"
        {
            yylhs.value.as < Field > () = Field();
            yylhs.value.as < Field > ().name = std::move(yystack_[2].value.as < std::string > ());
            yylhs.value.as < Field > ().type = std::move(yystack_[0].value.as < type_ptr > ());

            yylhs.value.as < Field > ().location = floc_to_loc(yystack_[2].location);
        }
#line 1690 "parser.cpp"
    break;

  case 37: // struct_def: STRUCT LABEL LBRA fields RBRA
#line 309 "src/parser.y"
        {
            yylhs.value.as < struct_decl_ptr > () = std::make_unique<StructDecl>();
            yylhs.value.as < struct_decl_ptr > ()->name = std::move(yystack_[3].value.as < std::string > ());
            yylhs.value.as < struct_decl_ptr > ()->fields = std::move(yystack_[1].value.as < std::vector<Field> > ());

            yylhs.value.as < struct_decl_ptr > ()->location = floc_to_loc(yystack_[4].location);
        }
#line 1702 "parser.cpp"
    break;

  case 38: // evar: LABEL
#line 319 "src/parser.y"
            { yylhs.value.as < std::string > () = std::move(yystack_[0].value.as < std::string > ()); }
#line 1708 "parser.cpp"
    break;

  case 39: // evars: evar
#line 322 "src/parser.y"
           { yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{yystack_[0].value.as < std::string > ()}; }
#line 1714 "parser.cpp"
    break;

  case 40: // evars: evars COMMA evar
#line 324 "src/parser.y"
        {
            yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));
            yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ());
        }
#line 1723 "parser.cpp"
    break;

  case 41: // enum_def: ENUM LABEL LBRA evars RBRA
#line 332 "src/parser.y"
        { 
            yylhs.value.as < enum_decl_ptr > () = std::make_unique<EnumDecl>(); 
            yylhs.value.as < enum_decl_ptr > ()->name = std::move(yystack_[3].value.as < std::string > ());
            yylhs.value.as < enum_decl_ptr > ()->evar = std::move(yystack_[1].value.as < std::vector<std::string> > ());

            yylhs.value.as < enum_decl_ptr > ()->location = floc_to_loc(yystack_[4].location);
        }
#line 1735 "parser.cpp"
    break;

  case 42: // program: helpers branch_expr
#line 343 "src/parser.y"
        {
            yylhs.value.as < prog_ptr > () = std::make_unique<ProgramNode>();
            yylhs.value.as < prog_ptr > ()->decl = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
            yylhs.value.as < prog_ptr > ()->body = std::move(yystack_[0].value.as < expr_ptr > ());
        }
#line 1745 "parser.cpp"
    break;

  case 43: // branch_expr: return_expr
#line 351 "src/parser.y"
                  { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 1751 "parser.cpp"
    break;

  case 44: // branch_expr: guard_expr
#line 352 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < guard_ptr > ()); }
#line 1757 "parser.cpp"
    break;

  case 45: // branch_expr: case_expr
#line 353 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < case_ptr > ()); }
#line 1763 "parser.cpp"
    break;

  case 46: // guard_expr: CASE OF TSEP guards PEND
#line 358 "src/parser.y"
        {
            yylhs.value.as < guard_ptr > () = std::make_unique<GuardNode>();
            yylhs.value.as < guard_ptr > ()->branches = std::move(yystack_[1].value.as < std::vector<g_branch_ptr> > ());
        }
#line 1772 "parser.cpp"
    break;

  case 47: // guards: guard
#line 366 "src/parser.y"
        { 
            yylhs.value.as < std::vector<g_branch_ptr> > () = std::vector<g_branch_ptr>{}; 
            yylhs.value.as < std::vector<g_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < g_branch_ptr > ()));
        }
#line 1781 "parser.cpp"
    break;

  case 48: // guards: guards COMMA guard
#line 371 "src/parser.y"
        {
            yystack_[2].value.as < std::vector<g_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < g_branch_ptr > ()));
            yylhs.value.as < std::vector<g_branch_ptr> > () = std::move(yystack_[2].value.as < std::vector<g_branch_ptr> > ());
        }
#line 1790 "parser.cpp"
    break;

  case 49: // guard: BAR value_expr ARROW program
#line 379 "src/parser.y"
        {
            yylhs.value.as < g_branch_ptr > () = std::make_unique<GuardBranchNode>();
            yylhs.value.as < g_branch_ptr > ()->match = std::move(yystack_[2].value.as < expr_ptr > ());
            yylhs.value.as < g_branch_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());
        }
#line 1800 "parser.cpp"
    break;

  case 50: // guard: BAR ELSE ARROW program
#line 385 "src/parser.y"
        {
            yylhs.value.as < g_branch_ptr > () = std::make_unique<GuardBranchNode>();
            auto temp = std::make_unique<BoolLit>();
            temp->value = true;
            yylhs.value.as < g_branch_ptr > ()->match = std::move(temp);
            yylhs.value.as < g_branch_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());
        }
#line 1812 "parser.cpp"
    break;

  case 51: // case_expr: MARK value_expr OF TSEP patterns PEND
#line 396 "src/parser.y"
        {
            yylhs.value.as < case_ptr > () = std::make_unique<CaseNode>();
            yylhs.value.as < case_ptr > ()->target = std::move(yystack_[4].value.as < expr_ptr > ());
            yylhs.value.as < case_ptr > ()->patterns = std::move(yystack_[1].value.as < std::vector<c_branch_ptr> > ());
        }
#line 1822 "parser.cpp"
    break;

  case 52: // patterns: pattern_branch
#line 405 "src/parser.y"
        { 
            yylhs.value.as < std::vector<c_branch_ptr> > () = std::vector<c_branch_ptr>{}; 
            yylhs.value.as < std::vector<c_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < c_branch_ptr > ())); 
        }
#line 1831 "parser.cpp"
    break;

  case 53: // patterns: patterns COMMA pattern_branch
#line 410 "src/parser.y"
        {
            yystack_[2].value.as < std::vector<c_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < c_branch_ptr > ()));
            yylhs.value.as < std::vector<c_branch_ptr> > () = std::move(yystack_[2].value.as < std::vector<c_branch_ptr> > ());
        }
#line 1840 "parser.cpp"
    break;

  case 54: // pattern_branch: pattern ARROW program
#line 418 "src/parser.y"
        {
            yylhs.value.as < c_branch_ptr > () = std::make_unique<CaseBranchNode>();
            yylhs.value.as < c_branch_ptr > ()->pattern = std::move(yystack_[2].value.as < literal_ptr > ());
            yylhs.value.as < c_branch_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());

            yylhs.value.as < c_branch_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 1852 "parser.cpp"
    break;

  case 55: // literal: char_lit
#line 428 "src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1858 "parser.cpp"
    break;

  case 56: // literal: int_lit
#line 429 "src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1864 "parser.cpp"
    break;

  case 57: // literal: float_lit
#line 430 "src/parser.y"
                { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1870 "parser.cpp"
    break;

  case 58: // literal: bool_lit
#line 431 "src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1876 "parser.cpp"
    break;

  case 59: // literal: enum_lit
#line 432 "src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1882 "parser.cpp"
    break;

  case 60: // literal: list_pattern
#line 433 "src/parser.y"
                   { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1888 "parser.cpp"
    break;

  case 61: // pattern: literal
#line 437 "src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1894 "parser.cpp"
    break;

  case 62: // pattern: NIL
#line 438 "src/parser.y"
          { yylhs.value.as < literal_ptr > () = std::make_unique<NilLit>(); yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);}
#line 1900 "parser.cpp"
    break;

  case 63: // pattern: DEFAULT
#line 439 "src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::make_unique<DefaultLit>(); }
#line 1906 "parser.cpp"
    break;

  case 64: // enum_lit: LABEL
#line 444 "src/parser.y"
        { 
            auto temp = std::make_unique<EnumLit>();
            temp->elem = std::move(yystack_[0].value.as < std::string > ()); 
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 1918 "parser.cpp"
    break;

  case 65: // list_pattern: SQ_LBRA SQ_RBRA
#line 454 "src/parser.y"
        { 
            auto temp = std::make_unique<ListLit>();
            temp->elems = std::vector<literal_ptr>{}; 
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 1930 "parser.cpp"
    break;

  case 66: // list_pattern: list_lit
#line 461 "src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1936 "parser.cpp"
    break;

  case 67: // list_pattern: string_lit
#line 462 "src/parser.y"
                 { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1942 "parser.cpp"
    break;

  case 68: // list_pattern: size_patterns
#line 464 "src/parser.y"
        {
            auto temp = std::make_unique<ListPatternLit>(); 
            temp->patterns = std::move(yystack_[0].value.as < std::vector<std::string> > ());
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 1954 "parser.cpp"
    break;

  case 69: // string_lit: STRING
#line 474 "src/parser.y"
             {yylhs.value.as < literal_ptr > () = str_to_chlist(yystack_[0].value.as < std::string > ()); yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location); }
#line 1960 "parser.cpp"
    break;

  case 70: // list_lit: SQ_LBRA list_pattern_lit SQ_RBRA
#line 478 "src/parser.y"
        { 
            auto temp = std::make_unique<ListLit>(); 
            temp->elems = std::move(yystack_[1].value.as < std::vector<literal_ptr> > ()); 
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 1972 "parser.cpp"
    break;

  case 71: // list_pattern_lit: literal
#line 488 "src/parser.y"
        { 
            yylhs.value.as < std::vector<literal_ptr> > () = std::vector<literal_ptr>{}; 
            yylhs.value.as < std::vector<literal_ptr> > ().push_back(std::move(yystack_[0].value.as < literal_ptr > ()));
        }
#line 1981 "parser.cpp"
    break;

  case 72: // list_pattern_lit: list_pattern_lit COMMA literal
#line 493 "src/parser.y"
        { 
            yystack_[2].value.as < std::vector<literal_ptr> > ().push_back(std::move(yystack_[0].value.as < literal_ptr > ()));
            yylhs.value.as < std::vector<literal_ptr> > () = std::move(yystack_[2].value.as < std::vector<literal_ptr> > ());
        }
#line 1990 "parser.cpp"
    break;

  case 73: // size_patterns: LABEL TSEP LABEL
#line 501 "src/parser.y"
        { 
            yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{};
            yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[2].value.as < std::string > ()));
            yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ())); 
        }
#line 2000 "parser.cpp"
    break;

  case 74: // size_patterns: size_patterns TSEP LABEL
#line 506 "src/parser.y"
                               {
        yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));
        yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ());
    }
#line 2009 "parser.cpp"
    break;

  case 75: // return_expr: RETURN value_expr
#line 514 "src/parser.y"
        { 
            auto temp = std::make_unique<ReturnNode>();
            temp->rexp = std::move(yystack_[0].value.as < expr_ptr > ()); 
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2021 "parser.cpp"
    break;

  case 76: // helpers: %empty
#line 524 "src/parser.y"
             { yylhs.value.as < std::vector<decl_ptr> > () = std::vector<decl_ptr>{}; }
#line 2027 "parser.cpp"
    break;

  case 77: // helpers: helpers helper_expr
#line 526 "src/parser.y"
        {
            yystack_[1].value.as < std::vector<decl_ptr> > ().push_back(std::move(yystack_[0].value.as < decl_ptr > ()));
            yylhs.value.as < std::vector<decl_ptr> > () = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
        }
#line 2036 "parser.cpp"
    break;

  case 78: // helper_expr: assign_expr
#line 533 "src/parser.y"
                  { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < decl_ptr > ()); }
#line 2042 "parser.cpp"
    break;

  case 79: // helper_expr: print_expr
#line 534 "src/parser.y"
                 { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < print_ptr > ()); }
#line 2048 "parser.cpp"
    break;

  case 80: // helper_expr: read_expr
#line 535 "src/parser.y"
                { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < read_ptr > ()); }
#line 2054 "parser.cpp"
    break;

  case 81: // print_expr: PRINT LBRA value_expr RBRA
#line 540 "src/parser.y"
        { 
            yylhs.value.as < print_ptr > () = std::make_unique<PrintNode>();
            yylhs.value.as < print_ptr > ()->msg = std::move(yystack_[1].value.as < expr_ptr > ());

            yylhs.value.as < print_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 2065 "parser.cpp"
    break;

  case 82: // read_expr: LABEL TSEP non_function_type ASSGN READ LBRA RBRA
#line 550 "src/parser.y"
        {
            yylhs.value.as < read_ptr > () = std::make_unique<ReadNode>();
            yylhs.value.as < read_ptr > ()->name = std::move(yystack_[6].value.as < std::string > ());
            yylhs.value.as < read_ptr > ()->type = std::move(yystack_[4].value.as < type_ptr > ());

            yylhs.value.as < read_ptr > ()->location = floc_to_loc(yystack_[6].location);
        }
#line 2077 "parser.cpp"
    break;

  case 83: // assign_expr: LABEL TSEP LBRA opt_params RBRA PROD type LBRA program RBRA
#line 561 "src/parser.y"
        { 
            auto temp = std::make_unique<FuncDecl>();
            temp->name = std::move(yystack_[9].value.as < std::string > ());
            temp->params = std::move(yystack_[6].value.as < std::vector<Param> > ());
            temp->ret = std::move(yystack_[3].value.as < type_ptr > ());
            temp->body = std::move(yystack_[1].value.as < prog_ptr > ());
            yylhs.value.as < decl_ptr > () = std::move(temp);

            yylhs.value.as < decl_ptr > ()->location = floc_to_loc(yystack_[9].location);
        }
#line 2092 "parser.cpp"
    break;

  case 84: // assign_expr: LABEL TSEP non_function_type ASSGN value_expr
#line 572 "src/parser.y"
        {
            auto temp = std::make_unique<VarDecl>();
            temp->name = std::move(yystack_[4].value.as < std::string > ());
            temp->type = std::move(yystack_[2].value.as < type_ptr > ());
            temp->r_val = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < decl_ptr > () = std::move(temp);
            yylhs.value.as < decl_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2105 "parser.cpp"
    break;

  case 85: // int_lit: INT
#line 584 "src/parser.y"
        { 
            auto temp = std::make_unique<IntLit>();
            temp->value = yystack_[0].value.as < uint64_t > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2117 "parser.cpp"
    break;

  case 86: // float_lit: FLOAT
#line 594 "src/parser.y"
        {
            auto temp = std::make_unique<IntLit>();
            temp->value = yystack_[0].value.as < double > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2129 "parser.cpp"
    break;

  case 87: // bool_lit: TRUE
#line 604 "src/parser.y"
        { 
            auto temp = std::make_unique<BoolLit>();
            temp->value = true;
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2141 "parser.cpp"
    break;

  case 88: // bool_lit: FALSE
#line 612 "src/parser.y"
        { 
            auto temp = std::make_unique<BoolLit>();
            temp->value = false;
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2153 "parser.cpp"
    break;

  case 89: // char_lit: CHAR
#line 623 "src/parser.y"
        { 
            auto temp = std::make_unique<CharLit>();
            temp->value = yystack_[0].value.as < char > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2165 "parser.cpp"
    break;

  case 90: // bool_op: BOR
#line 632 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::BOR; }
#line 2171 "parser.cpp"
    break;

  case 91: // bool_op: BAND
#line 633 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::BAND; }
#line 2177 "parser.cpp"
    break;

  case 92: // comp_op: CEQ
#line 637 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CEQ; }
#line 2183 "parser.cpp"
    break;

  case 93: // comp_op: CNEQ
#line 638 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CNEQ; }
#line 2189 "parser.cpp"
    break;

  case 94: // comp_op: CGT
#line 639 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CGT; }
#line 2195 "parser.cpp"
    break;

  case 95: // comp_op: CLT
#line 640 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CLT; }
#line 2201 "parser.cpp"
    break;

  case 96: // comp_op: CGEQ
#line 641 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CGEQ; }
#line 2207 "parser.cpp"
    break;

  case 97: // comp_op: CLEQ
#line 642 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CLEQ; }
#line 2213 "parser.cpp"
    break;

  case 98: // bitwise_op: LAND
#line 646 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::LAND; }
#line 2219 "parser.cpp"
    break;

  case 99: // bitwise_op: BAR
#line 647 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LOR; }
#line 2225 "parser.cpp"
    break;

  case 100: // bitwise_op: LXOR
#line 648 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::LXOR; }
#line 2231 "parser.cpp"
    break;

  case 101: // shift_op: LSL
#line 651 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LSL; }
#line 2237 "parser.cpp"
    break;

  case 102: // shift_op: LSR
#line 652 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LSR; }
#line 2243 "parser.cpp"
    break;

  case 103: // additive_op: ADD
#line 655 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::ADD; }
#line 2249 "parser.cpp"
    break;

  case 104: // additive_op: SUB
#line 656 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::SUB; }
#line 2255 "parser.cpp"
    break;

  case 105: // additive_op: CONCAT
#line 657 "src/parser.y"
             { yylhs.value.as < BinaryOp > () = BinaryOp::CONCAT; }
#line 2261 "parser.cpp"
    break;

  case 106: // mult_op: MUL
#line 661 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::MUL; }
#line 2267 "parser.cpp"
    break;

  case 107: // mult_op: DIV
#line 662 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::DIV; }
#line 2273 "parser.cpp"
    break;

  case 108: // mult_op: MOD
#line 663 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::MOD; }
#line 2279 "parser.cpp"
    break;

  case 109: // mult_op: FLR
#line 664 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::FLR; }
#line 2285 "parser.cpp"
    break;

  case 110: // unary_op: BNOT
#line 668 "src/parser.y"
           { yylhs.value.as < UnaryOp > () = UnaryOp::BNOT; }
#line 2291 "parser.cpp"
    break;

  case 111: // unary_op: LNEG
#line 669 "src/parser.y"
           { yylhs.value.as < UnaryOp > () = UnaryOp::LNEG; }
#line 2297 "parser.cpp"
    break;

  case 112: // unary_op: SUB
#line 670 "src/parser.y"
          { yylhs.value.as < UnaryOp > () = UnaryOp::MINUS; }
#line 2303 "parser.cpp"
    break;

  case 113: // nominal_expr: LABEL
#line 675 "src/parser.y"
        { 
            auto temp = std::make_unique<NominalNode>();
            temp->label = std::move(yystack_[0].value.as < std::string > ()); 
            yylhs.value.as < expr_ptr > () = std::move(temp);
            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2314 "parser.cpp"
    break;

  case 114: // list_expr: empty_list
#line 683 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < list_ptr > ()); }
#line 2320 "parser.cpp"
    break;

  case 115: // list_expr: list_con
#line 684 "src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < list_ptr > ()); }
#line 2326 "parser.cpp"
    break;

  case 116: // list_expr: string_lit
#line 685 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2332 "parser.cpp"
    break;

  case 117: // empty_list: SQ_LBRA SQ_RBRA
#line 690 "src/parser.y"
        { 
            yylhs.value.as < list_ptr > () = std::make_unique<ListNode>(); 
            yylhs.value.as < list_ptr > ()->elems = std::vector<expr_ptr>{}; 
            yylhs.value.as < list_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2342 "parser.cpp"
    break;

  case 118: // list_con: SQ_LBRA expr_list SQ_RBRA
#line 699 "src/parser.y"
        { 
            yylhs.value.as < list_ptr > () = std::make_unique<ListNode>(); 
            yylhs.value.as < list_ptr > ()->elems = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ()); 
            yylhs.value.as < list_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 2352 "parser.cpp"
    break;

  case 119: // expr_list: value_expr
#line 708 "src/parser.y"
        { 
            yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>{};
            yylhs.value.as < std::vector<expr_ptr> > ().push_back(std::move(yystack_[0].value.as < expr_ptr > ())); 
        }
#line 2361 "parser.cpp"
    break;

  case 120: // expr_list: expr_list COMMA value_expr
#line 713 "src/parser.y"
        {
            yystack_[2].value.as < std::vector<expr_ptr> > ().push_back(std::move(yystack_[0].value.as < expr_ptr > ()));
            yylhs.value.as < std::vector<expr_ptr> > () = std::move(yystack_[2].value.as < std::vector<expr_ptr> > ());
        }
#line 2370 "parser.cpp"
    break;

  case 121: // call_expr: LABEL LBRA RBRA
#line 721 "src/parser.y"
        {
            auto temp = std::make_unique<CallNode>();
            temp->label = std::move(yystack_[2].value.as < std::string > ());
            temp->params = std::vector<expr_ptr>{};
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 2383 "parser.cpp"
    break;

  case 122: // call_expr: LABEL LBRA expr_list RBRA
#line 730 "src/parser.y"
        {
            auto temp = std::make_unique<CallNode>(); 
            temp->label = std::move(yystack_[3].value.as < std::string > ());
            temp->params = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 2396 "parser.cpp"
    break;

  case 123: // struct_expr: LABEL C_LBRA expr_list C_RBRA
#line 742 "src/parser.y"
        {
            auto temp = std::make_unique<StructNode>();
            temp->name = std::move(yystack_[3].value.as < std::string > ());
            temp->fields = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 2409 "parser.cpp"
    break;

  case 124: // value_expr: bool_expr
#line 752 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2415 "parser.cpp"
    break;

  case 125: // bool_expr: comp_expr
#line 755 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2421 "parser.cpp"
    break;

  case 126: // bool_expr: bool_expr bool_op comp_expr
#line 757 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2435 "parser.cpp"
    break;

  case 127: // comp_expr: bitwise_expr
#line 769 "src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2441 "parser.cpp"
    break;

  case 128: // comp_expr: bitwise_expr comp_op bitwise_expr
#line 771 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2455 "parser.cpp"
    break;

  case 129: // bitwise_expr: shift_expr
#line 783 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2461 "parser.cpp"
    break;

  case 130: // bitwise_expr: bitwise_expr bitwise_op shift_expr
#line 785 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2475 "parser.cpp"
    break;

  case 131: // shift_expr: additive_expr
#line 797 "src/parser.y"
                    { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2481 "parser.cpp"
    break;

  case 132: // shift_expr: shift_expr shift_op additive_expr
#line 799 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2495 "parser.cpp"
    break;

  case 133: // additive_expr: mult_expr
#line 811 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2501 "parser.cpp"
    break;

  case 134: // additive_expr: additive_expr additive_op mult_expr
#line 813 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2515 "parser.cpp"
    break;

  case 135: // mult_expr: pow_expr
#line 825 "src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2521 "parser.cpp"
    break;

  case 136: // mult_expr: mult_expr mult_op pow_expr
#line 827 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2535 "parser.cpp"
    break;

  case 137: // pow_expr: unary_expr
#line 839 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2541 "parser.cpp"
    break;

  case 138: // pow_expr: unary_expr POW pow_expr
#line 841 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = BinaryOp::POW;
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2555 "parser.cpp"
    break;

  case 139: // unary_expr: postfix_expr
#line 853 "src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2561 "parser.cpp"
    break;

  case 140: // unary_expr: unary_op postfix_expr
#line 855 "src/parser.y"
        {
            auto temp = std::make_unique<UnaryNode>();
            temp->op = yystack_[1].value.as < UnaryOp > ();
            temp->exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2574 "parser.cpp"
    break;

  case 141: // postfix_expr: literal_expr
#line 866 "src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2580 "parser.cpp"
    break;

  case 142: // postfix_expr: postfix_expr SQ_LBRA value_expr SQ_RBRA
#line 868 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = BinaryOp::INDEX;
            temp->l_exp = std::move(yystack_[3].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[1].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 2594 "parser.cpp"
    break;

  case 143: // postfix_expr: postfix_expr DOT LABEL
#line 878 "src/parser.y"
        {
            auto temp = std::make_unique<AccessNode>();
            temp->field = std::move(yystack_[0].value.as < std::string > ());
            temp->struct_expr = std::move(yystack_[2].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2607 "parser.cpp"
    break;

  case 144: // literal_expr: int_lit
#line 889 "src/parser.y"
              { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2613 "parser.cpp"
    break;

  case 145: // literal_expr: float_lit
#line 890 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2619 "parser.cpp"
    break;

  case 146: // literal_expr: char_lit
#line 891 "src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2625 "parser.cpp"
    break;

  case 147: // literal_expr: bool_lit
#line 892 "src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2631 "parser.cpp"
    break;

  case 148: // literal_expr: list_expr
#line 893 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2637 "parser.cpp"
    break;

  case 149: // literal_expr: nominal_expr
#line 894 "src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2643 "parser.cpp"
    break;

  case 150: // literal_expr: call_expr
#line 895 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2649 "parser.cpp"
    break;

  case 151: // literal_expr: struct_expr
#line 896 "src/parser.y"
                  { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2655 "parser.cpp"
    break;

  case 152: // literal_expr: LBRA value_expr RBRA
#line 897 "src/parser.y"
                           { yylhs.value.as < expr_ptr > () = std::move(yystack_[1].value.as < expr_ptr > ()); }
#line 2661 "parser.cpp"
    break;


#line 2665 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
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


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const short parser::yypact_ninf_ = -195;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
    -195,     1,    55,  -195,  -195,     4,    60,    74,  -195,  -195,
    -195,  -195,   -26,    58,    70,   106,   111,   113,    -1,   124,
     126,  -195,   130,     8,  -195,  -195,  -195,    29,   182,   147,
     106,   182,  -195,   111,  -195,   113,  -195,  -195,  -195,  -195,
    -195,  -195,  -195,   182,   182,  -195,  -195,  -195,  -195,  -195,
    -195,  -195,  -195,   182,  -195,  -195,  -195,  -195,   158,   157,
    -195,   161,  -195,   129,   182,  -195,  -195,   174,   182,  -195,
     163,   192,   104,   183,   104,  -195,  -195,  -195,  -195,  -195,
    -195,  -195,  -195,  -195,   191,   165,  -195,  -195,  -195,  -195,
      51,  -195,  -195,   104,     3,  -195,  -195,  -195,  -195,  -195,
    -195,  -195,  -195,   168,  -195,  -195,  -195,  -195,  -195,  -195,
     194,    -4,  -195,   181,    39,   -11,   196,  -195,   175,   -12,
    -195,   104,  -195,   106,   185,   177,    11,   104,   197,  -195,
     115,  -195,   -12,   205,  -195,  -195,   104,  -195,  -195,  -195,
    -195,  -195,  -195,  -195,  -195,  -195,   104,   104,  -195,  -195,
     104,  -195,  -195,  -195,   104,  -195,  -195,  -195,  -195,   104,
     104,   104,   221,   215,   216,    43,    72,    80,  -195,  -195,
      53,    91,  -195,  -195,   104,   134,  -195,   -23,    39,   -11,
     196,  -195,  -195,   217,  -195,  -195,   186,   218,  -195,   184,
     188,   177,  -195,  -195,  -195,  -195,   213,  -195,  -195,   125,
     110,  -195,  -195,   189,  -195,  -195,  -195,  -195,   219,  -195,
    -195,  -195,  -195,  -195,   182,   224,  -195,  -195,  -195,   248,
    -195,  -195,   127,   134,  -195,  -195,   250,   229,  -195,  -195,
    -195,  -195,  -195,   173,  -195,  -195,  -195,  -195,  -195,   230,
    -195
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     1,     2,     0,     0,     0,     4,     5,
       6,     7,     0,     0,     0,    28,     0,     0,     0,     0,
      29,    30,     0,     0,    34,    38,    39,     0,     0,     0,
       0,     0,    37,     0,    41,     0,    27,    21,    22,    23,
      24,    17,    18,     8,     0,    15,    32,    12,    19,    20,
      13,    16,    14,     0,    31,    36,    35,    40,     0,     9,
      10,     0,    76,     0,     0,    25,    33,     0,     0,    11,
       0,     0,     0,     0,     0,    42,    44,    45,    43,    77,
      79,    80,    78,    26,     0,     0,    85,    86,    89,    69,
     113,    87,    88,     0,     0,   112,   111,   110,   116,   144,
     145,   147,   146,     0,   149,   148,   114,   115,   150,   151,
       0,   124,   125,   127,   129,   131,   133,   135,   137,   139,
     141,     0,    75,    28,     0,     0,     0,     0,     0,   117,
       0,   119,   140,     0,    91,    90,     0,    98,    99,   100,
      94,    95,    96,    97,    92,    93,     0,     0,   101,   102,
       0,   103,   104,   105,     0,   106,   107,   108,   109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    47,   121,
       0,     0,   152,   118,     0,     0,   126,   128,   130,   132,
     134,   136,   138,     0,   143,    81,     0,     0,    84,     0,
       0,     0,    46,   122,   123,   120,    64,    63,    62,     0,
       0,    52,    61,     0,    59,    60,    67,    66,    68,    56,
      57,    58,    55,   142,     0,     0,    76,    76,    48,     0,
      65,    71,     0,     0,    51,    76,     0,     0,    82,    50,
      49,    73,    70,     0,    53,    54,    74,    76,    72,     0,
      83
  };

  const short
  parser::yypgoto_[] =
  {
    -195,  -195,  -195,  -195,  -195,  -195,   178,   -31,  -195,  -195,
    -195,  -195,  -195,  -195,   136,  -195,   231,  -195,  -195,   232,
    -195,   228,  -195,  -195,     7,  -195,  -195,  -195,    73,  -195,
    -195,    44,  -194,  -195,  -195,  -195,  -131,  -195,  -195,  -195,
    -195,  -195,  -195,  -195,  -195,  -195,  -117,  -106,   -75,   -63,
    -195,  -195,  -195,  -195,  -195,  -195,  -195,  -195,  -195,  -195,
    -195,    37,  -195,  -195,   -70,  -195,   132,   120,   122,   121,
     116,     9,  -195,   169,  -195
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     1,     2,     8,    58,    59,    45,    46,    47,    48,
      49,    50,    51,    52,    19,    20,    21,     9,    23,    24,
      10,    26,    27,    11,    66,    75,    76,   167,   168,    77,
     200,   201,   202,   203,   204,   205,    98,   207,   222,   208,
      78,    67,    79,    80,    81,    82,    99,   100,   101,   102,
     136,   146,   147,   150,   154,   159,   103,   104,   105,   106,
     107,   130,   108,   109,   131,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120
  };

  const unsigned char
  parser::yytable_[] =
  {
      55,     3,   110,    15,   122,   221,    86,    87,    88,    89,
      90,    12,    60,    61,    86,    87,    88,    89,    90,   161,
      91,    92,    62,   128,   162,   137,   138,   139,    91,    92,
     151,   152,    93,    69,    94,   129,    28,    83,    32,   238,
      93,   169,    94,    33,   206,    95,    86,    87,    88,    89,
      90,   163,   153,    95,    96,     4,   134,   135,   209,    34,
      91,    92,    96,   187,    35,    97,     5,    13,   206,   210,
       6,     7,    93,    97,    94,    86,    87,    88,    89,    90,
     126,    14,   209,   193,   127,    95,   189,    16,   174,    91,
      92,   183,   206,   210,    96,   188,   190,   148,   149,    17,
     211,    93,   206,    94,   195,    97,   209,    86,    87,    88,
      89,    90,   212,    18,    95,   191,   209,   210,    22,   192,
      25,    91,    92,    96,   211,   194,   174,   210,    86,    87,
      88,    89,   196,    93,    97,    94,   212,    86,    87,    88,
      89,   196,    91,    92,   197,   223,    95,   173,   211,   224,
     174,    91,    92,   198,    29,    96,   199,   220,   211,   232,
     212,    30,   233,   170,   171,   199,    97,    31,   181,   182,
     212,    86,    87,    88,    89,    90,    86,    87,    88,    89,
     196,    70,    71,   227,    53,    91,    92,    72,    63,    36,
      91,    92,    64,    65,    68,    73,    74,    93,    36,    94,
      84,    85,   125,   133,   199,    37,    38,    39,    40,    41,
      42,    43,   121,    44,    37,    38,    39,    40,    41,    42,
     123,   160,    44,   229,   230,   165,   166,   172,   184,   137,
     138,   139,   235,   140,   141,   142,   143,   144,   145,   155,
     156,   157,   175,   158,   239,   185,   186,   215,   216,   213,
     219,   214,   217,   225,   228,   231,   226,   236,   237,   164,
     240,    54,   124,    57,   218,    56,   177,   234,   176,   178,
     180,   179,   132
  };

  const unsigned char
  parser::yycheck_[] =
  {
      31,     0,    72,    29,    74,   199,     3,     4,     5,     6,
       7,     7,    43,    44,     3,     4,     5,     6,     7,    31,
      17,    18,    53,    93,    36,    48,    49,    50,    17,    18,
      41,    42,    29,    64,    31,    32,    37,    68,    30,   233,
      29,    30,    31,    35,   175,    42,     3,     4,     5,     6,
       7,   121,    63,    42,    51,     0,    60,    61,   175,    30,
      17,    18,    51,    20,    35,    62,    11,     7,   199,   175,
      15,    16,    29,    62,    31,     3,     4,     5,     6,     7,
      29,     7,   199,    30,    33,    42,    14,    29,    35,    17,
      18,   161,   223,   199,    51,   165,   166,    58,    59,    29,
     175,    29,   233,    31,   174,    62,   223,     3,     4,     5,
       6,     7,   175,     7,    42,    35,   233,   223,     7,    39,
       7,    17,    18,    51,   199,    34,    35,   233,     3,     4,
       5,     6,     7,    29,    62,    31,   199,     3,     4,     5,
       6,     7,    17,    18,    10,    35,    42,    32,   223,    39,
      35,    17,    18,    19,    30,    51,    31,    32,   233,    32,
     223,    35,    35,   126,   127,    31,    62,    37,   159,   160,
     233,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,     7,     8,   214,    37,    17,    18,    13,    30,     7,
      17,    18,    35,    32,    65,    21,    22,    29,     7,    31,
      37,     9,    37,     9,    31,    23,    24,    25,    26,    27,
      28,    29,    29,    31,    23,    24,    25,    26,    27,    28,
      29,    46,    31,   216,   217,    40,    49,    30,     7,    48,
      49,    50,   225,    52,    53,    54,    55,    56,    57,    43,
      44,    45,    37,    47,   237,    30,    30,    29,    64,    32,
      37,    65,    64,    64,    30,     7,    37,     7,    29,   123,
      30,    30,    84,    35,   191,    33,   146,   223,   136,   147,
     154,   150,   103
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    67,    68,     0,     0,    11,    15,    16,    69,    83,
      86,    89,     7,     7,     7,    29,    29,    29,     7,    80,
      81,    82,     7,    84,    85,     7,    87,    88,    37,    30,
      35,    37,    30,    35,    30,    35,     7,    23,    24,    25,
      26,    27,    28,    29,    31,    72,    73,    74,    75,    76,
      77,    78,    79,    37,    82,    73,    85,    87,    70,    71,
      73,    73,    73,    30,    35,    32,    90,   107,    65,    73,
       7,     8,    13,    21,    22,    91,    92,    95,   106,   108,
     109,   110,   111,    73,    37,     9,     3,     4,     5,     6,
       7,    17,    18,    29,    31,    42,    51,    62,   102,   112,
     113,   114,   115,   122,   123,   124,   125,   126,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,    29,   130,    29,    72,    37,    29,    33,   130,    32,
     127,   130,   139,     9,    60,    61,   116,    48,    49,    50,
      52,    53,    54,    55,    56,    57,   117,   118,    58,    59,
     119,    41,    42,    63,   120,    43,    44,    45,    47,   121,
      46,    31,    36,   130,    80,    40,    49,    93,    94,    30,
     127,   127,    30,    32,    35,    37,   132,   133,   134,   135,
     136,   137,   137,   130,     7,    30,    30,    20,   130,    14,
     130,    35,    39,    30,    34,   130,     7,    10,    19,    31,
      96,    97,    98,    99,   100,   101,   102,   103,   105,   112,
     113,   114,   115,    32,    65,    29,    64,    64,    94,    37,
      32,    98,   104,    35,    39,    64,    37,    73,    30,    90,
      90,     7,    32,    35,    97,    90,     7,    29,    98,    90,
      30
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    66,    67,    68,    68,    69,    69,    69,    70,    70,
      71,    71,    72,    72,    72,    73,    73,    74,    74,    74,
      74,    75,    75,    76,    76,    77,    78,    79,    80,    80,
      81,    81,    82,    83,    84,    84,    85,    86,    87,    88,
      88,    89,    90,    91,    91,    91,    92,    93,    93,    94,
      94,    95,    96,    96,    97,    98,    98,    98,    98,    98,
      98,    99,    99,    99,   100,   101,   101,   101,   101,   102,
     103,   104,   104,   105,   105,   106,   107,   107,   108,   108,
     108,   109,   110,   111,   111,   112,   113,   114,   114,   115,
     116,   116,   117,   117,   117,   117,   117,   117,   118,   118,
     118,   119,   119,   120,   120,   120,   121,   121,   121,   121,
     122,   122,   122,   123,   124,   124,   124,   125,   126,   127,
     127,   128,   128,   129,   130,   131,   131,   132,   132,   133,
     133,   134,   134,   135,   135,   136,   136,   137,   137,   138,
     138,   139,   139,   139,   140,   140,   140,   140,   140,   140,
     140,   140,   140
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     2,     1,     1,     1,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     5,     1,     0,     1,
       1,     3,     3,     8,     1,     3,     3,     5,     1,     1,
       3,     5,     2,     1,     1,     1,     5,     1,     3,     4,
       4,     6,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       3,     1,     3,     3,     3,     2,     0,     2,     1,     1,
       1,     4,     7,    10,     5,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     1,
       3,     3,     4,     4,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       2,     1,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "KEOF", "error", "\"invalid token\"", "INT", "FLOAT", "CHAR", "STRING",
  "LABEL", "CASE", "OF", "DEFAULT", "FUNC", "LAMB", "MARK", "ELSE",
  "STRUCT", "ENUM", "TRUE", "FALSE", "NIL", "READ", "PRINT", "RETURN",
  "T_INT", "T_LONG", "T_FLOAT", "T_DOUBLE", "T_CHAR", "T_BOOL", "LBRA",
  "RBRA", "SQ_LBRA", "SQ_RBRA", "C_LBRA", "C_RBRA", "COMMA", "DOT", "TSEP",
  "EMPTY", "PEND", "ASSGN", "ADD", "SUB", "MUL", "DIV", "MOD", "POW",
  "FLR", "LAND", "BAR", "LXOR", "LNEG", "CGT", "CLT", "CGEQ", "CLEQ",
  "CEQ", "CNEQ", "LSL", "LSR", "BAND", "BOR", "BNOT", "CONCAT", "ARROW",
  "PROD", "$accept", "module", "definitions", "definition", "opt_types",
  "types", "non_function_type", "type", "literal_type", "int_lit_type",
  "float_lit_type", "list_type", "func_type", "nominal_type", "opt_params",
  "params", "param", "function_def", "fields", "field", "struct_def",
  "evar", "evars", "enum_def", "program", "branch_expr", "guard_expr",
  "guards", "guard", "case_expr", "patterns", "pattern_branch", "literal",
  "pattern", "enum_lit", "list_pattern", "string_lit", "list_lit",
  "list_pattern_lit", "size_patterns", "return_expr", "helpers",
  "helper_expr", "print_expr", "read_expr", "assign_expr", "int_lit",
  "float_lit", "bool_lit", "char_lit", "bool_op", "comp_op", "bitwise_op",
  "shift_op", "additive_op", "mult_op", "unary_op", "nominal_expr",
  "list_expr", "empty_list", "list_con", "expr_list", "call_expr",
  "struct_expr", "value_expr", "bool_expr", "comp_expr", "bitwise_expr",
  "shift_expr", "additive_expr", "mult_expr", "pow_expr", "unary_expr",
  "postfix_expr", "literal_expr", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   183,   183,   192,   194,   202,   203,   204,   207,   208,
     211,   212,   218,   219,   220,   224,   225,   229,   230,   231,
     232,   236,   237,   240,   241,   244,   247,   250,   253,   254,
     257,   258,   265,   275,   288,   290,   298,   308,   319,   322,
     323,   331,   342,   351,   352,   353,   357,   365,   370,   378,
     384,   395,   404,   409,   417,   428,   429,   430,   431,   432,
     433,   437,   438,   439,   443,   453,   461,   462,   463,   474,
     477,   487,   492,   500,   506,   513,   524,   525,   533,   534,
     535,   539,   549,   560,   571,   583,   593,   603,   611,   622,
     632,   633,   637,   638,   639,   640,   641,   642,   646,   647,
     648,   651,   652,   655,   656,   657,   661,   662,   663,   664,
     668,   669,   670,   674,   683,   684,   685,   689,   698,   707,
     712,   720,   729,   741,   752,   755,   756,   769,   770,   783,
     784,   797,   798,   811,   812,   825,   826,   839,   840,   853,
     854,   866,   867,   877,   889,   890,   891,   892,   893,   894,
     895,   896,   897
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 39 "src/parser.y"
} // yy
#line 3172 "parser.cpp"

