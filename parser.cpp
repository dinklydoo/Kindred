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
      case symbol_kind::S_size_pattern: // size_pattern
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
      case symbol_kind::S_size_pattern: // size_pattern
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
      case symbol_kind::S_size_pattern: // size_pattern
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
      case symbol_kind::S_size_pattern: // size_pattern
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
      case symbol_kind::S_size_pattern: // size_pattern
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
#line 187 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < module_ptr > () = std::make_unique<ModuleNode>();
            yylhs.value.as < module_ptr > ()->decl = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
            module_node = std::move(yylhs.value.as < module_ptr > ());
        }
#line 1450 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 3: // definitions: %empty
#line 196 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { yylhs.value.as < std::vector<decl_ptr> > () = std::vector<decl_ptr>{}; }
#line 1456 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 4: // definitions: definitions definition
#line 198 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yystack_[1].value.as < std::vector<decl_ptr> > ().push_back(std::move(yystack_[0].value.as < decl_ptr > ()));
            yylhs.value.as < std::vector<decl_ptr> > () = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
        }
#line 1465 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 5: // definition: function_def
#line 205 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                  { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < func_decl_ptr > ()); }
#line 1471 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 6: // definition: struct_def
#line 206 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < struct_decl_ptr > ()); }
#line 1477 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 7: // definition: enum_def
#line 207 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < enum_decl_ptr > ()); }
#line 1483 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 8: // opt_types: %empty
#line 210 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < std::vector<type_ptr> > () = std::vector<type_ptr>{}; }
#line 1489 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 9: // opt_types: types
#line 211 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
            { yylhs.value.as < std::vector<type_ptr> > () = std::move(yystack_[0].value.as < std::vector<type_ptr> > ()); }
#line 1495 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 10: // types: type
#line 214 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < std::vector<type_ptr> > () = std::vector<type_ptr>{yystack_[0].value.as < type_ptr > ()}; }
#line 1501 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 11: // types: types COMMA type
#line 215 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                       {
        yystack_[2].value.as < std::vector<type_ptr> > ().push_back(std::move(yystack_[0].value.as < type_ptr > ()));
        yylhs.value.as < std::vector<type_ptr> > () = std::move(yystack_[2].value.as < std::vector<type_ptr> > ());
    }
#line 1510 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 12: // non_function_type: literal_type
#line 221 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1516 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 13: // non_function_type: list_type
#line 222 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1522 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 14: // non_function_type: nominal_type
#line 223 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1528 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 15: // type: non_function_type
#line 227 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                        { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1534 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 16: // type: func_type
#line 228 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1540 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 17: // literal_type: T_CHAR
#line 232 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.char_type(); }
#line 1546 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 18: // literal_type: T_BOOL
#line 233 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.bool_type(); }
#line 1552 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 19: // literal_type: int_lit_type
#line 234 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1558 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 20: // literal_type: float_lit_type
#line 235 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                     { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1564 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 21: // int_lit_type: T_INT
#line 239 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
            { yylhs.value.as < type_ptr > () = type_s.int_type(); }
#line 1570 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 22: // int_lit_type: T_LONG
#line 240 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.long_type(); }
#line 1576 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 23: // float_lit_type: T_FLOAT
#line 243 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < type_ptr > () = type_s.float_type(); }
#line 1582 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 24: // float_lit_type: T_DOUBLE
#line 244 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < type_ptr > () = type_s.double_type(); }
#line 1588 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 25: // list_type: SQ_LBRA type SQ_RBRA
#line 247 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                           { yylhs.value.as < type_ptr > () = type_s.list_type(yystack_[1].value.as < type_ptr > ()); }
#line 1594 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 26: // func_type: LBRA opt_types RBRA PROD type
#line 250 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                                    { yylhs.value.as < type_ptr > () = type_s.func_type(yystack_[3].value.as < std::vector<type_ptr> > (), yystack_[0].value.as < type_ptr > ()); }
#line 1600 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 27: // nominal_type: LABEL
#line 253 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
            { yylhs.value.as < type_ptr > () = type_s.nominal_type(yystack_[0].value.as < std::string > ()); }
#line 1606 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 28: // opt_params: %empty
#line 256 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < std::vector<Param> > () = std::vector<Param>{}; }
#line 1612 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 29: // opt_params: params
#line 257 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < std::vector<Param> > () = std::move(yystack_[0].value.as < std::vector<Param> > ()); }
#line 1618 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 30: // params: param
#line 260 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
            { yylhs.value.as < std::vector<Param> > () = std::vector<Param>{yystack_[0].value.as < Param > ()}; }
#line 1624 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 31: // params: params COMMA param
#line 262 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<Param> > ().push_back(std::move(yystack_[0].value.as < Param > ()));
            yylhs.value.as < std::vector<Param> > () = std::move(yystack_[2].value.as < std::vector<Param> > ());
        }
#line 1633 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 32: // param: LABEL TSEP type
#line 269 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < Param > () = Param(); 
            yylhs.value.as < Param > ().name = std::move(yystack_[2].value.as < std::string > ());
            yylhs.value.as < Param > ().type = std::move(yystack_[0].value.as < type_ptr > ());
            yylhs.value.as < Param > ().location = floc_to_loc(yystack_[2].location);
        }
#line 1644 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 33: // function_def: FUNC LABEL LBRA opt_params RBRA TSEP type program
#line 279 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {   
            yylhs.value.as < func_decl_ptr > () = std::make_unique<FuncDecl>();
            yylhs.value.as < func_decl_ptr > ()->name = std::move(yystack_[6].value.as < std::string > ());
            yylhs.value.as < func_decl_ptr > ()->params = std::move(yystack_[4].value.as < std::vector<Param> > ());
            yylhs.value.as < func_decl_ptr > ()->ret = std::move(yystack_[1].value.as < type_ptr > ());
            yylhs.value.as < func_decl_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());

            yylhs.value.as < func_decl_ptr > ()->location = floc_to_loc(yystack_[7].location);
        }
#line 1658 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 34: // fields: field
#line 292 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {   yylhs.value.as < std::vector<Field> > () = std::vector<Field>{}; yylhs.value.as < std::vector<Field> > ().push_back(std::move(yystack_[0].value.as < Field > ())); }
#line 1664 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 35: // fields: fields COMMA field
#line 294 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yystack_[2].value.as < std::vector<Field> > ().push_back(std::move(yystack_[0].value.as < Field > ()));
            yylhs.value.as < std::vector<Field> > () = std::move(yystack_[2].value.as < std::vector<Field> > ());
        }
#line 1673 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 36: // field: LABEL TSEP type
#line 302 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < Field > () = Field();
            yylhs.value.as < Field > ().name = std::move(yystack_[2].value.as < std::string > ());
            yylhs.value.as < Field > ().type = std::move(yystack_[0].value.as < type_ptr > ());

            yylhs.value.as < Field > ().location = floc_to_loc(yystack_[2].location);
        }
#line 1685 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 37: // struct_def: STRUCT LABEL LBRA fields RBRA
#line 312 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < struct_decl_ptr > () = std::make_unique<StructDecl>();
            yylhs.value.as < struct_decl_ptr > ()->name = std::move(yystack_[3].value.as < std::string > ());
            yylhs.value.as < struct_decl_ptr > ()->fields = std::move(yystack_[1].value.as < std::vector<Field> > ());

            yylhs.value.as < struct_decl_ptr > ()->location = floc_to_loc(yystack_[4].location);
        }
#line 1697 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 38: // evar: LABEL
#line 322 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
            { yylhs.value.as < std::string > () = std::move(yystack_[0].value.as < std::string > ()); }
#line 1703 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 39: // evars: evar
#line 325 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{yystack_[0].value.as < std::string > ()}; }
#line 1709 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 40: // evars: evars COMMA evar
#line 327 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));
            yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ());
        }
#line 1718 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 41: // enum_def: ENUM LABEL LBRA evars RBRA
#line 335 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < enum_decl_ptr > () = std::make_unique<EnumDecl>(); 
            yylhs.value.as < enum_decl_ptr > ()->name = std::move(yystack_[3].value.as < std::string > ());
            yylhs.value.as < enum_decl_ptr > ()->evar = std::move(yystack_[1].value.as < std::vector<std::string> > ());

            yylhs.value.as < enum_decl_ptr > ()->location = floc_to_loc(yystack_[4].location);
        }
#line 1730 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 42: // program: helpers branch_expr
#line 346 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < prog_ptr > () = std::make_unique<ProgramNode>();
            yylhs.value.as < prog_ptr > ()->decl = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
            yylhs.value.as < prog_ptr > ()->body = std::move(yystack_[0].value.as < expr_ptr > ());
        }
#line 1740 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 43: // branch_expr: return_expr
#line 354 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                  { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 1746 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 44: // branch_expr: guard_expr
#line 355 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < guard_ptr > ()); }
#line 1752 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 45: // branch_expr: case_expr
#line 356 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < case_ptr > ()); }
#line 1758 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 46: // guard_expr: CASE OF TSEP guards PEND
#line 361 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < guard_ptr > () = std::make_unique<GuardNode>();
            yylhs.value.as < guard_ptr > ()->branches = std::move(yystack_[1].value.as < std::vector<g_branch_ptr> > ());

            yylhs.value.as < guard_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 1769 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 47: // guards: guard
#line 371 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < std::vector<g_branch_ptr> > () = std::vector<g_branch_ptr>{}; 
            yylhs.value.as < std::vector<g_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < g_branch_ptr > ()));
        }
#line 1778 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 48: // guards: guards COMMA guard
#line 376 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<g_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < g_branch_ptr > ()));
            yylhs.value.as < std::vector<g_branch_ptr> > () = std::move(yystack_[2].value.as < std::vector<g_branch_ptr> > ());
        }
#line 1787 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 49: // guard: BAR value_expr ARROW program
#line 384 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < g_branch_ptr > () = std::make_unique<GuardBranchNode>();
            yylhs.value.as < g_branch_ptr > ()->match = std::move(yystack_[2].value.as < expr_ptr > ());
            yylhs.value.as < g_branch_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());

            yylhs.value.as < g_branch_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 1799 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 50: // guard: BAR ELSE ARROW program
#line 392 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
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
#line 1816 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 51: // case_expr: MARK value_expr OF TSEP patterns PEND
#line 408 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < case_ptr > () = std::make_unique<CaseNode>();
            yylhs.value.as < case_ptr > ()->target = std::move(yystack_[4].value.as < expr_ptr > ());
            yylhs.value.as < case_ptr > ()->patterns = std::move(yystack_[1].value.as < std::vector<c_branch_ptr> > ());

            yylhs.value.as < case_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 1828 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 52: // patterns: pattern_branch
#line 419 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < std::vector<c_branch_ptr> > () = std::vector<c_branch_ptr>{}; 
            yylhs.value.as < std::vector<c_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < c_branch_ptr > ())); 
        }
#line 1837 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 53: // patterns: patterns COMMA pattern_branch
#line 424 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<c_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < c_branch_ptr > ()));
            yylhs.value.as < std::vector<c_branch_ptr> > () = std::move(yystack_[2].value.as < std::vector<c_branch_ptr> > ());
        }
#line 1846 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 54: // pattern_branch: pattern ARROW program
#line 432 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < c_branch_ptr > () = std::make_unique<CaseBranchNode>();
            yylhs.value.as < c_branch_ptr > ()->pattern = std::move(yystack_[2].value.as < literal_ptr > ());
            yylhs.value.as < c_branch_ptr > ()->pattern_type = false;
            yylhs.value.as < c_branch_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());

            yylhs.value.as < c_branch_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 1859 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 55: // pattern_branch: size_pattern ARROW program
#line 441 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < c_branch_ptr > () = std::make_unique<CaseBranchNode>();
            yylhs.value.as < c_branch_ptr > ()->pattern = std::move(yystack_[2].value.as < literal_ptr > ());
            yylhs.value.as < c_branch_ptr > ()->pattern_type = true;
            yylhs.value.as < c_branch_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());

            yylhs.value.as < c_branch_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 1872 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 56: // literal: char_lit
#line 452 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1878 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 57: // literal: int_lit
#line 453 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1884 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 58: // literal: float_lit
#line 454 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1890 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 59: // literal: bool_lit
#line 455 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1896 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 60: // literal: enum_lit
#line 456 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1902 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 61: // literal: list_pattern
#line 457 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1908 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 62: // size_pattern: list_size_pattern
#line 461 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                        { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1914 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 63: // size_pattern: struct_size_pattern
#line 462 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                          { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1920 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 64: // pattern: literal
#line 465 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1926 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 65: // pattern: DEFAULT
#line 466 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::make_unique<DefaultLit>(); yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);}
#line 1932 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 66: // pattern: NIL
#line 467 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < literal_ptr > () = std::make_unique<NilLit>(); yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);}
#line 1938 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 67: // enum_lit: LABEL
#line 472 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<EnumLit>();
            temp->elem = std::move(yystack_[0].value.as < std::string > ()); 
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 1950 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 68: // list_pattern: SQ_LBRA SQ_RBRA
#line 482 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < literal_ptr > () = std::make_unique<EmptyLit>();

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 1960 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 69: // string_expr: STRING
#line 490 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             {yylhs.value.as < expr_ptr > () = str_to_chlist(yystack_[0].value.as < std::string > ()); yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[0].location); }
#line 1966 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 70: // list_size_pattern: list_vars
#line 495 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<ListPatternLit>(); 
            temp->patterns = std::move(yystack_[0].value.as < std::vector<std::string> > ());
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 1978 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 71: // list_vars: LABEL TSEP LABEL
#line 506 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{};
            yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[2].value.as < std::string > ()));
            yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ())); 
        }
#line 1988 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 72: // list_vars: list_vars TSEP LABEL
#line 512 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));
            yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ());
        }
#line 1997 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 73: // struct_size_pattern: LABEL C_LBRA struct_vars C_RBRA
#line 520 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<StructPatternLit>();
            temp->name = std::move(yystack_[3].value.as < std::string > ());
            temp->patterns = std::move(yystack_[1].value.as < std::vector<std::string> > ());
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 2010 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 74: // struct_vars: LABEL
#line 531 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{}; yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));}
#line 2016 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 75: // struct_vars: NIL
#line 532 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
         { yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{}; yylhs.value.as < std::vector<std::string> > ().push_back("");}
#line 2022 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 76: // struct_vars: struct_vars COMMA LABEL
#line 533 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                              { yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ())); yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ()); }
#line 2028 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 77: // struct_vars: struct_vars COMMA NIL
#line 534 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                            { yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move("")); yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ()); }
#line 2034 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 78: // return_expr: RETURN value_expr
#line 539 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<ReturnNode>();
            temp->rexp = std::move(yystack_[0].value.as < expr_ptr > ()); 
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2046 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 79: // helpers: %empty
#line 549 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < std::vector<decl_ptr> > () = std::vector<decl_ptr>{}; }
#line 2052 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 80: // helpers: helpers helper_expr
#line 551 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[1].value.as < std::vector<decl_ptr> > ().push_back(std::move(yystack_[0].value.as < decl_ptr > ()));
            yylhs.value.as < std::vector<decl_ptr> > () = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
        }
#line 2061 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 81: // helper_expr: assign_expr
#line 558 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                  { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < decl_ptr > ()); }
#line 2067 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 82: // helper_expr: print_expr
#line 559 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < print_ptr > ()); }
#line 2073 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 83: // helper_expr: read_expr
#line 560 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < read_ptr > ()); }
#line 2079 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 84: // print_expr: PRINT LBRA value_expr RBRA
#line 565 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < print_ptr > () = std::make_unique<PrintNode>();
            yylhs.value.as < print_ptr > ()->msg = std::move(yystack_[1].value.as < expr_ptr > ());

            yylhs.value.as < print_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 2090 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 85: // read_expr: LABEL TSEP non_function_type ASSGN READ LBRA RBRA
#line 575 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < read_ptr > () = std::make_unique<ReadNode>();
            yylhs.value.as < read_ptr > ()->name = std::move(yystack_[6].value.as < std::string > ());
            yylhs.value.as < read_ptr > ()->type = std::move(yystack_[4].value.as < type_ptr > ());

            yylhs.value.as < read_ptr > ()->location = floc_to_loc(yystack_[6].location);
        }
#line 2102 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 86: // assign_expr: LABEL TSEP LBRA opt_params RBRA PROD type LBRA program RBRA
#line 586 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<FuncDecl>();
            temp->name = std::move(yystack_[9].value.as < std::string > ());
            temp->params = std::move(yystack_[6].value.as < std::vector<Param> > ());
            temp->ret = std::move(yystack_[3].value.as < type_ptr > ());
            temp->body = std::move(yystack_[1].value.as < prog_ptr > ());
            yylhs.value.as < decl_ptr > () = std::move(temp);

            yylhs.value.as < decl_ptr > ()->location = floc_to_loc(yystack_[9].location);
        }
#line 2117 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 87: // assign_expr: LABEL TSEP non_function_type ASSGN value_expr
#line 597 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<VarDecl>();
            temp->name = std::move(yystack_[4].value.as < std::string > ());
            temp->type = std::move(yystack_[2].value.as < type_ptr > ());
            temp->r_val = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < decl_ptr > () = std::move(temp);
            yylhs.value.as < decl_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2130 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 88: // int_lit: INT
#line 609 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<IntLit>();
            temp->value = yystack_[0].value.as < uint64_t > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2142 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 89: // float_lit: FLOAT
#line 619 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<IntLit>();
            temp->value = yystack_[0].value.as < double > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2154 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 90: // bool_lit: TRUE
#line 629 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<BoolLit>();
            temp->value = true;
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2166 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 91: // bool_lit: FALSE
#line 637 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<BoolLit>();
            temp->value = false;
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2178 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 92: // char_lit: CHAR
#line 648 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<CharLit>();
            temp->value = yystack_[0].value.as < char > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2190 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 93: // bool_op: BOR
#line 657 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::BOR; }
#line 2196 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 94: // bool_op: BAND
#line 658 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::BAND; }
#line 2202 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 95: // comp_op: CEQ
#line 662 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CEQ; }
#line 2208 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 96: // comp_op: CNEQ
#line 663 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CNEQ; }
#line 2214 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 97: // comp_op: CGT
#line 664 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CGT; }
#line 2220 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 98: // comp_op: CLT
#line 665 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CLT; }
#line 2226 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 99: // comp_op: CGEQ
#line 666 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CGEQ; }
#line 2232 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 100: // comp_op: CLEQ
#line 667 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CLEQ; }
#line 2238 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 101: // bitwise_op: LAND
#line 671 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::LAND; }
#line 2244 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 102: // bitwise_op: BAR
#line 672 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LOR; }
#line 2250 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 103: // bitwise_op: LXOR
#line 673 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::LXOR; }
#line 2256 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 104: // shift_op: LSL
#line 676 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LSL; }
#line 2262 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 105: // shift_op: LSR
#line 677 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LSR; }
#line 2268 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 106: // additive_op: ADD
#line 680 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::ADD; }
#line 2274 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 107: // additive_op: SUB
#line 681 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::SUB; }
#line 2280 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 108: // additive_op: CONCAT
#line 682 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < BinaryOp > () = BinaryOp::CONCAT; }
#line 2286 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 109: // mult_op: MUL
#line 686 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::MUL; }
#line 2292 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 110: // mult_op: DIV
#line 687 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::DIV; }
#line 2298 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 111: // mult_op: MOD
#line 688 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::MOD; }
#line 2304 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 112: // mult_op: FLR
#line 689 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::FLR; }
#line 2310 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 113: // unary_op: BNOT
#line 693 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < UnaryOp > () = UnaryOp::BNOT; }
#line 2316 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 114: // unary_op: LNEG
#line 694 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < UnaryOp > () = UnaryOp::LNEG; }
#line 2322 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 115: // unary_op: SUB
#line 695 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < UnaryOp > () = UnaryOp::MINUS; }
#line 2328 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 116: // nominal_expr: LABEL
#line 700 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<NominalNode>();
            temp->label = std::move(yystack_[0].value.as < std::string > ()); 
            yylhs.value.as < expr_ptr > () = std::move(temp);
            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2339 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 117: // list_expr: empty_list
#line 708 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < list_ptr > ()); }
#line 2345 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 118: // list_expr: list_con
#line 709 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < list_ptr > ()); }
#line 2351 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 119: // list_expr: string_expr
#line 710 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                  { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2357 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 120: // empty_list: SQ_LBRA SQ_RBRA
#line 715 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < list_ptr > () = std::make_unique<ListNode>(); 
            yylhs.value.as < list_ptr > ()->elems = std::vector<expr_ptr>{}; 
            yylhs.value.as < list_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2367 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 121: // list_con: SQ_LBRA expr_list SQ_RBRA
#line 724 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < list_ptr > () = std::make_unique<ListNode>(); 
            yylhs.value.as < list_ptr > ()->elems = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ()); 
            yylhs.value.as < list_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 2377 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 122: // expr_list: value_expr
#line 733 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>{};
            yylhs.value.as < std::vector<expr_ptr> > ().push_back(std::move(yystack_[0].value.as < expr_ptr > ())); 
        }
#line 2386 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 123: // expr_list: expr_list COMMA value_expr
#line 738 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<expr_ptr> > ().push_back(std::move(yystack_[0].value.as < expr_ptr > ()));
            yylhs.value.as < std::vector<expr_ptr> > () = std::move(yystack_[2].value.as < std::vector<expr_ptr> > ());
        }
#line 2395 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 124: // call_expr: LABEL LBRA RBRA
#line 746 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<CallNode>();
            temp->label = std::move(yystack_[2].value.as < std::string > ());
            temp->params = std::vector<expr_ptr>{};
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 2408 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 125: // call_expr: LABEL LBRA expr_list RBRA
#line 755 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<CallNode>(); 
            temp->label = std::move(yystack_[3].value.as < std::string > ());
            temp->params = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 2421 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 126: // struct_expr: LABEL C_LBRA expr_list C_RBRA
#line 767 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<StructNode>();
            temp->name = std::move(yystack_[3].value.as < std::string > ());
            temp->fields = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 2434 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 127: // value_expr: bool_expr
#line 777 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2440 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 128: // bool_expr: comp_expr
#line 780 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2446 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 129: // bool_expr: bool_expr bool_op comp_expr
#line 782 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2460 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 130: // comp_expr: bitwise_expr
#line 794 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2466 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 131: // comp_expr: bitwise_expr comp_op bitwise_expr
#line 796 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2480 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 132: // bitwise_expr: shift_expr
#line 808 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2486 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 133: // bitwise_expr: bitwise_expr bitwise_op shift_expr
#line 810 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2500 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 134: // shift_expr: additive_expr
#line 822 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                    { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2506 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 135: // shift_expr: shift_expr shift_op additive_expr
#line 824 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2520 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 136: // additive_expr: mult_expr
#line 836 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2526 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 137: // additive_expr: additive_expr additive_op mult_expr
#line 838 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2540 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 138: // mult_expr: pow_expr
#line 850 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2546 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 139: // mult_expr: mult_expr mult_op pow_expr
#line 852 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2560 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 140: // pow_expr: unary_expr
#line 864 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2566 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 141: // pow_expr: unary_expr POW pow_expr
#line 866 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = BinaryOp::POW;
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2580 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 142: // unary_expr: postfix_expr
#line 878 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2586 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 143: // unary_expr: unary_op postfix_expr
#line 880 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<UnaryNode>();
            temp->op = yystack_[1].value.as < UnaryOp > ();
            temp->exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2599 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 144: // postfix_expr: literal_expr
#line 891 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2605 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 145: // postfix_expr: postfix_expr SQ_LBRA value_expr SQ_RBRA
#line 893 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = BinaryOp::INDEX;
            temp->l_exp = std::move(yystack_[3].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[1].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 2619 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 146: // postfix_expr: postfix_expr DOT LABEL
#line 903 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<AccessNode>();
            temp->field = std::move(yystack_[0].value.as < std::string > ());
            temp->struct_expr = std::move(yystack_[2].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2632 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 147: // literal_expr: int_lit
#line 914 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2638 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 148: // literal_expr: float_lit
#line 915 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2644 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 149: // literal_expr: char_lit
#line 916 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2650 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 150: // literal_expr: bool_lit
#line 917 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2656 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 151: // literal_expr: list_expr
#line 918 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2662 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 152: // literal_expr: nominal_expr
#line 919 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2668 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 153: // literal_expr: call_expr
#line 920 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2674 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 154: // literal_expr: struct_expr
#line 921 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                  { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2680 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 155: // literal_expr: LBRA value_expr RBRA
#line 922 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                           { yylhs.value.as < expr_ptr > () = std::move(yystack_[1].value.as < expr_ptr > ()); }
#line 2686 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;


#line 2690 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"

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









  const short parser::yypact_ninf_ = -165;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
    -165,    25,    55,  -165,  -165,    -4,    36,   120,  -165,  -165,
    -165,  -165,    91,   103,   118,   135,   143,   146,    31,   159,
     139,  -165,   167,    34,  -165,  -165,  -165,    53,   144,   168,
     135,   144,  -165,   143,  -165,   146,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,   144,   144,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,   144,  -165,  -165,  -165,  -165,   176,   172,
    -165,   177,  -165,   111,   144,  -165,  -165,   141,   144,  -165,
     171,   201,   104,   182,   104,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,   154,   175,  -165,  -165,  -165,  -165,
     -28,  -165,  -165,   104,     3,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,   112,  -165,  -165,  -165,  -165,  -165,  -165,
     204,    -3,  -165,   138,    41,   -11,   113,  -165,   169,    61,
    -165,   104,  -165,   135,   174,   170,    11,   104,   186,  -165,
      -8,  -165,    61,   180,  -165,  -165,   104,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,   104,   104,  -165,  -165,
     104,  -165,  -165,  -165,   104,  -165,  -165,  -165,  -165,   104,
     104,   104,   211,   190,   191,    43,    72,    67,  -165,  -165,
      63,    78,  -165,  -165,   104,   121,  -165,    32,    41,   -11,
     113,  -165,  -165,   192,  -165,  -165,   157,   194,  -165,   161,
     164,   170,  -165,  -165,  -165,  -165,   163,  -165,  -165,   195,
     162,  -165,  -165,   165,   166,  -165,  -165,  -165,   189,  -165,
    -165,  -165,  -165,  -165,  -165,   144,   202,  -165,  -165,  -165,
      19,   224,  -165,   121,  -165,  -165,  -165,   226,   205,  -165,
    -165,  -165,  -165,  -165,   130,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,    37,   206,  -165,  -165,  -165
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
      10,     0,    79,     0,     0,    25,    33,     0,     0,    11,
       0,     0,     0,     0,     0,    42,    44,    45,    43,    80,
      82,    83,    81,    26,     0,     0,    88,    89,    92,    69,
     116,    90,    91,     0,     0,   115,   114,   113,   119,   147,
     148,   150,   149,     0,   152,   151,   117,   118,   153,   154,
       0,   127,   128,   130,   132,   134,   136,   138,   140,   142,
     144,     0,    78,    28,     0,     0,     0,     0,     0,   120,
       0,   122,   143,     0,    94,    93,     0,   101,   102,   103,
      97,    98,    99,   100,    95,    96,     0,     0,   104,   105,
       0,   106,   107,   108,     0,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    47,   124,
       0,     0,   155,   121,     0,     0,   129,   131,   133,   135,
     137,   139,   141,     0,   146,    84,     0,     0,    87,     0,
       0,     0,    46,   125,   126,   123,    67,    65,    66,     0,
       0,    52,    64,     0,     0,    60,    61,    62,    70,    63,
      57,    58,    59,    56,   145,     0,     0,    79,    79,    48,
       0,     0,    68,     0,    51,    79,    79,     0,     0,    85,
      50,    49,    74,    75,     0,    71,    53,    55,    54,    72,
      79,    73,     0,     0,    76,    77,    86
  };

  const short
  parser::yypgoto_[] =
  {
    -165,  -165,  -165,  -165,  -165,  -165,   151,   -31,  -165,  -165,
    -165,  -165,  -165,  -165,   114,  -165,   208,  -165,  -165,   207,
    -165,   209,  -165,  -165,   -81,  -165,  -165,  -165,    48,  -165,
    -165,    18,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -164,  -156,
    -139,  -136,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,    76,  -165,  -165,   -70,  -165,   106,    97,
      98,    96,    93,    39,  -165,   145,  -165
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     1,     2,     8,    58,    59,    45,    46,    47,    48,
      49,    50,    51,    52,    19,    20,    21,     9,    23,    24,
      10,    26,    27,    11,    66,    75,    76,   167,   168,    77,
     200,   201,   202,   203,   204,   205,   206,    98,   207,   208,
     209,   234,    78,    67,    79,    80,    81,    82,    99,   100,
     101,   102,   136,   146,   147,   150,   154,   159,   103,   104,
     105,   106,   107,   130,   108,   109,   131,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120
  };

  const unsigned char
  parser::yytable_[] =
  {
      55,   126,   110,    12,   122,   127,    86,    87,    88,    89,
      90,   210,    60,    61,    86,    87,    88,    89,    90,   211,
      91,    92,    62,   128,   173,     3,   232,   174,    91,    92,
     151,   152,    93,    69,    94,   129,   212,    83,   233,   213,
      93,   169,    94,    13,   244,    95,    86,    87,    88,    89,
      90,   163,   153,    95,    96,     4,   245,   134,   135,   210,
      91,    92,    96,   187,    32,    97,     5,   211,    28,    33,
       6,     7,    93,    97,    94,    86,    87,    88,    89,    90,
     137,   138,   139,    34,   212,    95,   189,   213,    35,    91,
      92,   183,   161,   193,    96,   188,   190,   162,   174,   148,
     149,    93,   191,    94,   195,    97,   192,    86,    87,    88,
      89,    90,   194,   174,    95,    86,    87,    88,    89,    90,
      15,    91,    92,    96,    86,    87,    88,    14,   196,    91,
      92,   197,    16,    93,    97,    94,   230,   231,    91,    92,
     198,    93,    18,    94,   237,   238,    95,    17,    70,    71,
      22,    36,   199,    25,    72,    96,   155,   156,   157,   243,
     158,    36,    73,    74,   241,   242,    97,    37,    38,    39,
      40,    41,    42,    43,    30,    44,    68,    37,    38,    39,
      40,    41,    42,   123,   228,    44,   137,   138,   139,    29,
     140,   141,   142,   143,   144,   145,   220,   223,   181,   182,
     221,   224,   170,   171,    31,    53,    63,    64,    84,    65,
      85,   121,   125,   133,   165,   160,   172,   175,   184,   166,
     185,   186,   215,   216,   214,   217,   227,   222,   218,   225,
     226,   235,   229,   239,   240,   124,   246,   164,    54,   219,
      56,   236,   176,   177,    57,   178,   179,   180,   132
  };

  const unsigned char
  parser::yycheck_[] =
  {
      31,    29,    72,     7,    74,    33,     3,     4,     5,     6,
       7,   175,    43,    44,     3,     4,     5,     6,     7,   175,
      17,    18,    53,    93,    32,     0,     7,    35,    17,    18,
      41,    42,    29,    64,    31,    32,   175,    68,    19,   175,
      29,    30,    31,     7,     7,    42,     3,     4,     5,     6,
       7,   121,    63,    42,    51,     0,    19,    60,    61,   223,
      17,    18,    51,    20,    30,    62,    11,   223,    37,    35,
      15,    16,    29,    62,    31,     3,     4,     5,     6,     7,
      48,    49,    50,    30,   223,    42,    14,   223,    35,    17,
      18,   161,    31,    30,    51,   165,   166,    36,    35,    58,
      59,    29,    35,    31,   174,    62,    39,     3,     4,     5,
       6,     7,    34,    35,    42,     3,     4,     5,     6,     7,
      29,    17,    18,    51,     3,     4,     5,     7,     7,    17,
      18,    10,    29,    29,    62,    31,   217,   218,    17,    18,
      19,    29,     7,    31,   225,   226,    42,    29,     7,     8,
       7,     7,    31,     7,    13,    51,    43,    44,    45,   240,
      47,     7,    21,    22,    34,    35,    62,    23,    24,    25,
      26,    27,    28,    29,    35,    31,    65,    23,    24,    25,
      26,    27,    28,    29,   215,    31,    48,    49,    50,    30,
      52,    53,    54,    55,    56,    57,    33,    35,   159,   160,
      37,    39,   126,   127,    37,    37,    30,    35,    37,    32,
       9,    29,    37,     9,    40,    46,    30,    37,     7,    49,
      30,    30,    65,    29,    32,    64,    37,    32,    64,    64,
      64,     7,    30,     7,    29,    84,    30,   123,    30,   191,
      33,   223,   136,   146,    35,   147,   150,   154,   103
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
      73,    73,    73,    30,    35,    32,    90,   109,    65,    73,
       7,     8,    13,    21,    22,    91,    92,    95,   108,   110,
     111,   112,   113,    73,    37,     9,     3,     4,     5,     6,
       7,    17,    18,    29,    31,    42,    51,    62,   103,   114,
     115,   116,   117,   124,   125,   126,   127,   128,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,    29,   132,    29,    72,    37,    29,    33,   132,    32,
     129,   132,   141,     9,    60,    61,   118,    48,    49,    50,
      52,    53,    54,    55,    56,    57,   119,   120,    58,    59,
     121,    41,    42,    63,   122,    43,    44,    45,    47,   123,
      46,    31,    36,   132,    80,    40,    49,    93,    94,    30,
     129,   129,    30,    32,    35,    37,   134,   135,   136,   137,
     138,   139,   139,   132,     7,    30,    30,    20,   132,    14,
     132,    35,    39,    30,    34,   132,     7,    10,    19,    31,
      96,    97,    98,    99,   100,   101,   102,   104,   105,   106,
     114,   115,   116,   117,    32,    65,    29,    64,    64,    94,
      33,    37,    32,    35,    39,    64,    64,    37,    73,    30,
      90,    90,     7,    19,   107,     7,    97,    90,    90,     7,
      29,    34,    35,    90,     7,    19,    30
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    66,    67,    68,    68,    69,    69,    69,    70,    70,
      71,    71,    72,    72,    72,    73,    73,    74,    74,    74,
      74,    75,    75,    76,    76,    77,    78,    79,    80,    80,
      81,    81,    82,    83,    84,    84,    85,    86,    87,    88,
      88,    89,    90,    91,    91,    91,    92,    93,    93,    94,
      94,    95,    96,    96,    97,    97,    98,    98,    98,    98,
      98,    98,    99,    99,   100,   100,   100,   101,   102,   103,
     104,   105,   105,   106,   107,   107,   107,   107,   108,   109,
     109,   110,   110,   110,   111,   112,   113,   113,   114,   115,
     116,   116,   117,   118,   118,   119,   119,   119,   119,   119,
     119,   120,   120,   120,   121,   121,   122,   122,   122,   123,
     123,   123,   123,   124,   124,   124,   125,   126,   126,   126,
     127,   128,   129,   129,   130,   130,   131,   132,   133,   133,
     134,   134,   135,   135,   136,   136,   137,   137,   138,   138,
     139,   139,   140,   140,   141,   141,   141,   142,   142,   142,
     142,   142,   142,   142,   142,   142
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     2,     1,     1,     1,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     5,     1,     0,     1,
       1,     3,     3,     8,     1,     3,     3,     5,     1,     1,
       3,     5,     2,     1,     1,     1,     5,     1,     3,     4,
       4,     6,     1,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     3,     3,     4,     1,     1,     3,     3,     2,     0,
       2,     1,     1,     1,     4,     7,    10,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     1,     3,     3,     4,     4,     1,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     2,     1,     4,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3
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
  "size_pattern", "pattern", "enum_lit", "list_pattern", "string_expr",
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
       0,   186,   186,   195,   197,   205,   206,   207,   210,   211,
     214,   215,   221,   222,   223,   227,   228,   232,   233,   234,
     235,   239,   240,   243,   244,   247,   250,   253,   256,   257,
     260,   261,   268,   278,   291,   293,   301,   311,   322,   325,
     326,   334,   345,   354,   355,   356,   360,   370,   375,   383,
     391,   407,   418,   423,   431,   440,   452,   453,   454,   455,
     456,   457,   461,   462,   465,   466,   467,   471,   481,   490,
     494,   505,   511,   519,   531,   532,   533,   534,   538,   549,
     550,   558,   559,   560,   564,   574,   585,   596,   608,   618,
     628,   636,   647,   657,   658,   662,   663,   664,   665,   666,
     667,   671,   672,   673,   676,   677,   680,   681,   682,   686,
     687,   688,   689,   693,   694,   695,   699,   708,   709,   710,
     714,   723,   732,   737,   745,   754,   766,   777,   780,   781,
     794,   795,   808,   809,   822,   823,   836,   837,   850,   851,
     864,   865,   878,   879,   891,   892,   902,   914,   915,   916,
     917,   918,   919,   920,   921,   922
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
#line 3191 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"

