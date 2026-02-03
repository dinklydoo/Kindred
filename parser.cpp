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
#line 6 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"

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

#line 70 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"


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

#line 39 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
namespace yy {
#line 168 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"

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
      case symbol_kind::S_string_expr: // string_expr
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
      case symbol_kind::S_list_size_pattern: // list_size_pattern
      case symbol_kind::S_struct_size_pattern: // struct_size_pattern
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

      case symbol_kind::S_evars: // evars
      case symbol_kind::S_list_vars: // list_vars
      case symbol_kind::S_struct_vars: // struct_vars
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
      case symbol_kind::S_string_expr: // string_expr
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
      case symbol_kind::S_list_size_pattern: // list_size_pattern
      case symbol_kind::S_struct_size_pattern: // struct_size_pattern
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

      case symbol_kind::S_evars: // evars
      case symbol_kind::S_list_vars: // list_vars
      case symbol_kind::S_struct_vars: // struct_vars
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
      case symbol_kind::S_string_expr: // string_expr
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
      case symbol_kind::S_list_size_pattern: // list_size_pattern
      case symbol_kind::S_struct_size_pattern: // struct_size_pattern
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

      case symbol_kind::S_evars: // evars
      case symbol_kind::S_list_vars: // list_vars
      case symbol_kind::S_struct_vars: // struct_vars
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
      case symbol_kind::S_string_expr: // string_expr
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
      case symbol_kind::S_list_size_pattern: // list_size_pattern
      case symbol_kind::S_struct_size_pattern: // struct_size_pattern
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

      case symbol_kind::S_evars: // evars
      case symbol_kind::S_list_vars: // list_vars
      case symbol_kind::S_struct_vars: // struct_vars
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
      case symbol_kind::S_string_expr: // string_expr
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
      case symbol_kind::S_list_size_pattern: // list_size_pattern
      case symbol_kind::S_struct_size_pattern: // struct_size_pattern
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

      case symbol_kind::S_evars: // evars
      case symbol_kind::S_list_vars: // list_vars
      case symbol_kind::S_struct_vars: // struct_vars
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
#line 186 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < module_ptr > () = std::make_unique<ModuleNode>();
            yylhs.value.as < module_ptr > ()->decl = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
            module_node = std::move(yylhs.value.as < module_ptr > ());
        }
#line 1445 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 3: // definitions: %empty
#line 195 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { yylhs.value.as < std::vector<decl_ptr> > () = std::vector<decl_ptr>{}; }
#line 1451 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 4: // definitions: definitions definition
#line 197 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yystack_[1].value.as < std::vector<decl_ptr> > ().push_back(std::move(yystack_[0].value.as < decl_ptr > ()));
            yylhs.value.as < std::vector<decl_ptr> > () = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
        }
#line 1460 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 5: // definition: function_def
#line 204 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                  { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < func_decl_ptr > ()); }
#line 1466 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 6: // definition: struct_def
#line 205 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < struct_decl_ptr > ()); }
#line 1472 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 7: // definition: enum_def
#line 206 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < enum_decl_ptr > ()); }
#line 1478 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 8: // opt_types: %empty
#line 209 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < std::vector<type_ptr> > () = std::vector<type_ptr>{}; }
#line 1484 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 9: // opt_types: types
#line 210 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
            { yylhs.value.as < std::vector<type_ptr> > () = std::move(yystack_[0].value.as < std::vector<type_ptr> > ()); }
#line 1490 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 10: // types: type
#line 213 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < std::vector<type_ptr> > () = std::vector<type_ptr>{yystack_[0].value.as < type_ptr > ()}; }
#line 1496 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 11: // types: types COMMA type
#line 214 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                       {
        yystack_[2].value.as < std::vector<type_ptr> > ().push_back(std::move(yystack_[0].value.as < type_ptr > ()));
        yylhs.value.as < std::vector<type_ptr> > () = std::move(yystack_[2].value.as < std::vector<type_ptr> > ());
    }
#line 1505 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 12: // non_function_type: literal_type
#line 220 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1511 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 13: // non_function_type: list_type
#line 221 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1517 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 14: // non_function_type: nominal_type
#line 222 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1523 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 15: // type: non_function_type
#line 226 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                        { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1529 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 16: // type: func_type
#line 227 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1535 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 17: // literal_type: T_CHAR
#line 231 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.char_type(); }
#line 1541 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 18: // literal_type: T_BOOL
#line 232 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.bool_type(); }
#line 1547 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 19: // literal_type: int_lit_type
#line 233 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1553 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 20: // literal_type: float_lit_type
#line 234 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                     { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1559 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 21: // int_lit_type: T_INT
#line 238 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
            { yylhs.value.as < type_ptr > () = type_s.int_type(); }
#line 1565 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 22: // int_lit_type: T_LONG
#line 239 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.long_type(); }
#line 1571 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 23: // float_lit_type: T_FLOAT
#line 242 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < type_ptr > () = type_s.float_type(); }
#line 1577 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 24: // float_lit_type: T_DOUBLE
#line 243 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < type_ptr > () = type_s.double_type(); }
#line 1583 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 25: // list_type: SQ_LBRA type SQ_RBRA
#line 246 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                           { yylhs.value.as < type_ptr > () = type_s.list_type(yystack_[1].value.as < type_ptr > ()); }
#line 1589 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 26: // func_type: LBRA opt_types RBRA PROD type
#line 249 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                                    { yylhs.value.as < type_ptr > () = type_s.func_type(yystack_[3].value.as < std::vector<type_ptr> > (), yystack_[0].value.as < type_ptr > ()); }
#line 1595 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 27: // nominal_type: LABEL
#line 252 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
            { yylhs.value.as < type_ptr > () = type_s.nominal_type(yystack_[0].value.as < std::string > ()); }
#line 1601 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 28: // opt_params: %empty
#line 255 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < std::vector<Param> > () = std::vector<Param>{}; }
#line 1607 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 29: // opt_params: params
#line 256 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < std::vector<Param> > () = std::move(yystack_[0].value.as < std::vector<Param> > ()); }
#line 1613 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 30: // params: param
#line 259 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
            { yylhs.value.as < std::vector<Param> > () = std::vector<Param>{yystack_[0].value.as < Param > ()}; }
#line 1619 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 31: // params: params COMMA param
#line 261 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<Param> > ().push_back(std::move(yystack_[0].value.as < Param > ()));
            yylhs.value.as < std::vector<Param> > () = std::move(yystack_[2].value.as < std::vector<Param> > ());
        }
#line 1628 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 32: // param: LABEL TSEP type
#line 268 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < Param > () = Param(); 
            yylhs.value.as < Param > ().name = std::move(yystack_[2].value.as < std::string > ());
            yylhs.value.as < Param > ().type = std::move(yystack_[0].value.as < type_ptr > ());
            yylhs.value.as < Param > ().location = floc_to_loc(yystack_[2].location);
        }
#line 1639 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 33: // function_def: FUNC LABEL LBRA opt_params RBRA TSEP type program
#line 278 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {   
            yylhs.value.as < func_decl_ptr > () = std::make_unique<FuncDecl>();
            yylhs.value.as < func_decl_ptr > ()->name = std::move(yystack_[6].value.as < std::string > ());
            yylhs.value.as < func_decl_ptr > ()->params = std::move(yystack_[4].value.as < std::vector<Param> > ());
            yylhs.value.as < func_decl_ptr > ()->ret = std::move(yystack_[1].value.as < type_ptr > ());
            yylhs.value.as < func_decl_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());

            yylhs.value.as < func_decl_ptr > ()->location = floc_to_loc(yystack_[7].location);
        }
#line 1653 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 34: // fields: field
#line 291 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {   yylhs.value.as < std::vector<Field> > () = std::vector<Field>{}; yylhs.value.as < std::vector<Field> > ().push_back(std::move(yystack_[0].value.as < Field > ())); }
#line 1659 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 35: // fields: fields COMMA field
#line 293 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yystack_[2].value.as < std::vector<Field> > ().push_back(std::move(yystack_[0].value.as < Field > ()));
            yylhs.value.as < std::vector<Field> > () = std::move(yystack_[2].value.as < std::vector<Field> > ());
        }
#line 1668 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 36: // field: LABEL TSEP type
#line 301 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < Field > () = Field();
            yylhs.value.as < Field > ().name = std::move(yystack_[2].value.as < std::string > ());
            yylhs.value.as < Field > ().type = std::move(yystack_[0].value.as < type_ptr > ());

            yylhs.value.as < Field > ().location = floc_to_loc(yystack_[2].location);
        }
#line 1680 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 37: // struct_def: STRUCT LABEL LBRA fields RBRA
#line 311 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < struct_decl_ptr > () = std::make_unique<StructDecl>();
            yylhs.value.as < struct_decl_ptr > ()->name = std::move(yystack_[3].value.as < std::string > ());
            yylhs.value.as < struct_decl_ptr > ()->fields = std::move(yystack_[1].value.as < std::vector<Field> > ());

            yylhs.value.as < struct_decl_ptr > ()->location = floc_to_loc(yystack_[4].location);
        }
#line 1692 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 38: // evar: LABEL
#line 321 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
            { yylhs.value.as < std::string > () = std::move(yystack_[0].value.as < std::string > ()); }
#line 1698 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 39: // evars: evar
#line 324 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{yystack_[0].value.as < std::string > ()}; }
#line 1704 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 40: // evars: evars COMMA evar
#line 326 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));
            yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ());
        }
#line 1713 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 41: // enum_def: ENUM LABEL LBRA evars RBRA
#line 334 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < enum_decl_ptr > () = std::make_unique<EnumDecl>(); 
            yylhs.value.as < enum_decl_ptr > ()->name = std::move(yystack_[3].value.as < std::string > ());
            yylhs.value.as < enum_decl_ptr > ()->evar = std::move(yystack_[1].value.as < std::vector<std::string> > ());

            yylhs.value.as < enum_decl_ptr > ()->location = floc_to_loc(yystack_[4].location);
        }
#line 1725 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 42: // program: helpers branch_expr
#line 345 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < prog_ptr > () = std::make_unique<ProgramNode>();
            yylhs.value.as < prog_ptr > ()->decl = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
            yylhs.value.as < prog_ptr > ()->body = std::move(yystack_[0].value.as < expr_ptr > ());
        }
#line 1735 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 43: // branch_expr: return_expr
#line 353 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                  { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 1741 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 44: // branch_expr: guard_expr
#line 354 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < guard_ptr > ()); }
#line 1747 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 45: // branch_expr: case_expr
#line 355 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < case_ptr > ()); }
#line 1753 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 46: // guard_expr: CASE OF TSEP guards PEND
#line 360 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < guard_ptr > () = std::make_unique<GuardNode>();
            yylhs.value.as < guard_ptr > ()->branches = std::move(yystack_[1].value.as < std::vector<g_branch_ptr> > ());

            yylhs.value.as < guard_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 1764 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 47: // guards: guard
#line 370 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < std::vector<g_branch_ptr> > () = std::vector<g_branch_ptr>{}; 
            yylhs.value.as < std::vector<g_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < g_branch_ptr > ()));
        }
#line 1773 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 48: // guards: guards COMMA guard
#line 375 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<g_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < g_branch_ptr > ()));
            yylhs.value.as < std::vector<g_branch_ptr> > () = std::move(yystack_[2].value.as < std::vector<g_branch_ptr> > ());
        }
#line 1782 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 49: // guard: BAR value_expr ARROW program
#line 383 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < g_branch_ptr > () = std::make_unique<GuardBranchNode>();
            yylhs.value.as < g_branch_ptr > ()->match = std::move(yystack_[2].value.as < expr_ptr > ());
            yylhs.value.as < g_branch_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());

            yylhs.value.as < g_branch_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 1794 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 50: // guard: BAR ELSE ARROW program
#line 391 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < g_branch_ptr > () = std::make_unique<GuardBranchNode>();
            //auto temp = std::make_unique<BoolLit>();
            //temp->value = true;
            //$$->match = std::move(temp);

            auto temp = std::make_unique<ElseLit>();
            yylhs.value.as < g_branch_ptr > ()->match = std::move(temp);
            yylhs.value.as < g_branch_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());

            yylhs.value.as < g_branch_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 1811 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 51: // case_expr: MARK value_expr OF TSEP patterns PEND
#line 407 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < case_ptr > () = std::make_unique<CaseNode>();
            yylhs.value.as < case_ptr > ()->target = std::move(yystack_[4].value.as < expr_ptr > ());
            yylhs.value.as < case_ptr > ()->patterns = std::move(yystack_[1].value.as < std::vector<c_branch_ptr> > ());

            yylhs.value.as < case_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 1823 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 52: // patterns: pattern_branch
#line 418 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < std::vector<c_branch_ptr> > () = std::vector<c_branch_ptr>{}; 
            yylhs.value.as < std::vector<c_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < c_branch_ptr > ())); 
        }
#line 1832 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 53: // patterns: patterns COMMA pattern_branch
#line 423 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<c_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < c_branch_ptr > ()));
            yylhs.value.as < std::vector<c_branch_ptr> > () = std::move(yystack_[2].value.as < std::vector<c_branch_ptr> > ());
        }
#line 1841 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 54: // pattern_branch: pattern ARROW program
#line 431 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < c_branch_ptr > () = std::make_unique<CaseBranchNode>();
            yylhs.value.as < c_branch_ptr > ()->pattern = std::move(yystack_[2].value.as < literal_ptr > ());
            yylhs.value.as < c_branch_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());

            yylhs.value.as < c_branch_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 1853 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 55: // literal: char_lit
#line 441 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1859 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 56: // literal: int_lit
#line 442 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1865 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 57: // literal: float_lit
#line 443 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1871 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 58: // literal: bool_lit
#line 444 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1877 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 59: // literal: enum_lit
#line 445 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1883 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 60: // literal: list_pattern
#line 446 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1889 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 61: // pattern: literal
#line 450 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1895 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 62: // pattern: list_size_pattern
#line 451 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                        { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1901 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 63: // pattern: struct_size_pattern
#line 452 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                          { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1907 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 64: // pattern: DEFAULT
#line 453 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::make_unique<DefaultLit>(); yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);}
#line 1913 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 65: // pattern: NIL
#line 454 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < literal_ptr > () = std::make_unique<NilLit>(); yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);}
#line 1919 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 66: // enum_lit: LABEL
#line 459 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<EnumLit>();
            temp->elem = std::move(yystack_[0].value.as < std::string > ()); 
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 1931 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 67: // list_pattern: SQ_LBRA SQ_RBRA
#line 469 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < literal_ptr > () = std::make_unique<EmptyLit>();

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 1941 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 68: // string_expr: STRING
#line 477 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             {yylhs.value.as < expr_ptr > () = str_to_chlist(yystack_[0].value.as < std::string > ()); yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[0].location); }
#line 1947 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 69: // list_size_pattern: list_vars
#line 482 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<ListPatternLit>(); 
            temp->patterns = std::move(yystack_[0].value.as < std::vector<std::string> > ());
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 1959 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 70: // list_vars: LABEL TSEP LABEL
#line 493 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{};
            yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[2].value.as < std::string > ()));
            yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ())); 
        }
#line 1969 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 71: // list_vars: list_vars TSEP LABEL
#line 499 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));
            yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ());
        }
#line 1978 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 72: // struct_size_pattern: LABEL C_LBRA struct_vars C_RBRA
#line 507 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<StructPatternLit>();
            temp->name = std::move(yystack_[3].value.as < std::string > ());
            temp->patterns = std::move(yystack_[1].value.as < std::vector<std::string> > ());
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 1991 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 73: // struct_vars: LABEL
#line 518 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{}; yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));}
#line 1997 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 74: // struct_vars: NIL
#line 519 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
         { yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{}; yylhs.value.as < std::vector<std::string> > ().push_back("");}
#line 2003 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 75: // struct_vars: struct_vars COMMA LABEL
#line 520 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                              { yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ())); yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ()); }
#line 2009 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 76: // struct_vars: struct_vars COMMA NIL
#line 521 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                            { yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move("")); yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ()); }
#line 2015 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 77: // return_expr: RETURN value_expr
#line 526 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<ReturnNode>();
            temp->rexp = std::move(yystack_[0].value.as < expr_ptr > ()); 
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2027 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 78: // helpers: %empty
#line 536 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < std::vector<decl_ptr> > () = std::vector<decl_ptr>{}; }
#line 2033 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 79: // helpers: helpers helper_expr
#line 538 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[1].value.as < std::vector<decl_ptr> > ().push_back(std::move(yystack_[0].value.as < decl_ptr > ()));
            yylhs.value.as < std::vector<decl_ptr> > () = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
        }
#line 2042 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 80: // helper_expr: assign_expr
#line 545 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                  { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < decl_ptr > ()); }
#line 2048 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 81: // helper_expr: print_expr
#line 546 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < print_ptr > ()); }
#line 2054 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 82: // helper_expr: read_expr
#line 547 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < read_ptr > ()); }
#line 2060 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 83: // print_expr: PRINT LBRA value_expr RBRA
#line 552 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < print_ptr > () = std::make_unique<PrintNode>();
            yylhs.value.as < print_ptr > ()->msg = std::move(yystack_[1].value.as < expr_ptr > ());

            yylhs.value.as < print_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 2071 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 84: // read_expr: LABEL TSEP non_function_type ASSGN READ LBRA RBRA
#line 562 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < read_ptr > () = std::make_unique<ReadNode>();
            yylhs.value.as < read_ptr > ()->name = std::move(yystack_[6].value.as < std::string > ());
            yylhs.value.as < read_ptr > ()->type = std::move(yystack_[4].value.as < type_ptr > ());

            yylhs.value.as < read_ptr > ()->location = floc_to_loc(yystack_[6].location);
        }
#line 2083 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 85: // assign_expr: LABEL TSEP LBRA opt_params RBRA PROD type LBRA program RBRA
#line 573 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<FuncDecl>();
            temp->name = std::move(yystack_[9].value.as < std::string > ());
            temp->params = std::move(yystack_[6].value.as < std::vector<Param> > ());
            temp->ret = std::move(yystack_[3].value.as < type_ptr > ());
            temp->body = std::move(yystack_[1].value.as < prog_ptr > ());
            yylhs.value.as < decl_ptr > () = std::move(temp);

            yylhs.value.as < decl_ptr > ()->location = floc_to_loc(yystack_[9].location);
        }
#line 2098 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 86: // assign_expr: LABEL TSEP non_function_type ASSGN value_expr
#line 584 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<VarDecl>();
            temp->name = std::move(yystack_[4].value.as < std::string > ());
            temp->type = std::move(yystack_[2].value.as < type_ptr > ());
            temp->r_val = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < decl_ptr > () = std::move(temp);
            yylhs.value.as < decl_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2111 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 87: // int_lit: INT
#line 596 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<IntLit>();
            temp->value = yystack_[0].value.as < uint64_t > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2123 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 88: // float_lit: FLOAT
#line 606 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<IntLit>();
            temp->value = yystack_[0].value.as < double > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2135 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 89: // bool_lit: TRUE
#line 616 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<BoolLit>();
            temp->value = true;
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2147 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 90: // bool_lit: FALSE
#line 624 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<BoolLit>();
            temp->value = false;
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2159 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 91: // char_lit: CHAR
#line 635 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<CharLit>();
            temp->value = yystack_[0].value.as < char > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2171 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 92: // bool_op: BOR
#line 644 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::BOR; }
#line 2177 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 93: // bool_op: BAND
#line 645 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::BAND; }
#line 2183 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 94: // comp_op: CEQ
#line 649 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CEQ; }
#line 2189 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 95: // comp_op: CNEQ
#line 650 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CNEQ; }
#line 2195 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 96: // comp_op: CGT
#line 651 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CGT; }
#line 2201 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 97: // comp_op: CLT
#line 652 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CLT; }
#line 2207 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 98: // comp_op: CGEQ
#line 653 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CGEQ; }
#line 2213 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 99: // comp_op: CLEQ
#line 654 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CLEQ; }
#line 2219 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 100: // bitwise_op: LAND
#line 658 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::LAND; }
#line 2225 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 101: // bitwise_op: BAR
#line 659 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LOR; }
#line 2231 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 102: // bitwise_op: LXOR
#line 660 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::LXOR; }
#line 2237 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 103: // shift_op: LSL
#line 663 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LSL; }
#line 2243 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 104: // shift_op: LSR
#line 664 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LSR; }
#line 2249 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 105: // additive_op: ADD
#line 667 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::ADD; }
#line 2255 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 106: // additive_op: SUB
#line 668 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::SUB; }
#line 2261 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 107: // additive_op: CONCAT
#line 669 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < BinaryOp > () = BinaryOp::CONCAT; }
#line 2267 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 108: // mult_op: MUL
#line 673 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::MUL; }
#line 2273 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 109: // mult_op: DIV
#line 674 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::DIV; }
#line 2279 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 110: // mult_op: MOD
#line 675 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::MOD; }
#line 2285 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 111: // mult_op: FLR
#line 676 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::FLR; }
#line 2291 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 112: // unary_op: BNOT
#line 680 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < UnaryOp > () = UnaryOp::BNOT; }
#line 2297 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 113: // unary_op: LNEG
#line 681 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < UnaryOp > () = UnaryOp::LNEG; }
#line 2303 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 114: // unary_op: SUB
#line 682 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < UnaryOp > () = UnaryOp::MINUS; }
#line 2309 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 115: // nominal_expr: LABEL
#line 687 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<NominalNode>();
            temp->label = std::move(yystack_[0].value.as < std::string > ()); 
            yylhs.value.as < expr_ptr > () = std::move(temp);
            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2320 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 116: // list_expr: empty_list
#line 695 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < list_ptr > ()); }
#line 2326 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 117: // list_expr: list_con
#line 696 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < list_ptr > ()); }
#line 2332 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 118: // list_expr: string_expr
#line 697 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                  { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2338 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 119: // empty_list: SQ_LBRA SQ_RBRA
#line 702 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < list_ptr > () = std::make_unique<ListNode>(); 
            yylhs.value.as < list_ptr > ()->elems = std::vector<expr_ptr>{}; 
            yylhs.value.as < list_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2348 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 120: // list_con: SQ_LBRA expr_list SQ_RBRA
#line 711 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < list_ptr > () = std::make_unique<ListNode>(); 
            yylhs.value.as < list_ptr > ()->elems = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ()); 
            yylhs.value.as < list_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 2358 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 121: // expr_list: value_expr
#line 720 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>{};
            yylhs.value.as < std::vector<expr_ptr> > ().push_back(std::move(yystack_[0].value.as < expr_ptr > ())); 
        }
#line 2367 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 122: // expr_list: expr_list COMMA value_expr
#line 725 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<expr_ptr> > ().push_back(std::move(yystack_[0].value.as < expr_ptr > ()));
            yylhs.value.as < std::vector<expr_ptr> > () = std::move(yystack_[2].value.as < std::vector<expr_ptr> > ());
        }
#line 2376 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 123: // call_expr: LABEL LBRA RBRA
#line 733 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<CallNode>();
            temp->label = std::move(yystack_[2].value.as < std::string > ());
            temp->params = std::vector<expr_ptr>{};
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 2389 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 124: // call_expr: LABEL LBRA expr_list RBRA
#line 742 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<CallNode>(); 
            temp->label = std::move(yystack_[3].value.as < std::string > ());
            temp->params = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 2402 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 125: // struct_expr: LABEL C_LBRA expr_list C_RBRA
#line 754 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<StructNode>();
            temp->name = std::move(yystack_[3].value.as < std::string > ());
            temp->fields = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 2415 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 126: // value_expr: bool_expr
#line 764 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2421 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 127: // bool_expr: comp_expr
#line 767 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2427 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 128: // bool_expr: bool_expr bool_op comp_expr
#line 769 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2441 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 129: // comp_expr: bitwise_expr
#line 781 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2447 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 130: // comp_expr: bitwise_expr comp_op bitwise_expr
#line 783 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2461 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 131: // bitwise_expr: shift_expr
#line 795 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2467 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 132: // bitwise_expr: bitwise_expr bitwise_op shift_expr
#line 797 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2481 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 133: // shift_expr: additive_expr
#line 809 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                    { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2487 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 134: // shift_expr: shift_expr shift_op additive_expr
#line 811 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2501 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 135: // additive_expr: mult_expr
#line 823 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2507 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 136: // additive_expr: additive_expr additive_op mult_expr
#line 825 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2521 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 137: // mult_expr: pow_expr
#line 837 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2527 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 138: // mult_expr: mult_expr mult_op pow_expr
#line 839 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2541 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 139: // pow_expr: unary_expr
#line 851 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2547 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 140: // pow_expr: unary_expr POW pow_expr
#line 853 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = BinaryOp::POW;
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2561 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 141: // unary_expr: postfix_expr
#line 865 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2567 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 142: // unary_expr: unary_op postfix_expr
#line 867 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<UnaryNode>();
            temp->op = yystack_[1].value.as < UnaryOp > ();
            temp->exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2580 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 143: // postfix_expr: literal_expr
#line 878 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2586 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 144: // postfix_expr: postfix_expr SQ_LBRA value_expr SQ_RBRA
#line 880 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = BinaryOp::INDEX;
            temp->l_exp = std::move(yystack_[3].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[1].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 2600 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 145: // postfix_expr: postfix_expr DOT LABEL
#line 890 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<AccessNode>();
            temp->field = std::move(yystack_[0].value.as < std::string > ());
            temp->struct_expr = std::move(yystack_[2].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2613 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 146: // literal_expr: int_lit
#line 901 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2619 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 147: // literal_expr: float_lit
#line 902 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2625 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 148: // literal_expr: char_lit
#line 903 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2631 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 149: // literal_expr: bool_lit
#line 904 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2637 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 150: // literal_expr: list_expr
#line 905 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2643 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 151: // literal_expr: nominal_expr
#line 906 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2649 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 152: // literal_expr: call_expr
#line 907 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2655 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 153: // literal_expr: struct_expr
#line 908 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                  { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2661 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 154: // literal_expr: LBRA value_expr RBRA
#line 909 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                           { yylhs.value.as < expr_ptr > () = std::move(yystack_[1].value.as < expr_ptr > ()); }
#line 2667 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;


#line 2671 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"

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









  const short parser::yypact_ninf_ = -171;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
    -171,    83,   142,  -171,  -171,    -6,    -4,    92,  -171,  -171,
    -171,  -171,    77,    91,    98,   105,   130,   140,   113,   126,
     124,  -171,   127,    -5,  -171,  -171,  -171,     1,   144,   151,
     105,   144,  -171,   130,  -171,   140,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,   144,   144,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,   144,  -171,  -171,  -171,  -171,   175,   139,
    -171,   174,  -171,   143,   144,  -171,  -171,   141,   144,  -171,
     170,   200,   104,   181,   104,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,   153,   176,  -171,  -171,  -171,  -171,
      55,  -171,  -171,   104,     3,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,   112,  -171,  -171,  -171,  -171,  -171,  -171,
     202,   -17,  -171,   137,    10,    39,   152,  -171,   166,    28,
    -171,   104,  -171,   105,   177,   165,    11,   104,   185,  -171,
      35,  -171,    28,   179,  -171,  -171,   104,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,  -171,   104,   104,  -171,  -171,
     104,  -171,  -171,  -171,   104,  -171,  -171,  -171,  -171,   104,
     104,   104,   211,   189,   190,    43,    72,    97,  -171,  -171,
      52,    63,  -171,  -171,   104,   121,  -171,     7,    10,    39,
     152,  -171,  -171,   191,  -171,  -171,   156,   193,  -171,   160,
     161,   165,  -171,  -171,  -171,  -171,   128,  -171,  -171,   194,
     163,  -171,  -171,   164,  -171,  -171,  -171,   192,  -171,  -171,
    -171,  -171,  -171,  -171,   144,   197,  -171,  -171,  -171,    19,
     223,  -171,   121,  -171,  -171,   224,   203,  -171,  -171,  -171,
    -171,  -171,   110,  -171,  -171,  -171,  -171,  -171,  -171,    20,
     204,  -171,  -171,  -171
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
      10,     0,    78,     0,     0,    25,    33,     0,     0,    11,
       0,     0,     0,     0,     0,    42,    44,    45,    43,    79,
      81,    82,    80,    26,     0,     0,    87,    88,    91,    68,
     115,    89,    90,     0,     0,   114,   113,   112,   118,   146,
     147,   149,   148,     0,   151,   150,   116,   117,   152,   153,
       0,   126,   127,   129,   131,   133,   135,   137,   139,   141,
     143,     0,    77,    28,     0,     0,     0,     0,     0,   119,
       0,   121,   142,     0,    93,    92,     0,   100,   101,   102,
      96,    97,    98,    99,    94,    95,     0,     0,   103,   104,
       0,   105,   106,   107,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    47,   123,
       0,     0,   154,   120,     0,     0,   128,   130,   132,   134,
     136,   138,   140,     0,   145,    83,     0,     0,    86,     0,
       0,     0,    46,   124,   125,   122,    66,    64,    65,     0,
       0,    52,    61,     0,    59,    60,    62,    69,    63,    56,
      57,    58,    55,   144,     0,     0,    78,    78,    48,     0,
       0,    67,     0,    51,    78,     0,     0,    84,    50,    49,
      73,    74,     0,    70,    53,    54,    71,    78,    72,     0,
       0,    75,    76,    85
  };

  const short
  parser::yypgoto_[] =
  {
    -171,  -171,  -171,  -171,  -171,  -171,   149,   -31,  -171,  -171,
    -171,  -171,  -171,  -171,   114,  -171,   205,  -171,  -171,   206,
    -171,   201,  -171,  -171,  -124,  -171,  -171,  -171,    47,  -171,
    -171,    18,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,  -171,  -171,  -170,  -164,  -156,
    -151,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,    74,  -171,  -171,   -70,  -171,   106,    95,    96,
      94,    93,    44,  -171,   145,  -171
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     1,     2,     8,    58,    59,    45,    46,    47,    48,
      49,    50,    51,    52,    19,    20,    21,     9,    23,    24,
      10,    26,    27,    11,    66,    75,    76,   167,   168,    77,
     200,   201,   202,   203,   204,   205,    98,   206,   207,   208,
     232,    78,    67,    79,    80,    81,    82,    99,   100,   101,
     102,   136,   146,   147,   150,   154,   159,   103,   104,   105,
     106,   107,   130,   108,   109,   131,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120
  };

  const unsigned char
  parser::yytable_[] =
  {
      55,    12,   110,    13,   122,   209,    86,    87,    88,    89,
      90,   210,    60,    61,    86,    87,    88,    89,    90,   211,
      91,    92,    62,   128,   212,    32,   230,   241,    91,    92,
      33,    34,    93,    69,    94,   129,    35,    83,   231,   242,
      93,   169,    94,   134,   135,    95,    86,    87,    88,    89,
      90,   163,   209,    95,    96,   137,   138,   139,   210,   161,
      91,    92,    96,   187,   162,    97,   211,   173,   148,   149,
     174,   212,    93,    97,    94,    86,    87,    88,    89,    90,
     151,   152,   193,     3,   126,    95,   189,   174,   127,    91,
      92,   183,   228,   229,    96,   188,   190,   194,   174,    14,
     235,    93,   153,    94,   195,    97,    15,    86,    87,    88,
      89,    90,    18,   240,    95,    86,    87,    88,    89,    90,
      16,    91,    92,    96,    86,    87,    88,    17,   196,    91,
      92,   197,   191,    93,    97,    94,   192,    22,    91,    92,
     198,    93,     4,    94,   238,   239,    95,    25,    70,    71,
      28,    36,   199,     5,    72,    96,    29,     6,     7,    30,
      36,   219,    73,    74,    31,   220,    97,    37,    38,    39,
      40,    41,    42,    43,    64,    44,    37,    38,    39,    40,
      41,    42,   123,   226,    44,   137,   138,   139,    53,   140,
     141,   142,   143,   144,   145,   155,   156,   157,   222,   158,
     170,   171,   223,   181,   182,    63,    65,    84,    68,    85,
     121,   133,   160,   125,   166,   172,   175,   165,   184,   185,
     186,   214,   215,   213,   216,   217,   221,   227,   224,   225,
     233,   236,   237,   124,   243,    54,    57,   164,   218,    56,
     234,   177,   176,   178,   179,     0,     0,   180,   132
  };

  const short
  parser::yycheck_[] =
  {
      31,     7,    72,     7,    74,   175,     3,     4,     5,     6,
       7,   175,    43,    44,     3,     4,     5,     6,     7,   175,
      17,    18,    53,    93,   175,    30,     7,     7,    17,    18,
      35,    30,    29,    64,    31,    32,    35,    68,    19,    19,
      29,    30,    31,    60,    61,    42,     3,     4,     5,     6,
       7,   121,   222,    42,    51,    48,    49,    50,   222,    31,
      17,    18,    51,    20,    36,    62,   222,    32,    58,    59,
      35,   222,    29,    62,    31,     3,     4,     5,     6,     7,
      41,    42,    30,     0,    29,    42,    14,    35,    33,    17,
      18,   161,   216,   217,    51,   165,   166,    34,    35,     7,
     224,    29,    63,    31,   174,    62,    29,     3,     4,     5,
       6,     7,     7,   237,    42,     3,     4,     5,     6,     7,
      29,    17,    18,    51,     3,     4,     5,    29,     7,    17,
      18,    10,    35,    29,    62,    31,    39,     7,    17,    18,
      19,    29,     0,    31,    34,    35,    42,     7,     7,     8,
      37,     7,    31,    11,    13,    51,    30,    15,    16,    35,
       7,    33,    21,    22,    37,    37,    62,    23,    24,    25,
      26,    27,    28,    29,    35,    31,    23,    24,    25,    26,
      27,    28,    29,   214,    31,    48,    49,    50,    37,    52,
      53,    54,    55,    56,    57,    43,    44,    45,    35,    47,
     126,   127,    39,   159,   160,    30,    32,    37,    65,     9,
      29,     9,    46,    37,    49,    30,    37,    40,     7,    30,
      30,    65,    29,    32,    64,    64,    32,    30,    64,    37,
       7,     7,    29,    84,    30,    30,    35,   123,   191,    33,
     222,   146,   136,   147,   150,    -1,    -1,   154,   103
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
      73,    73,    73,    30,    35,    32,    90,   108,    65,    73,
       7,     8,    13,    21,    22,    91,    92,    95,   107,   109,
     110,   111,   112,    73,    37,     9,     3,     4,     5,     6,
       7,    17,    18,    29,    31,    42,    51,    62,   102,   113,
     114,   115,   116,   123,   124,   125,   126,   127,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,    29,   131,    29,    72,    37,    29,    33,   131,    32,
     128,   131,   140,     9,    60,    61,   117,    48,    49,    50,
      52,    53,    54,    55,    56,    57,   118,   119,    58,    59,
     120,    41,    42,    63,   121,    43,    44,    45,    47,   122,
      46,    31,    36,   131,    80,    40,    49,    93,    94,    30,
     128,   128,    30,    32,    35,    37,   133,   134,   135,   136,
     137,   138,   138,   131,     7,    30,    30,    20,   131,    14,
     131,    35,    39,    30,    34,   131,     7,    10,    19,    31,
      96,    97,    98,    99,   100,   101,   103,   104,   105,   113,
     114,   115,   116,    32,    65,    29,    64,    64,    94,    33,
      37,    32,    35,    39,    64,    37,    73,    30,    90,    90,
       7,    19,   106,     7,    97,    90,     7,    29,    34,    35,
      90,     7,    19,    30
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
      98,    99,    99,    99,    99,    99,   100,   101,   102,   103,
     104,   104,   105,   106,   106,   106,   106,   107,   108,   108,
     109,   109,   109,   110,   111,   112,   112,   113,   114,   115,
     115,   116,   117,   117,   118,   118,   118,   118,   118,   118,
     119,   119,   119,   120,   120,   121,   121,   121,   122,   122,
     122,   122,   123,   123,   123,   124,   125,   125,   125,   126,
     127,   128,   128,   129,   129,   130,   131,   132,   132,   133,
     133,   134,   134,   135,   135,   136,   136,   137,   137,   138,
     138,   139,   139,   140,   140,   140,   141,   141,   141,   141,
     141,   141,   141,   141,   141
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
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       3,     3,     4,     1,     1,     3,     3,     2,     0,     2,
       1,     1,     1,     4,     7,    10,     5,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     1,     3,     3,     4,     4,     1,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     2,     1,     4,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     3
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
  "pattern", "enum_lit", "list_pattern", "string_expr",
  "list_size_pattern", "list_vars", "struct_size_pattern", "struct_vars",
  "return_expr", "helpers", "helper_expr", "print_expr", "read_expr",
  "assign_expr", "int_lit", "float_lit", "bool_lit", "char_lit", "bool_op",
  "comp_op", "bitwise_op", "shift_op", "additive_op", "mult_op",
  "unary_op", "nominal_expr", "list_expr", "empty_list", "list_con",
  "expr_list", "call_expr", "struct_expr", "value_expr", "bool_expr",
  "comp_expr", "bitwise_expr", "shift_expr", "additive_expr", "mult_expr",
  "pow_expr", "unary_expr", "postfix_expr", "literal_expr", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   185,   185,   194,   196,   204,   205,   206,   209,   210,
     213,   214,   220,   221,   222,   226,   227,   231,   232,   233,
     234,   238,   239,   242,   243,   246,   249,   252,   255,   256,
     259,   260,   267,   277,   290,   292,   300,   310,   321,   324,
     325,   333,   344,   353,   354,   355,   359,   369,   374,   382,
     390,   406,   417,   422,   430,   441,   442,   443,   444,   445,
     446,   450,   451,   452,   453,   454,   458,   468,   477,   481,
     492,   498,   506,   518,   519,   520,   521,   525,   536,   537,
     545,   546,   547,   551,   561,   572,   583,   595,   605,   615,
     623,   634,   644,   645,   649,   650,   651,   652,   653,   654,
     658,   659,   660,   663,   664,   667,   668,   669,   673,   674,
     675,   676,   680,   681,   682,   686,   695,   696,   697,   701,
     710,   719,   724,   732,   741,   753,   764,   767,   768,   781,
     782,   795,   796,   809,   810,   823,   824,   837,   838,   851,
     852,   865,   866,   878,   879,   889,   901,   902,   903,   904,
     905,   906,   907,   908,   909
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


#line 39 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
} // yy
#line 3172 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"

