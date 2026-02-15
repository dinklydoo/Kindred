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
      case symbol_kind::S_assign_val_expr: // assign_val_expr
      case symbol_kind::S_nominal_expr: // nominal_expr
      case symbol_kind::S_list_expr: // list_expr
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
      case symbol_kind::S_assign_val_expr: // assign_val_expr
      case symbol_kind::S_nominal_expr: // nominal_expr
      case symbol_kind::S_list_expr: // list_expr
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
      case symbol_kind::S_assign_val_expr: // assign_val_expr
      case symbol_kind::S_nominal_expr: // nominal_expr
      case symbol_kind::S_list_expr: // list_expr
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
      case symbol_kind::S_assign_val_expr: // assign_val_expr
      case symbol_kind::S_nominal_expr: // nominal_expr
      case symbol_kind::S_list_expr: // list_expr
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
      case symbol_kind::S_assign_val_expr: // assign_val_expr
      case symbol_kind::S_nominal_expr: // nominal_expr
      case symbol_kind::S_list_expr: // list_expr
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
#line 1430 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 3: // definitions: %empty
#line 195 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { yylhs.value.as < std::vector<decl_ptr> > () = std::vector<decl_ptr>{}; }
#line 1436 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 4: // definitions: definitions definition
#line 197 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yystack_[1].value.as < std::vector<decl_ptr> > ().push_back(std::move(yystack_[0].value.as < decl_ptr > ()));
            yylhs.value.as < std::vector<decl_ptr> > () = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
        }
#line 1445 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 5: // definition: function_def
#line 204 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                  { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < func_decl_ptr > ()); }
#line 1451 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 6: // definition: struct_def
#line 205 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < struct_decl_ptr > ()); }
#line 1457 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 7: // definition: enum_def
#line 206 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < enum_decl_ptr > ()); }
#line 1463 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 8: // opt_types: %empty
#line 209 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < std::vector<type_ptr> > () = std::vector<type_ptr>{}; }
#line 1469 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 9: // opt_types: types
#line 210 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
            { yylhs.value.as < std::vector<type_ptr> > () = std::move(yystack_[0].value.as < std::vector<type_ptr> > ()); }
#line 1475 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 10: // types: type
#line 213 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < std::vector<type_ptr> > () = std::vector<type_ptr>{yystack_[0].value.as < type_ptr > ()}; }
#line 1481 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 11: // types: types COMMA type
#line 214 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                       {
        yystack_[2].value.as < std::vector<type_ptr> > ().push_back(std::move(yystack_[0].value.as < type_ptr > ()));
        yylhs.value.as < std::vector<type_ptr> > () = std::move(yystack_[2].value.as < std::vector<type_ptr> > ());
    }
#line 1490 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 12: // non_function_type: literal_type
#line 220 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1496 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 13: // non_function_type: list_type
#line 221 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1502 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 14: // non_function_type: nominal_type
#line 222 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1508 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 15: // type: non_function_type
#line 226 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                        { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1514 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 16: // type: func_type
#line 227 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1520 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 17: // literal_type: T_CHAR
#line 231 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.char_type(); }
#line 1526 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 18: // literal_type: T_BOOL
#line 232 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.bool_type(); }
#line 1532 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 19: // literal_type: int_lit_type
#line 233 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1538 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 20: // literal_type: float_lit_type
#line 234 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                     { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1544 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 21: // int_lit_type: T_INT
#line 238 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
            { yylhs.value.as < type_ptr > () = type_s.int_type(); }
#line 1550 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 22: // int_lit_type: T_LONG
#line 239 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.long_type(); }
#line 1556 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 23: // float_lit_type: T_FLOAT
#line 242 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < type_ptr > () = type_s.float_type(); }
#line 1562 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 24: // float_lit_type: T_DOUBLE
#line 243 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < type_ptr > () = type_s.double_type(); }
#line 1568 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 25: // list_type: SQ_LBRA type SQ_RBRA
#line 246 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                           { yylhs.value.as < type_ptr > () = type_s.list_type(yystack_[1].value.as < type_ptr > ()); }
#line 1574 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 26: // func_type: LBRA opt_types RBRA PROD type
#line 249 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                                    { yylhs.value.as < type_ptr > () = type_s.func_type(yystack_[3].value.as < std::vector<type_ptr> > (), yystack_[0].value.as < type_ptr > ()); }
#line 1580 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 27: // nominal_type: LABEL
#line 252 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
            { yylhs.value.as < type_ptr > () = type_s.nominal_type(yystack_[0].value.as < std::string > ()); }
#line 1586 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 28: // opt_params: TSEP
#line 255 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < std::vector<Param> > () = std::vector<Param>{}; }
#line 1592 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 29: // opt_params: params
#line 256 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < std::vector<Param> > () = std::move(yystack_[0].value.as < std::vector<Param> > ()); }
#line 1598 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 30: // params: param
#line 259 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
            { yylhs.value.as < std::vector<Param> > () = std::vector<Param>{yystack_[0].value.as < Param > ()}; }
#line 1604 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 31: // params: params COMMA param
#line 261 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<Param> > ().push_back(std::move(yystack_[0].value.as < Param > ()));
            yylhs.value.as < std::vector<Param> > () = std::move(yystack_[2].value.as < std::vector<Param> > ());
        }
#line 1613 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 32: // param: LABEL TSEP type
#line 268 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < Param > () = Param(); 
            yylhs.value.as < Param > ().name = std::move(yystack_[2].value.as < std::string > ());
            yylhs.value.as < Param > ().type = std::move(yystack_[0].value.as < type_ptr > ());
            yylhs.value.as < Param > ().location = floc_to_loc(yystack_[2].location);
        }
#line 1624 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 33: // function_def: FUNC LABEL LBRA opt_params RBRA TSEP type program
#line 278 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {   
            yylhs.value.as < func_decl_ptr > () = std::make_unique<FuncDecl>();
            yylhs.value.as < func_decl_ptr > ()->is_closure = false;
            yylhs.value.as < func_decl_ptr > ()->name = std::move(yystack_[6].value.as < std::string > ());
            yylhs.value.as < func_decl_ptr > ()->params = std::move(yystack_[4].value.as < std::vector<Param> > ());
            yylhs.value.as < func_decl_ptr > ()->ret = std::move(yystack_[1].value.as < type_ptr > ());
            yylhs.value.as < func_decl_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());

            yylhs.value.as < func_decl_ptr > ()->location = floc_to_loc(yystack_[7].location);
        }
#line 1639 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 34: // fields: field
#line 292 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {   yylhs.value.as < std::vector<Field> > () = std::vector<Field>{}; yylhs.value.as < std::vector<Field> > ().push_back(std::move(yystack_[0].value.as < Field > ())); }
#line 1645 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 35: // fields: fields COMMA field
#line 294 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yystack_[2].value.as < std::vector<Field> > ().push_back(std::move(yystack_[0].value.as < Field > ()));
            yylhs.value.as < std::vector<Field> > () = std::move(yystack_[2].value.as < std::vector<Field> > ());
        }
#line 1654 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 36: // field: LABEL TSEP type
#line 302 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < Field > () = Field();
            yylhs.value.as < Field > ().name = std::move(yystack_[2].value.as < std::string > ());
            yylhs.value.as < Field > ().type = std::move(yystack_[0].value.as < type_ptr > ());

            yylhs.value.as < Field > ().location = floc_to_loc(yystack_[2].location);
        }
#line 1666 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 37: // struct_def: STRUCT LABEL LBRA fields RBRA
#line 312 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < struct_decl_ptr > () = std::make_unique<StructDecl>();
            yylhs.value.as < struct_decl_ptr > ()->name = std::move(yystack_[3].value.as < std::string > ());
            yylhs.value.as < struct_decl_ptr > ()->fields = std::move(yystack_[1].value.as < std::vector<Field> > ());

            yylhs.value.as < struct_decl_ptr > ()->location = floc_to_loc(yystack_[4].location);
        }
#line 1678 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 38: // evar: LABEL
#line 322 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
            { yylhs.value.as < std::string > () = std::move(yystack_[0].value.as < std::string > ()); }
#line 1684 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 39: // evars: evar
#line 325 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{yystack_[0].value.as < std::string > ()}; }
#line 1690 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 40: // evars: evars COMMA evar
#line 327 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));
            yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ());
        }
#line 1699 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 41: // enum_def: ENUM LABEL LBRA evars RBRA
#line 335 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < enum_decl_ptr > () = std::make_unique<EnumDecl>(); 
            yylhs.value.as < enum_decl_ptr > ()->name = std::move(yystack_[3].value.as < std::string > ());
            yylhs.value.as < enum_decl_ptr > ()->evar = std::move(yystack_[1].value.as < std::vector<std::string> > ());

            yylhs.value.as < enum_decl_ptr > ()->location = floc_to_loc(yystack_[4].location);
        }
#line 1711 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 42: // program: helpers branch_expr
#line 346 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < prog_ptr > () = std::make_unique<ProgramNode>();
            yylhs.value.as < prog_ptr > ()->decl = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
            yylhs.value.as < prog_ptr > ()->body = std::move(yystack_[0].value.as < expr_ptr > ());
        }
#line 1721 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 43: // branch_expr: return_expr
#line 354 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                  { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 1727 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 44: // branch_expr: guard_expr
#line 355 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < guard_ptr > ()); }
#line 1733 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 45: // branch_expr: case_expr
#line 356 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < case_ptr > ()); }
#line 1739 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 46: // guard_expr: CASE OF TSEP guards PEND
#line 361 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < guard_ptr > () = std::make_unique<GuardNode>();
            yylhs.value.as < guard_ptr > ()->branches = std::move(yystack_[1].value.as < std::vector<g_branch_ptr> > ());

            yylhs.value.as < guard_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 1750 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 47: // guards: guard
#line 371 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < std::vector<g_branch_ptr> > () = std::vector<g_branch_ptr>{}; 
            yylhs.value.as < std::vector<g_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < g_branch_ptr > ()));
        }
#line 1759 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 48: // guards: guards COMMA guard
#line 376 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<g_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < g_branch_ptr > ()));
            yylhs.value.as < std::vector<g_branch_ptr> > () = std::move(yystack_[2].value.as < std::vector<g_branch_ptr> > ());
        }
#line 1768 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 49: // guard: BAR value_expr ARROW program
#line 384 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < g_branch_ptr > () = std::make_unique<GuardBranchNode>();
            yylhs.value.as < g_branch_ptr > ()->match = std::move(yystack_[2].value.as < expr_ptr > ());
            yylhs.value.as < g_branch_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());

            yylhs.value.as < g_branch_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 1780 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
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
#line 1797 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 51: // case_expr: MARK value_expr OF TSEP patterns PEND
#line 408 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < case_ptr > () = std::make_unique<CaseNode>();
            yylhs.value.as < case_ptr > ()->target = std::move(yystack_[4].value.as < expr_ptr > ());
            yylhs.value.as < case_ptr > ()->patterns = std::move(yystack_[1].value.as < std::vector<c_branch_ptr> > ());

            yylhs.value.as < case_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 1809 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 52: // patterns: pattern_branch
#line 419 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < std::vector<c_branch_ptr> > () = std::vector<c_branch_ptr>{}; 
            yylhs.value.as < std::vector<c_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < c_branch_ptr > ())); 
        }
#line 1818 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 53: // patterns: patterns COMMA pattern_branch
#line 424 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<c_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < c_branch_ptr > ()));
            yylhs.value.as < std::vector<c_branch_ptr> > () = std::move(yystack_[2].value.as < std::vector<c_branch_ptr> > ());
        }
#line 1827 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
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
#line 1840 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
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
#line 1853 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 56: // literal: char_lit
#line 452 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1859 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 57: // literal: int_lit
#line 453 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1865 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 58: // literal: float_lit
#line 454 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1871 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 59: // literal: bool_lit
#line 455 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1877 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 60: // literal: enum_lit
#line 456 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1883 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 61: // literal: list_pattern
#line 457 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1889 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 62: // size_pattern: list_size_pattern
#line 461 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                        { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1895 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 63: // size_pattern: struct_size_pattern
#line 462 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                          { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1901 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 64: // pattern: literal
#line 465 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1907 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 65: // pattern: DEFAULT
#line 466 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::make_unique<DefaultLit>(); yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);}
#line 1913 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 66: // pattern: NIL
#line 467 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < literal_ptr > () = std::make_unique<NilLit>(); yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);}
#line 1919 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 67: // enum_lit: LABEL
#line 472 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<EnumLit>();
            temp->elem = std::move(yystack_[0].value.as < std::string > ()); 
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 1931 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 68: // list_pattern: SQ_LBRA SQ_RBRA
#line 482 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < literal_ptr > () = std::make_unique<EmptyLit>();

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 1941 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 69: // string_expr: STRING
#line 490 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             {yylhs.value.as < expr_ptr > () = str_to_chlist(yystack_[0].value.as < std::string > ()); yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[0].location); }
#line 1947 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 70: // list_size_pattern: list_vars
#line 495 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<ListPatternLit>(); 
            temp->patterns = std::move(yystack_[0].value.as < std::vector<std::string> > ());
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 1959 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 71: // list_vars: LABEL TSEP LABEL
#line 506 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{};
            yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[2].value.as < std::string > ()));
            yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ())); 
        }
#line 1969 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 72: // list_vars: list_vars TSEP LABEL
#line 512 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));
            yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ());
        }
#line 1978 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
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
#line 1991 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 74: // struct_vars: LABEL
#line 531 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{}; yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));}
#line 1997 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 75: // struct_vars: NIL
#line 532 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
         { yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{}; yylhs.value.as < std::vector<std::string> > ().push_back("");}
#line 2003 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 76: // struct_vars: struct_vars COMMA LABEL
#line 533 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                              { yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ())); yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ()); }
#line 2009 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 77: // struct_vars: struct_vars COMMA NIL
#line 534 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                            { yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move("")); yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ()); }
#line 2015 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 78: // return_expr: RETURN value_expr
#line 539 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<ReturnNode>();
            temp->rexp = std::move(yystack_[0].value.as < expr_ptr > ()); 
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2027 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 79: // helpers: %empty
#line 549 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < std::vector<decl_ptr> > () = std::vector<decl_ptr>{}; }
#line 2033 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 80: // helpers: helpers helper_expr
#line 551 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[1].value.as < std::vector<decl_ptr> > ().push_back(std::move(yystack_[0].value.as < decl_ptr > ()));
            yylhs.value.as < std::vector<decl_ptr> > () = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
        }
#line 2042 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 81: // helper_expr: assign_expr
#line 558 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                  { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < decl_ptr > ()); }
#line 2048 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 82: // helper_expr: print_expr
#line 559 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < print_ptr > ()); }
#line 2054 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 83: // print_expr: PRINT LBRA value_expr RBRA
#line 564 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < print_ptr > () = std::make_unique<PrintNode>();
            yylhs.value.as < print_ptr > ()->msg = std::move(yystack_[1].value.as < expr_ptr > ());

            yylhs.value.as < print_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 2065 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 84: // assign_val_expr: value_expr
#line 573 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2071 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 85: // assign_val_expr: READ LBRA RBRA
#line 574 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                     {
        yylhs.value.as < expr_ptr > () = std::make_unique<ReadNode>(); 
        yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[2].location);
    }
#line 2080 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 86: // assign_expr: LABEL TSEP LBRA opt_params RBRA PROD type LBRA program RBRA
#line 581 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<FuncDecl>();
            temp->is_closure = true;
            temp->name = std::move(yystack_[9].value.as < std::string > ());
            temp->params = std::move(yystack_[6].value.as < std::vector<Param> > ());
            temp->ret = std::move(yystack_[3].value.as < type_ptr > ());
            temp->body = std::move(yystack_[1].value.as < prog_ptr > ());
            yylhs.value.as < decl_ptr > () = std::move(temp);

            yylhs.value.as < decl_ptr > ()->location = floc_to_loc(yystack_[9].location);
        }
#line 2096 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 87: // assign_expr: LABEL TSEP type ASSGN assign_val_expr
#line 593 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<VarDecl>();
            temp->name = std::move(yystack_[4].value.as < std::string > ());
            temp->type = std::move(yystack_[2].value.as < type_ptr > ());
            temp->r_val = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < decl_ptr > () = std::move(temp);
            yylhs.value.as < decl_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2109 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 88: // int_lit: INT
#line 605 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<IntLit>();
            temp->value = yystack_[0].value.as < uint64_t > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2121 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 89: // float_lit: FLOAT
#line 615 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<IntLit>();
            temp->value = yystack_[0].value.as < double > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2133 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 90: // bool_lit: TRUE
#line 625 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<BoolLit>();
            temp->value = true;
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2145 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 91: // bool_lit: FALSE
#line 633 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<BoolLit>();
            temp->value = false;
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2157 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 92: // char_lit: CHAR
#line 644 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<CharLit>();
            temp->value = yystack_[0].value.as < char > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);

            yylhs.value.as < literal_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2169 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 93: // bool_op: BOR
#line 653 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::BOR; }
#line 2175 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 94: // bool_op: BAND
#line 654 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::BAND; }
#line 2181 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 95: // comp_op: CEQ
#line 658 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CEQ; }
#line 2187 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 96: // comp_op: CNEQ
#line 659 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CNEQ; }
#line 2193 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 97: // comp_op: CGT
#line 660 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CGT; }
#line 2199 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 98: // comp_op: CLT
#line 661 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CLT; }
#line 2205 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 99: // comp_op: CGEQ
#line 662 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CGEQ; }
#line 2211 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 100: // comp_op: CLEQ
#line 663 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CLEQ; }
#line 2217 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 101: // bitwise_op: LAND
#line 667 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::LAND; }
#line 2223 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 102: // bitwise_op: BAR
#line 668 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LOR; }
#line 2229 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 103: // bitwise_op: LXOR
#line 669 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::LXOR; }
#line 2235 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 104: // shift_op: LSL
#line 672 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LSL; }
#line 2241 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 105: // shift_op: LSR
#line 673 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LSR; }
#line 2247 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 106: // additive_op: ADD
#line 676 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::ADD; }
#line 2253 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 107: // additive_op: SUB
#line 677 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::SUB; }
#line 2259 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 108: // additive_op: CONCAT
#line 678 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
             { yylhs.value.as < BinaryOp > () = BinaryOp::CONCAT; }
#line 2265 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 109: // mult_op: MUL
#line 682 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::MUL; }
#line 2271 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 110: // mult_op: DIV
#line 683 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::DIV; }
#line 2277 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 111: // mult_op: MOD
#line 684 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::MOD; }
#line 2283 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 112: // mult_op: FLR
#line 685 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::FLR; }
#line 2289 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 113: // unary_op: BNOT
#line 689 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < UnaryOp > () = UnaryOp::BNOT; }
#line 2295 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 114: // unary_op: LNEG
#line 690 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
           { yylhs.value.as < UnaryOp > () = UnaryOp::LNEG; }
#line 2301 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 115: // unary_op: SUB
#line 691 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
          { yylhs.value.as < UnaryOp > () = UnaryOp::MINUS; }
#line 2307 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 116: // nominal_expr: LABEL
#line 696 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            auto temp = std::make_unique<NominalNode>();
            temp->label = std::move(yystack_[0].value.as < std::string > ()); 
            yylhs.value.as < expr_ptr > () = std::move(temp);
            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2318 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 117: // list_expr: empty_list
#line 704 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < list_ptr > ()); }
#line 2324 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 118: // list_expr: list_con
#line 705 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < list_ptr > ()); }
#line 2330 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 119: // list_expr: string_expr
#line 706 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                  { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2336 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 120: // empty_list: SQ_LBRA SQ_RBRA
#line 711 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < list_ptr > () = std::make_unique<ListNode>(); 
            yylhs.value.as < list_ptr > ()->elems = std::vector<expr_ptr>{}; 
            yylhs.value.as < list_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2346 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 121: // list_con: SQ_LBRA expr_list SQ_RBRA
#line 720 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < list_ptr > () = std::make_unique<ListNode>(); 
            yylhs.value.as < list_ptr > ()->elems = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ()); 
            yylhs.value.as < list_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 2356 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 122: // expr_list: value_expr
#line 729 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        { 
            yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>{};
            yylhs.value.as < std::vector<expr_ptr> > ().push_back(std::move(yystack_[0].value.as < expr_ptr > ())); 
        }
#line 2365 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 123: // expr_list: expr_list COMMA value_expr
#line 734 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yystack_[2].value.as < std::vector<expr_ptr> > ().push_back(std::move(yystack_[0].value.as < expr_ptr > ()));
            yylhs.value.as < std::vector<expr_ptr> > () = std::move(yystack_[2].value.as < std::vector<expr_ptr> > ());
        }
#line 2374 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 124: // struct_expr: LABEL C_LBRA expr_list C_RBRA
#line 742 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<StructNode>();
            temp->name = std::move(yystack_[3].value.as < std::string > ());
            temp->fields = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 2387 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 125: // struct_expr: NIL
#line 751 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            yylhs.value.as < expr_ptr > () = std::make_unique<NilLit>();
            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[0].location);
        }
#line 2396 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 126: // value_expr: bool_expr
#line 757 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2402 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 127: // bool_expr: comp_expr
#line 760 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2408 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 128: // bool_expr: bool_expr bool_op comp_expr
#line 762 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2422 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 129: // comp_expr: bitwise_expr
#line 774 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2428 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 130: // comp_expr: bitwise_expr comp_op bitwise_expr
#line 776 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2442 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 131: // bitwise_expr: shift_expr
#line 788 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2448 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 132: // bitwise_expr: bitwise_expr bitwise_op shift_expr
#line 790 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2462 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 133: // shift_expr: additive_expr
#line 802 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                    { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2468 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 134: // shift_expr: shift_expr shift_op additive_expr
#line 804 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2482 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 135: // additive_expr: mult_expr
#line 816 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2488 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 136: // additive_expr: additive_expr additive_op mult_expr
#line 818 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2502 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 137: // mult_expr: pow_expr
#line 830 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2508 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 138: // mult_expr: mult_expr mult_op pow_expr
#line 832 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2522 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 139: // pow_expr: unary_expr
#line 844 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2528 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 140: // pow_expr: unary_expr POW pow_expr
#line 846 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = BinaryOp::POW;
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2542 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 141: // unary_expr: postfix_expr
#line 858 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2548 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 142: // unary_expr: unary_op postfix_expr
#line 860 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<UnaryNode>();
            temp->op = yystack_[1].value.as < UnaryOp > ();
            temp->exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2561 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 143: // postfix_expr: literal_expr
#line 871 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2567 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 144: // postfix_expr: postfix_expr SQ_LBRA value_expr SQ_RBRA
#line 873 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = BinaryOp::INDEX;
            temp->l_exp = std::move(yystack_[3].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[1].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 2581 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 145: // postfix_expr: postfix_expr DOT LABEL
#line 883 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<AccessNode>();
            temp->field = std::move(yystack_[0].value.as < std::string > ());
            temp->struct_expr = std::move(yystack_[2].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[1].location);
        }
#line 2594 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 146: // postfix_expr: postfix_expr LBRA RBRA
#line 892 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<CallNode>();
            temp->f_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->params = std::vector<expr_ptr>{};
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[2].location);
        }
#line 2607 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 147: // postfix_expr: postfix_expr LBRA expr_list RBRA
#line 901 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
        {
            auto temp = std::make_unique<CallNode>(); 
            temp->f_exp = std::move(yystack_[3].value.as < expr_ptr > ());
            temp->params = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);

            yylhs.value.as < expr_ptr > ()->location = floc_to_loc(yystack_[3].location);
        }
#line 2620 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 148: // literal_expr: int_lit
#line 912 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
              { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2626 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 149: // literal_expr: float_lit
#line 913 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2632 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 150: // literal_expr: char_lit
#line 914 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2638 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 151: // literal_expr: bool_lit
#line 915 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2644 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 152: // literal_expr: list_expr
#line 916 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2650 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 153: // literal_expr: nominal_expr
#line 917 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2656 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 154: // literal_expr: struct_expr
#line 918 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                  { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2662 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;

  case 155: // literal_expr: LBRA value_expr RBRA
#line 919 "/Users/huangyugen/Documents/cs projects/Kindred/src/parser.y"
                           { yylhs.value.as < expr_ptr > () = std::move(yystack_[1].value.as < expr_ptr > ()); }
#line 2668 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"
    break;


#line 2672 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"

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









  const short parser::yypact_ninf_ = -174;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
    -174,    18,    26,  -174,  -174,    25,    84,    90,  -174,  -174,
    -174,  -174,    86,    89,    94,     6,   122,   124,   105,  -174,
     134,   131,  -174,   147,    -6,  -174,  -174,  -174,    44,   166,
     148,   161,   166,  -174,   122,  -174,   124,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,   166,   166,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,   166,  -174,  -174,  -174,  -174,   150,
     170,  -174,   164,  -174,   145,   166,  -174,  -174,   204,   166,
    -174,   172,   205,    82,   184,    82,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,   175,   181,  -174,  -174,  -174,  -174,
     186,  -174,  -174,  -174,    82,     2,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,   152,  -174,  -174,  -174,  -174,  -174,
     211,   -22,  -174,   179,    93,    15,    83,  -174,   176,    -1,
    -174,    82,  -174,   112,   183,   188,    82,   191,  -174,   140,
    -174,    -1,   187,  -174,  -174,    82,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,    82,    82,  -174,  -174,    82,
    -174,  -174,  -174,    82,  -174,  -174,  -174,  -174,    82,    82,
      42,    82,   231,   209,   105,   210,    63,   103,    19,  -174,
     142,  -174,  -174,    82,   143,  -174,    27,    93,    15,    83,
    -174,  -174,  -174,    68,   212,  -174,  -174,   177,   214,  -174,
    -174,   182,   185,   188,  -174,  -174,  -174,    79,  -174,  -174,
     213,   128,  -174,  -174,   189,   190,  -174,  -174,  -174,   215,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,   166,   217,  -174,
    -174,  -174,     3,   234,  -174,   143,  -174,  -174,  -174,   241,
     221,  -174,  -174,  -174,  -174,  -174,   144,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,     8,   225,  -174,  -174,  -174
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     1,     2,     0,     0,     0,     4,     5,
       6,     7,     0,     0,     0,     0,     0,     0,     0,    28,
       0,    29,    30,     0,     0,    34,    38,    39,     0,     0,
       0,     0,     0,    37,     0,    41,     0,    27,    21,    22,
      23,    24,    17,    18,     8,     0,    15,    32,    12,    19,
      20,    13,    16,    14,     0,    31,    36,    35,    40,     0,
       9,    10,     0,    79,     0,     0,    25,    33,     0,     0,
      11,     0,     0,     0,     0,     0,    42,    44,    45,    43,
      80,    82,    81,    26,     0,     0,    88,    89,    92,    69,
     116,    90,    91,   125,     0,     0,   115,   114,   113,   119,
     148,   149,   151,   150,     0,   153,   152,   117,   118,   154,
       0,   126,   127,   129,   131,   133,   135,   137,   139,   141,
     143,     0,    78,     8,     0,     0,     0,     0,   120,     0,
     122,   142,     0,    94,    93,     0,   101,   102,   103,    97,
      98,    99,   100,    95,    96,     0,     0,   104,   105,     0,
     106,   107,   108,     0,   109,   110,   111,   112,     0,     0,
       0,     0,     0,     0,    27,     0,     0,     0,     0,    47,
       0,   155,   121,     0,     0,   128,   130,   132,   134,   136,
     138,   140,   146,     0,     0,   145,    83,     0,     0,    87,
      84,     0,     0,     0,    46,   124,   123,    67,    65,    66,
       0,     0,    52,    64,     0,     0,    60,    61,    62,    70,
      63,    57,    58,    59,    56,   147,   144,     0,     0,    79,
      79,    48,     0,     0,    68,     0,    51,    79,    79,     0,
       0,    85,    50,    49,    74,    75,     0,    71,    53,    55,
      54,    72,    79,    73,     0,     0,    76,    77,    86
  };

  const short
  parser::yypgoto_[] =
  {
    -174,  -174,  -174,  -174,  -174,  -174,  -174,   -29,  -174,  -174,
    -174,  -174,  -174,  -174,   133,  -174,   220,  -174,  -174,   223,
    -174,   222,  -174,  -174,   -12,  -174,  -174,  -174,    66,  -174,
    -174,    35,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -173,  -163,
    -162,  -160,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -109,  -174,   -71,  -174,   126,   117,   118,
     114,   113,    28,  -174,   163,  -174
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     1,     2,     8,    59,    60,    46,    61,    48,    49,
      50,    51,    52,    53,    20,    21,    22,     9,    24,    25,
      10,    27,    28,    11,    67,    76,    77,   168,   169,    78,
     201,   202,   203,   204,   205,   206,   207,    99,   208,   209,
     210,   236,    79,    68,    80,    81,   189,    82,   100,   101,
     102,   103,   135,   145,   146,   149,   153,   158,   104,   105,
     106,   107,   108,   129,   109,   130,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120
  };

  const unsigned char
  parser::yytable_[] =
  {
      47,   211,   110,    56,   122,    86,    87,    88,    89,    90,
     234,   212,   213,    18,   214,   246,    62,   170,     3,    91,
      92,    93,   235,   127,    33,    63,     4,   247,   160,    34,
     161,    94,    12,    95,   128,   162,    70,     5,   133,   134,
      83,     6,     7,    19,    96,    86,    87,    88,    89,    90,
     163,   183,   211,    97,   193,   124,   150,   151,   194,    91,
      92,    93,   212,   213,    98,   214,    86,    87,    88,    89,
      90,    94,   182,    95,    35,   136,   137,   138,   152,    36,
      91,    92,    93,   188,    96,    86,    87,    88,    89,    90,
     184,    13,    94,    97,    95,   190,   192,    14,   215,    91,
      92,    93,   196,   173,    98,    96,    86,    87,    88,    89,
      90,    94,   222,    95,    97,    15,   223,   191,    16,   164,
      91,    92,    93,    17,    96,    98,   154,   155,   156,    23,
     157,    26,    94,    97,    95,    38,    39,    40,    41,    42,
      43,    44,    29,    45,    98,    96,    86,    87,    88,    19,
     197,   147,   148,   198,    97,    86,    87,    88,    89,    90,
      91,    92,   199,   225,    30,    98,    31,   226,    18,    91,
      92,    93,   172,    37,   200,   173,   195,   173,   243,   244,
      64,    94,    37,    95,    32,    54,   180,   181,   230,    38,
      39,    40,    41,    42,    43,    44,    66,    45,    38,    39,
      40,    41,    42,    43,   123,    65,    45,   232,   233,    84,
      69,    71,    72,   121,    85,   239,   240,    73,   125,   126,
     132,   171,   159,   166,   174,    74,    75,   136,   137,   138,
     245,   139,   140,   141,   142,   143,   144,   167,   185,   186,
     187,   237,   217,   218,   216,   224,   219,   231,   241,   220,
     242,    55,   229,   227,   228,   248,   165,    57,    58,   221,
     238,   175,   176,   178,   177,     0,   179,   131
  };

  const short
  parser::yycheck_[] =
  {
      29,   174,    73,    32,    75,     3,     4,     5,     6,     7,
       7,   174,   174,     7,   174,     7,    45,   126,     0,    17,
      18,    19,    19,    94,    30,    54,     0,    19,    29,    35,
      31,    29,     7,    31,    32,    36,    65,    11,    60,    61,
      69,    15,    16,    37,    42,     3,     4,     5,     6,     7,
     121,   160,   225,    51,    35,    84,    41,    42,    39,    17,
      18,    19,   225,   225,    62,   225,     3,     4,     5,     6,
       7,    29,    30,    31,    30,    48,    49,    50,    63,    35,
      17,    18,    19,    20,    42,     3,     4,     5,     6,     7,
     161,     7,    29,    51,    31,   166,   167,     7,    30,    17,
      18,    19,   173,    35,    62,    42,     3,     4,     5,     6,
       7,    29,    33,    31,    51,    29,    37,    14,    29,     7,
      17,    18,    19,    29,    42,    62,    43,    44,    45,     7,
      47,     7,    29,    51,    31,    23,    24,    25,    26,    27,
      28,    29,    37,    31,    62,    42,     3,     4,     5,    37,
       7,    58,    59,    10,    51,     3,     4,     5,     6,     7,
      17,    18,    19,    35,    30,    62,    35,    39,     7,    17,
      18,    19,    32,     7,    31,    35,    34,    35,    34,    35,
      30,    29,     7,    31,    37,    37,   158,   159,   217,    23,
      24,    25,    26,    27,    28,    29,    32,    31,    23,    24,
      25,    26,    27,    28,    29,    35,    31,   219,   220,    37,
      65,     7,     8,    29,     9,   227,   228,    13,    37,    33,
       9,    30,    46,    40,    37,    21,    22,    48,    49,    50,
     242,    52,    53,    54,    55,    56,    57,    49,     7,    30,
      30,     7,    65,    29,    32,    32,    64,    30,     7,    64,
      29,    31,    37,    64,    64,    30,   123,    34,    36,   193,
     225,   135,   145,   149,   146,    -1,   153,   104
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    67,    68,     0,     0,    11,    15,    16,    69,    83,
      86,    89,     7,     7,     7,    29,    29,    29,     7,    37,
      80,    81,    82,     7,    84,    85,     7,    87,    88,    37,
      30,    35,    37,    30,    35,    30,    35,     7,    23,    24,
      25,    26,    27,    28,    29,    31,    72,    73,    74,    75,
      76,    77,    78,    79,    37,    82,    73,    85,    87,    70,
      71,    73,    73,    73,    30,    35,    32,    90,   109,    65,
      73,     7,     8,    13,    21,    22,    91,    92,    95,   108,
     110,   111,   113,    73,    37,     9,     3,     4,     5,     6,
       7,    17,    18,    19,    29,    31,    42,    51,    62,   103,
     114,   115,   116,   117,   124,   125,   126,   127,   128,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,    29,   131,    29,    73,    37,    33,   131,    32,   129,
     131,   140,     9,    60,    61,   118,    48,    49,    50,    52,
      53,    54,    55,    56,    57,   119,   120,    58,    59,   121,
      41,    42,    63,   122,    43,    44,    45,    47,   123,    46,
      29,    31,    36,   131,     7,    80,    40,    49,    93,    94,
     129,    30,    32,    35,    37,   133,   134,   135,   136,   137,
     138,   138,    30,   129,   131,     7,    30,    30,    20,   112,
     131,    14,   131,    35,    39,    34,   131,     7,    10,    19,
      31,    96,    97,    98,    99,   100,   101,   102,   104,   105,
     106,   114,   115,   116,   117,    30,    32,    65,    29,    64,
      64,    94,    33,    37,    32,    35,    39,    64,    64,    37,
      73,    30,    90,    90,     7,    19,   107,     7,    97,    90,
      90,     7,    29,    34,    35,    90,     7,    19,    30
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
     109,   110,   110,   111,   112,   112,   113,   113,   114,   115,
     116,   116,   117,   118,   118,   119,   119,   119,   119,   119,
     119,   120,   120,   120,   121,   121,   122,   122,   122,   123,
     123,   123,   123,   124,   124,   124,   125,   126,   126,   126,
     127,   128,   129,   129,   130,   130,   131,   132,   132,   133,
     133,   134,   134,   135,   135,   136,   136,   137,   137,   138,
     138,   139,   139,   140,   140,   140,   140,   140,   141,   141,
     141,   141,   141,   141,   141,   141
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     2,     1,     1,     1,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     5,     1,     1,     1,
       1,     3,     3,     8,     1,     3,     3,     5,     1,     1,
       3,     5,     2,     1,     1,     1,     5,     1,     3,     4,
       4,     6,     1,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     3,     3,     4,     1,     1,     3,     3,     2,     0,
       2,     1,     1,     4,     1,     3,    10,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     1,     3,     4,     1,     1,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     2,     1,     4,     3,     3,     4,     1,     1,
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
  "return_expr", "helpers", "helper_expr", "print_expr", "assign_val_expr",
  "assign_expr", "int_lit", "float_lit", "bool_lit", "char_lit", "bool_op",
  "comp_op", "bitwise_op", "shift_op", "additive_op", "mult_op",
  "unary_op", "nominal_expr", "list_expr", "empty_list", "list_con",
  "expr_list", "struct_expr", "value_expr", "bool_expr", "comp_expr",
  "bitwise_expr", "shift_expr", "additive_expr", "mult_expr", "pow_expr",
  "unary_expr", "postfix_expr", "literal_expr", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   185,   185,   194,   196,   204,   205,   206,   209,   210,
     213,   214,   220,   221,   222,   226,   227,   231,   232,   233,
     234,   238,   239,   242,   243,   246,   249,   252,   255,   256,
     259,   260,   267,   277,   291,   293,   301,   311,   322,   325,
     326,   334,   345,   354,   355,   356,   360,   370,   375,   383,
     391,   407,   418,   423,   431,   440,   452,   453,   454,   455,
     456,   457,   461,   462,   465,   466,   467,   471,   481,   490,
     494,   505,   511,   519,   531,   532,   533,   534,   538,   549,
     550,   558,   559,   563,   573,   574,   580,   592,   604,   614,
     624,   632,   643,   653,   654,   658,   659,   660,   661,   662,
     663,   667,   668,   669,   672,   673,   676,   677,   678,   682,
     683,   684,   685,   689,   690,   691,   695,   704,   705,   706,
     710,   719,   728,   733,   741,   750,   757,   760,   761,   774,
     775,   788,   789,   802,   803,   816,   817,   830,   831,   844,
     845,   858,   859,   871,   872,   882,   891,   900,   912,   913,
     914,   915,   916,   917,   918,   919
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
#line 3177 "/Users/huangyugen/Documents/cs projects/Kindred/parser.cpp"

