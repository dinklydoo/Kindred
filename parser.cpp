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

    module_ptr module;
    extern yy::parser::symbol_type yylex();

#line 63 "parser.cpp"


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

#line 32 "src/parser.y"
namespace yy {
#line 161 "parser.cpp"

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
      case symbol_kind::S_param_expr: // param_expr
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
      case symbol_kind::S_size_pattern_two: // size_pattern_two
        value.YY_MOVE_OR_COPY< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_types: // opt_types
      case symbol_kind::S_types: // types
        value.YY_MOVE_OR_COPY< std::vector<type_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_def: // struct_def
        value.YY_MOVE_OR_COPY< struct_decl_ptr > (YY_MOVE (that.value));
        break;

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

      case symbol_kind::S_assign_expr: // assign_expr
        value.YY_MOVE_OR_COPY< var_decl_ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_param_expr: // param_expr
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
      case symbol_kind::S_size_pattern_two: // size_pattern_two
        value.move< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_types: // opt_types
      case symbol_kind::S_types: // types
        value.move< std::vector<type_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_def: // struct_def
        value.move< struct_decl_ptr > (YY_MOVE (that.value));
        break;

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

      case symbol_kind::S_assign_expr: // assign_expr
        value.move< var_decl_ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_param_expr: // param_expr
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
      case symbol_kind::S_size_pattern_two: // size_pattern_two
        value.copy< std::vector<std::string> > (that.value);
        break;

      case symbol_kind::S_opt_types: // opt_types
      case symbol_kind::S_types: // types
        value.copy< std::vector<type_ptr> > (that.value);
        break;

      case symbol_kind::S_struct_def: // struct_def
        value.copy< struct_decl_ptr > (that.value);
        break;

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

      case symbol_kind::S_assign_expr: // assign_expr
        value.copy< var_decl_ptr > (that.value);
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
      case symbol_kind::S_param_expr: // param_expr
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
      case symbol_kind::S_size_pattern_two: // size_pattern_two
        value.move< std::vector<std::string> > (that.value);
        break;

      case symbol_kind::S_opt_types: // opt_types
      case symbol_kind::S_types: // types
        value.move< std::vector<type_ptr> > (that.value);
        break;

      case symbol_kind::S_struct_def: // struct_def
        value.move< struct_decl_ptr > (that.value);
        break;

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

      case symbol_kind::S_assign_expr: // assign_expr
        value.move< var_decl_ptr > (that.value);
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
      case symbol_kind::S_param_expr: // param_expr
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
      case symbol_kind::S_size_pattern_two: // size_pattern_two
        yylhs.value.emplace< std::vector<std::string> > ();
        break;

      case symbol_kind::S_opt_types: // opt_types
      case symbol_kind::S_types: // types
        yylhs.value.emplace< std::vector<type_ptr> > ();
        break;

      case symbol_kind::S_struct_def: // struct_def
        yylhs.value.emplace< struct_decl_ptr > ();
        break;

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

      case symbol_kind::S_assign_expr: // assign_expr
        yylhs.value.emplace< var_decl_ptr > ();
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
#line 174 "src/parser.y"
        { 
            yylhs.value.as < module_ptr > () = std::make_unique<ModuleNode>();
            yylhs.value.as < module_ptr > ()->decl = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
        }
#line 1457 "parser.cpp"
    break;

  case 3: // definitions: %empty
#line 182 "src/parser.y"
        { yylhs.value.as < std::vector<decl_ptr> > () = std::vector<decl_ptr>{}; }
#line 1463 "parser.cpp"
    break;

  case 4: // definitions: definitions definition
#line 184 "src/parser.y"
        { 
            yystack_[1].value.as < std::vector<decl_ptr> > ().push_back(std::move(yystack_[0].value.as < decl_ptr > ()));
            yylhs.value.as < std::vector<decl_ptr> > () = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
        }
#line 1472 "parser.cpp"
    break;

  case 5: // definition: function_def
#line 191 "src/parser.y"
                  { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < func_decl_ptr > ()); }
#line 1478 "parser.cpp"
    break;

  case 6: // definition: struct_def
#line 192 "src/parser.y"
                { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < struct_decl_ptr > ()); }
#line 1484 "parser.cpp"
    break;

  case 7: // definition: enum_def
#line 193 "src/parser.y"
              { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < enum_decl_ptr > ()); }
#line 1490 "parser.cpp"
    break;

  case 8: // opt_types: %empty
#line 196 "src/parser.y"
             { yylhs.value.as < std::vector<type_ptr> > () = std::vector<type_ptr>{}; }
#line 1496 "parser.cpp"
    break;

  case 9: // opt_types: types
#line 197 "src/parser.y"
            { yylhs.value.as < std::vector<type_ptr> > () = std::move(yystack_[0].value.as < std::vector<type_ptr> > ()); }
#line 1502 "parser.cpp"
    break;

  case 10: // types: type
#line 200 "src/parser.y"
           { yylhs.value.as < std::vector<type_ptr> > () = std::vector<type_ptr>{yystack_[0].value.as < type_ptr > ()}; }
#line 1508 "parser.cpp"
    break;

  case 11: // types: types COMMA type
#line 201 "src/parser.y"
                       {
        yystack_[2].value.as < std::vector<type_ptr> > ().push_back(std::move(yystack_[0].value.as < type_ptr > ()));
        yylhs.value.as < std::vector<type_ptr> > () = std::move(yystack_[2].value.as < std::vector<type_ptr> > ());
    }
#line 1517 "parser.cpp"
    break;

  case 12: // type: literal_type
#line 207 "src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1523 "parser.cpp"
    break;

  case 13: // type: list_type
#line 208 "src/parser.y"
                { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1529 "parser.cpp"
    break;

  case 14: // type: func_type
#line 209 "src/parser.y"
                { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1535 "parser.cpp"
    break;

  case 15: // type: nominal_type
#line 210 "src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1541 "parser.cpp"
    break;

  case 16: // literal_type: T_CHAR
#line 214 "src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.char_type(); }
#line 1547 "parser.cpp"
    break;

  case 17: // literal_type: T_BOOL
#line 215 "src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.bool_type(); }
#line 1553 "parser.cpp"
    break;

  case 18: // literal_type: int_lit_type
#line 216 "src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1559 "parser.cpp"
    break;

  case 19: // literal_type: float_lit_type
#line 217 "src/parser.y"
                     { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1565 "parser.cpp"
    break;

  case 20: // int_lit_type: T_INT
#line 221 "src/parser.y"
            { yylhs.value.as < type_ptr > () = type_s.int_type(); }
#line 1571 "parser.cpp"
    break;

  case 21: // int_lit_type: T_LONG
#line 222 "src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.long_type(); }
#line 1577 "parser.cpp"
    break;

  case 22: // float_lit_type: T_FLOAT
#line 225 "src/parser.y"
              { yylhs.value.as < type_ptr > () = type_s.float_type(); }
#line 1583 "parser.cpp"
    break;

  case 23: // float_lit_type: T_DOUBLE
#line 226 "src/parser.y"
               { yylhs.value.as < type_ptr > () = type_s.double_type(); }
#line 1589 "parser.cpp"
    break;

  case 24: // list_type: SQ_LBRA type SQ_RBRA
#line 229 "src/parser.y"
                           { yylhs.value.as < type_ptr > () = type_s.list_type(yystack_[1].value.as < type_ptr > ()); }
#line 1595 "parser.cpp"
    break;

  case 25: // func_type: LBRA opt_types RBRA PROD type
#line 232 "src/parser.y"
                                    { yylhs.value.as < type_ptr > () = type_s.func_type(yystack_[3].value.as < std::vector<type_ptr> > (), yystack_[0].value.as < type_ptr > ()); }
#line 1601 "parser.cpp"
    break;

  case 26: // nominal_type: LABEL
#line 235 "src/parser.y"
            { yylhs.value.as < type_ptr > () = type_s.nominal_type(yystack_[0].value.as < std::string > ()); }
#line 1607 "parser.cpp"
    break;

  case 27: // opt_params: %empty
#line 238 "src/parser.y"
             { yylhs.value.as < std::vector<Param> > () = std::vector<Param>{}; }
#line 1613 "parser.cpp"
    break;

  case 28: // opt_params: params
#line 239 "src/parser.y"
             { yylhs.value.as < std::vector<Param> > () = std::move(yystack_[0].value.as < std::vector<Param> > ()); }
#line 1619 "parser.cpp"
    break;

  case 29: // params: param
#line 242 "src/parser.y"
            { yylhs.value.as < std::vector<Param> > () = std::vector<Param>{yystack_[0].value.as < Param > ()}; }
#line 1625 "parser.cpp"
    break;

  case 30: // params: params COMMA param
#line 244 "src/parser.y"
        {
            yystack_[2].value.as < std::vector<Param> > ().push_back(std::move(yystack_[0].value.as < Param > ()));
            yylhs.value.as < std::vector<Param> > () = std::move(yystack_[2].value.as < std::vector<Param> > ());
        }
#line 1634 "parser.cpp"
    break;

  case 31: // param: LABEL TSEP type
#line 251 "src/parser.y"
        { 
            yylhs.value.as < Param > () = Param(); 
            yylhs.value.as < Param > ().name = std::move(yystack_[2].value.as < std::string > ());
            yylhs.value.as < Param > ().type = std::move(yystack_[0].value.as < type_ptr > ());
        }
#line 1644 "parser.cpp"
    break;

  case 32: // function_def: FUNC LABEL LBRA opt_params RBRA TSEP type program
#line 260 "src/parser.y"
        {   
            yylhs.value.as < func_decl_ptr > () = std::make_unique<FuncDecl>();
            yylhs.value.as < func_decl_ptr > ()->name = std::move(yystack_[6].value.as < std::string > ());
            yylhs.value.as < func_decl_ptr > ()->params = std::move(yystack_[4].value.as < std::vector<Param> > ());
            yylhs.value.as < func_decl_ptr > ()->ret = std::move(yystack_[1].value.as < type_ptr > ());
            yylhs.value.as < func_decl_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());
        }
#line 1656 "parser.cpp"
    break;

  case 33: // fields: field
#line 271 "src/parser.y"
        {   yylhs.value.as < std::vector<Field> > () = std::vector<Field>{}; yylhs.value.as < std::vector<Field> > ().push_back(std::move(yystack_[0].value.as < Field > ())); }
#line 1662 "parser.cpp"
    break;

  case 34: // fields: fields COMMA field
#line 273 "src/parser.y"
        { 
            yystack_[2].value.as < std::vector<Field> > ().push_back(std::move(yystack_[0].value.as < Field > ()));
            yylhs.value.as < std::vector<Field> > () = std::move(yystack_[2].value.as < std::vector<Field> > ());
        }
#line 1671 "parser.cpp"
    break;

  case 35: // field: LABEL TSEP type
#line 281 "src/parser.y"
        {
            yylhs.value.as < Field > () = Field();
            yylhs.value.as < Field > ().name = std::move(yystack_[2].value.as < std::string > ());
            yylhs.value.as < Field > ().type = std::move(yystack_[0].value.as < type_ptr > ());
        }
#line 1681 "parser.cpp"
    break;

  case 36: // struct_def: STRUCT LABEL LBRA fields RBRA
#line 289 "src/parser.y"
        {
            yylhs.value.as < struct_decl_ptr > () = std::make_unique<StructDecl>();
            yylhs.value.as < struct_decl_ptr > ()->name = std::move(yystack_[3].value.as < std::string > ());
            yylhs.value.as < struct_decl_ptr > ()->fields = std::move(yystack_[1].value.as < std::vector<Field> > ());
        }
#line 1691 "parser.cpp"
    break;

  case 37: // evar: LABEL
#line 297 "src/parser.y"
            { yylhs.value.as < std::string > () = std::move(yystack_[0].value.as < std::string > ()); }
#line 1697 "parser.cpp"
    break;

  case 38: // evars: evar
#line 300 "src/parser.y"
           { yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{yystack_[0].value.as < std::string > ()}; }
#line 1703 "parser.cpp"
    break;

  case 39: // evars: evars evar
#line 302 "src/parser.y"
        {
            yystack_[1].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));
            yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[1].value.as < std::vector<std::string> > ());
        }
#line 1712 "parser.cpp"
    break;

  case 40: // enum_def: ENUM LABEL LBRA evars RBRA
#line 310 "src/parser.y"
        { 
            yylhs.value.as < enum_decl_ptr > () = std::make_unique<EnumDecl>(); 
            yylhs.value.as < enum_decl_ptr > ()->name = std::move(yystack_[3].value.as < std::string > ());
            yylhs.value.as < enum_decl_ptr > ()->evar = std::move(yystack_[1].value.as < std::vector<std::string> > ());
        }
#line 1722 "parser.cpp"
    break;

  case 41: // program: helpers branch_expr
#line 319 "src/parser.y"
        {
            yylhs.value.as < prog_ptr > () = std::make_unique<ProgramNode>();
            yylhs.value.as < prog_ptr > ()->decl = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
            yylhs.value.as < prog_ptr > ()->body = std::move(yystack_[0].value.as < expr_ptr > ());
        }
#line 1732 "parser.cpp"
    break;

  case 42: // branch_expr: return_expr
#line 327 "src/parser.y"
                  { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 1738 "parser.cpp"
    break;

  case 43: // branch_expr: guard_expr
#line 328 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < guard_ptr > ()); }
#line 1744 "parser.cpp"
    break;

  case 44: // branch_expr: case_expr
#line 329 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < case_ptr > ()); }
#line 1750 "parser.cpp"
    break;

  case 45: // guard_expr: CASE OF TSEP guards PEND
#line 334 "src/parser.y"
        {
            yylhs.value.as < guard_ptr > () = std::make_unique<GuardNode>();
            yylhs.value.as < guard_ptr > ()->branches = std::move(yystack_[1].value.as < std::vector<g_branch_ptr> > ());
        }
#line 1759 "parser.cpp"
    break;

  case 46: // guards: guard
#line 342 "src/parser.y"
        { 
            yylhs.value.as < std::vector<g_branch_ptr> > () = std::vector<g_branch_ptr>{}; 
            yylhs.value.as < std::vector<g_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < g_branch_ptr > ()));
        }
#line 1768 "parser.cpp"
    break;

  case 47: // guards: guards COMMA guard
#line 347 "src/parser.y"
        {
            yystack_[2].value.as < std::vector<g_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < g_branch_ptr > ()));
            yylhs.value.as < std::vector<g_branch_ptr> > () = std::move(yystack_[2].value.as < std::vector<g_branch_ptr> > ());
        }
#line 1777 "parser.cpp"
    break;

  case 48: // guard: BAR value_expr ARROW program
#line 355 "src/parser.y"
        {
            yylhs.value.as < g_branch_ptr > () = std::make_unique<GuardBranchNode>();
            yylhs.value.as < g_branch_ptr > ()->match = std::move(yystack_[2].value.as < expr_ptr > ());
            yylhs.value.as < g_branch_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());
        }
#line 1787 "parser.cpp"
    break;

  case 49: // guard: BAR ELSE ARROW program
#line 361 "src/parser.y"
        {
            yylhs.value.as < g_branch_ptr > () = std::make_unique<GuardBranchNode>();
            auto temp = std::make_unique<BoolLit>();
            temp->value = true;
            yylhs.value.as < g_branch_ptr > ()->match = std::move(temp);
            yylhs.value.as < g_branch_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());
        }
#line 1799 "parser.cpp"
    break;

  case 50: // case_expr: MARK value_expr OF TSEP patterns PEND
#line 372 "src/parser.y"
        {
            yylhs.value.as < case_ptr > () = std::make_unique<CaseNode>();
            yylhs.value.as < case_ptr > ()->target = std::move(yystack_[4].value.as < expr_ptr > ());
            yylhs.value.as < case_ptr > ()->patterns = std::move(yystack_[1].value.as < std::vector<c_branch_ptr> > ());
        }
#line 1809 "parser.cpp"
    break;

  case 51: // patterns: pattern_branch
#line 381 "src/parser.y"
        { 
            yylhs.value.as < std::vector<c_branch_ptr> > () = std::vector<c_branch_ptr>{}; 
            yylhs.value.as < std::vector<c_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < c_branch_ptr > ())); 
        }
#line 1818 "parser.cpp"
    break;

  case 52: // patterns: patterns COMMA pattern_branch
#line 386 "src/parser.y"
        {
            yystack_[2].value.as < std::vector<c_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < c_branch_ptr > ()));
            yylhs.value.as < std::vector<c_branch_ptr> > () = std::move(yystack_[2].value.as < std::vector<c_branch_ptr> > ());
        }
#line 1827 "parser.cpp"
    break;

  case 53: // pattern_branch: pattern ARROW program
#line 394 "src/parser.y"
        {
            yylhs.value.as < c_branch_ptr > () = std::make_unique<CaseBranchNode>();
            yylhs.value.as < c_branch_ptr > ()->pattern = std::move(yystack_[2].value.as < literal_ptr > ());
            yylhs.value.as < c_branch_ptr > ()->body = std::move(yystack_[0].value.as < prog_ptr > ());
        }
#line 1837 "parser.cpp"
    break;

  case 54: // literal: char_lit
#line 402 "src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1843 "parser.cpp"
    break;

  case 55: // literal: int_lit
#line 403 "src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1849 "parser.cpp"
    break;

  case 56: // literal: float_lit
#line 404 "src/parser.y"
                { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1855 "parser.cpp"
    break;

  case 57: // literal: bool_lit
#line 405 "src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1861 "parser.cpp"
    break;

  case 58: // literal: enum_lit
#line 406 "src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1867 "parser.cpp"
    break;

  case 59: // literal: list_pattern
#line 407 "src/parser.y"
                   { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1873 "parser.cpp"
    break;

  case 60: // pattern: literal
#line 411 "src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1879 "parser.cpp"
    break;

  case 61: // pattern: NIL
#line 412 "src/parser.y"
          { yylhs.value.as < literal_ptr > () = std::make_unique<NilLit>(); }
#line 1885 "parser.cpp"
    break;

  case 62: // pattern: DEFAULT
#line 413 "src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::make_unique<DefaultLit>(); }
#line 1891 "parser.cpp"
    break;

  case 63: // enum_lit: LABEL
#line 418 "src/parser.y"
        { 
            auto temp = std::make_unique<EnumLit>();
            temp->elem = std::move(yystack_[0].value.as < std::string > ()); 
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 1901 "parser.cpp"
    break;

  case 64: // list_pattern: SQ_LBRA SQ_RBRA
#line 426 "src/parser.y"
        { 
            auto temp = std::make_unique<ListLit>();
            temp->elems = std::vector<literal_ptr>{}; 
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 1911 "parser.cpp"
    break;

  case 65: // list_pattern: list_lit
#line 431 "src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1917 "parser.cpp"
    break;

  case 66: // list_pattern: string_lit
#line 432 "src/parser.y"
                 { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1923 "parser.cpp"
    break;

  case 67: // list_pattern: size_patterns
#line 434 "src/parser.y"
        {
            auto temp = std::make_unique<ListPatternLit>(); 
            temp->patterns = std::move(yystack_[0].value.as < std::vector<std::string> > ());
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 1933 "parser.cpp"
    break;

  case 68: // string_lit: STRING
#line 442 "src/parser.y"
             {yylhs.value.as < literal_ptr > () = str_to_chlist(yystack_[0].value.as < std::string > ()); }
#line 1939 "parser.cpp"
    break;

  case 69: // list_lit: SQ_LBRA list_pattern_lit SQ_RBRA
#line 446 "src/parser.y"
        { 
            auto temp = std::make_unique<ListLit>(); 
            temp->elems = std::move(yystack_[1].value.as < std::vector<literal_ptr> > ()); 
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 1949 "parser.cpp"
    break;

  case 70: // list_pattern_lit: literal
#line 454 "src/parser.y"
        { 
            yylhs.value.as < std::vector<literal_ptr> > () = std::vector<literal_ptr>{}; 
            yylhs.value.as < std::vector<literal_ptr> > ().push_back(std::move(yystack_[0].value.as < literal_ptr > ()));
        }
#line 1958 "parser.cpp"
    break;

  case 71: // list_pattern_lit: list_pattern_lit COMMA literal
#line 459 "src/parser.y"
        { 
            yystack_[2].value.as < std::vector<literal_ptr> > ().push_back(std::move(yystack_[0].value.as < literal_ptr > ()));
            yylhs.value.as < std::vector<literal_ptr> > () = std::move(yystack_[2].value.as < std::vector<literal_ptr> > ());
        }
#line 1967 "parser.cpp"
    break;

  case 72: // size_patterns: LABEL TSEP SQ_LBRA SQ_LBRA
#line 467 "src/parser.y"
        { 
            yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{}; 
            yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[3].value.as < std::string > ()));
        }
#line 1976 "parser.cpp"
    break;

  case 73: // size_patterns: size_pattern_two
#line 471 "src/parser.y"
                       { yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[0].value.as < std::vector<std::string> > ()); }
#line 1982 "parser.cpp"
    break;

  case 74: // size_pattern_two: LABEL TSEP LABEL
#line 476 "src/parser.y"
        { 
            yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{};
            yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[2].value.as < std::string > ()));
            yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ())); 
        }
#line 1992 "parser.cpp"
    break;

  case 75: // size_pattern_two: size_pattern_two TSEP LABEL
#line 481 "src/parser.y"
                                  {
        yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));
        yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ());
    }
#line 2001 "parser.cpp"
    break;

  case 76: // return_expr: RETURN value_expr
#line 488 "src/parser.y"
                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2007 "parser.cpp"
    break;

  case 77: // helpers: %empty
#line 491 "src/parser.y"
             { yylhs.value.as < std::vector<decl_ptr> > () = std::vector<decl_ptr>{}; }
#line 2013 "parser.cpp"
    break;

  case 78: // helpers: helpers helper_expr
#line 493 "src/parser.y"
        {
            yystack_[1].value.as < std::vector<decl_ptr> > ().push_back(std::move(yystack_[0].value.as < decl_ptr > ()));
            yylhs.value.as < std::vector<decl_ptr> > () = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
        }
#line 2022 "parser.cpp"
    break;

  case 79: // helper_expr: assign_expr
#line 500 "src/parser.y"
                  { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < var_decl_ptr > ()); }
#line 2028 "parser.cpp"
    break;

  case 80: // helper_expr: print_expr
#line 501 "src/parser.y"
                 { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < print_ptr > ()); }
#line 2034 "parser.cpp"
    break;

  case 81: // helper_expr: read_expr
#line 502 "src/parser.y"
                { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < read_ptr > ()); }
#line 2040 "parser.cpp"
    break;

  case 82: // print_expr: PRINT LBRA value_expr RBRA
#line 507 "src/parser.y"
        { 
            yylhs.value.as < print_ptr > () = std::make_unique<PrintNode>();
            yylhs.value.as < print_ptr > ()->msg = std::move(yystack_[1].value.as < expr_ptr > ());
        }
#line 2049 "parser.cpp"
    break;

  case 83: // read_expr: LABEL TSEP type ASSGN READ LBRA RBRA
#line 515 "src/parser.y"
        {
            yylhs.value.as < read_ptr > () = std::make_unique<ReadNode>();
            yylhs.value.as < read_ptr > ()->name = std::move(yystack_[6].value.as < std::string > ());
            yylhs.value.as < read_ptr > ()->type = std::move(yystack_[4].value.as < type_ptr > ());
        }
#line 2059 "parser.cpp"
    break;

  case 84: // assign_expr: LABEL TSEP type LBRA program RBRA
#line 524 "src/parser.y"
        { 
            yylhs.value.as < var_decl_ptr > () = std::make_unique<VarDecl>();
            yylhs.value.as < var_decl_ptr > ()->name = std::move(yystack_[5].value.as < std::string > ());
            yylhs.value.as < var_decl_ptr > ()->type = std::move(yystack_[3].value.as < type_ptr > ());
            yylhs.value.as < var_decl_ptr > ()->r_val = std::move(yystack_[1].value.as < prog_ptr > ());
        }
#line 2070 "parser.cpp"
    break;

  case 85: // assign_expr: LABEL TSEP type ASSGN value_expr
#line 531 "src/parser.y"
        {
            yylhs.value.as < var_decl_ptr > () = std::make_unique<VarDecl>();
            yylhs.value.as < var_decl_ptr > ()->name = std::move(yystack_[4].value.as < std::string > ());
            yylhs.value.as < var_decl_ptr > ()->type = std::move(yystack_[2].value.as < type_ptr > ());
            yylhs.value.as < var_decl_ptr > ()->r_val = std::move(yystack_[0].value.as < expr_ptr > ());
        }
#line 2081 "parser.cpp"
    break;

  case 86: // int_lit: INT
#line 541 "src/parser.y"
        { 
            auto temp = std::make_unique<IntLit>();
            temp->value = yystack_[0].value.as < uint64_t > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 2091 "parser.cpp"
    break;

  case 87: // float_lit: FLOAT
#line 549 "src/parser.y"
        {
            auto temp = std::make_unique<IntLit>();
            temp->value = yystack_[0].value.as < double > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 2101 "parser.cpp"
    break;

  case 88: // bool_lit: TRUE
#line 557 "src/parser.y"
        { 
            auto temp = std::make_unique<BoolLit>();
            temp->value = true;
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 2111 "parser.cpp"
    break;

  case 89: // bool_lit: FALSE
#line 563 "src/parser.y"
        { 
            auto temp = std::make_unique<BoolLit>();
            temp->value = false;
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 2121 "parser.cpp"
    break;

  case 90: // char_lit: CHAR
#line 572 "src/parser.y"
        { 
            auto temp = std::make_unique<CharLit>();
            temp->value = yystack_[0].value.as < char > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 2131 "parser.cpp"
    break;

  case 91: // bool_op: BOR
#line 579 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::BOR; }
#line 2137 "parser.cpp"
    break;

  case 92: // bool_op: BAND
#line 580 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::BAND; }
#line 2143 "parser.cpp"
    break;

  case 93: // comp_op: CEQ
#line 584 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CEQ; }
#line 2149 "parser.cpp"
    break;

  case 94: // comp_op: CNEQ
#line 585 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CNEQ; }
#line 2155 "parser.cpp"
    break;

  case 95: // comp_op: CGT
#line 586 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CGT; }
#line 2161 "parser.cpp"
    break;

  case 96: // comp_op: CLT
#line 587 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CLT; }
#line 2167 "parser.cpp"
    break;

  case 97: // comp_op: CGEQ
#line 588 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CGEQ; }
#line 2173 "parser.cpp"
    break;

  case 98: // comp_op: CLEQ
#line 589 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CLEQ; }
#line 2179 "parser.cpp"
    break;

  case 99: // bitwise_op: LAND
#line 593 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::LAND; }
#line 2185 "parser.cpp"
    break;

  case 100: // bitwise_op: BAR
#line 594 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LOR; }
#line 2191 "parser.cpp"
    break;

  case 101: // bitwise_op: LXOR
#line 595 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::LXOR; }
#line 2197 "parser.cpp"
    break;

  case 102: // shift_op: LSL
#line 598 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LSL; }
#line 2203 "parser.cpp"
    break;

  case 103: // shift_op: LSR
#line 599 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LSR; }
#line 2209 "parser.cpp"
    break;

  case 104: // additive_op: ADD
#line 602 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::ADD; }
#line 2215 "parser.cpp"
    break;

  case 105: // additive_op: SUB
#line 603 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::SUB; }
#line 2221 "parser.cpp"
    break;

  case 106: // additive_op: CONCAT
#line 604 "src/parser.y"
             { yylhs.value.as < BinaryOp > () = BinaryOp::CONCAT; }
#line 2227 "parser.cpp"
    break;

  case 107: // mult_op: MUL
#line 608 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::MUL; }
#line 2233 "parser.cpp"
    break;

  case 108: // mult_op: DIV
#line 609 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::DIV; }
#line 2239 "parser.cpp"
    break;

  case 109: // mult_op: MOD
#line 610 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::MOD; }
#line 2245 "parser.cpp"
    break;

  case 110: // mult_op: FLR
#line 611 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::FLR; }
#line 2251 "parser.cpp"
    break;

  case 111: // unary_op: BNOT
#line 615 "src/parser.y"
           { yylhs.value.as < UnaryOp > () = UnaryOp::BNOT; }
#line 2257 "parser.cpp"
    break;

  case 112: // unary_op: LNEG
#line 616 "src/parser.y"
           { yylhs.value.as < UnaryOp > () = UnaryOp::LNEG; }
#line 2263 "parser.cpp"
    break;

  case 113: // unary_op: SUB
#line 617 "src/parser.y"
          { yylhs.value.as < UnaryOp > () = UnaryOp::MINUS; }
#line 2269 "parser.cpp"
    break;

  case 114: // nominal_expr: LABEL
#line 622 "src/parser.y"
        { 
            auto temp = std::make_unique<NominalNode>();
            temp->label = std::move(yystack_[0].value.as < std::string > ()); 
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2279 "parser.cpp"
    break;

  case 115: // list_expr: empty_list
#line 629 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < list_ptr > ()); }
#line 2285 "parser.cpp"
    break;

  case 116: // list_expr: list_con
#line 630 "src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < list_ptr > ()); }
#line 2291 "parser.cpp"
    break;

  case 117: // list_expr: string_lit
#line 631 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2297 "parser.cpp"
    break;

  case 118: // empty_list: SQ_LBRA SQ_RBRA
#line 635 "src/parser.y"
                      { yylhs.value.as < list_ptr > () = std::make_unique<ListNode>(); yylhs.value.as < list_ptr > ()->elems = std::vector<expr_ptr>{}; }
#line 2303 "parser.cpp"
    break;

  case 119: // list_con: SQ_LBRA expr_list SQ_RBRA
#line 639 "src/parser.y"
        { yylhs.value.as < list_ptr > () = std::make_unique<ListNode>(); yylhs.value.as < list_ptr > ()->elems = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ()); }
#line 2309 "parser.cpp"
    break;

  case 120: // expr_list: value_expr
#line 643 "src/parser.y"
        { 
            yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>{};
            yylhs.value.as < std::vector<expr_ptr> > ().push_back(std::move(yystack_[0].value.as < expr_ptr > ())); 
        }
#line 2318 "parser.cpp"
    break;

  case 121: // expr_list: expr_list COMMA value_expr
#line 648 "src/parser.y"
        {
            yystack_[2].value.as < std::vector<expr_ptr> > ().push_back(std::move(yystack_[0].value.as < expr_ptr > ()));
            yylhs.value.as < std::vector<expr_ptr> > () = std::move(yystack_[2].value.as < std::vector<expr_ptr> > ());
        }
#line 2327 "parser.cpp"
    break;

  case 122: // param_expr: LABEL LBRA RBRA
#line 656 "src/parser.y"
        {
            auto temp = std::make_unique<ParamNode>();
            temp->label = std::move(yystack_[2].value.as < std::string > ());
            temp->params = std::vector<expr_ptr>{};
            temp->kind = ParamKind::FUNC_CALL;
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2339 "parser.cpp"
    break;

  case 123: // param_expr: LABEL LBRA expr_list RBRA
#line 664 "src/parser.y"
        {
            auto temp = std::make_unique<ParamNode>(); 
            temp->label = std::move(yystack_[3].value.as < std::string > ());
            temp->params = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2350 "parser.cpp"
    break;

  case 124: // value_expr: bool_expr
#line 673 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2356 "parser.cpp"
    break;

  case 125: // bool_expr: comp_expr
#line 676 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2362 "parser.cpp"
    break;

  case 126: // bool_expr: bool_expr bool_op comp_expr
#line 678 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2374 "parser.cpp"
    break;

  case 127: // comp_expr: bitwise_expr
#line 688 "src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2380 "parser.cpp"
    break;

  case 128: // comp_expr: bitwise_expr comp_op bitwise_expr
#line 690 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2392 "parser.cpp"
    break;

  case 129: // bitwise_expr: shift_expr
#line 700 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2398 "parser.cpp"
    break;

  case 130: // bitwise_expr: bitwise_expr bitwise_op shift_expr
#line 702 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2410 "parser.cpp"
    break;

  case 131: // shift_expr: additive_expr
#line 712 "src/parser.y"
                    { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2416 "parser.cpp"
    break;

  case 132: // shift_expr: shift_expr shift_op additive_expr
#line 714 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2428 "parser.cpp"
    break;

  case 133: // additive_expr: mult_expr
#line 724 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2434 "parser.cpp"
    break;

  case 134: // additive_expr: additive_expr additive_op mult_expr
#line 726 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2446 "parser.cpp"
    break;

  case 135: // mult_expr: pow_expr
#line 736 "src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2452 "parser.cpp"
    break;

  case 136: // mult_expr: mult_expr mult_op pow_expr
#line 738 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2464 "parser.cpp"
    break;

  case 137: // pow_expr: unary_expr
#line 748 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2470 "parser.cpp"
    break;

  case 138: // pow_expr: unary_expr POW pow_expr
#line 750 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = BinaryOp::POW;
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2482 "parser.cpp"
    break;

  case 139: // unary_expr: postfix_expr
#line 760 "src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2488 "parser.cpp"
    break;

  case 140: // unary_expr: unary_op postfix_expr
#line 762 "src/parser.y"
        {
            auto temp = std::make_unique<UnaryNode>();
            temp->op = yystack_[1].value.as < UnaryOp > ();
            temp->exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2499 "parser.cpp"
    break;

  case 141: // postfix_expr: literal_expr
#line 771 "src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2505 "parser.cpp"
    break;

  case 142: // postfix_expr: postfix_expr SQ_LBRA value_expr SQ_RBRA
#line 773 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = BinaryOp::INDEX;
            temp->l_exp = std::move(yystack_[3].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[1].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2517 "parser.cpp"
    break;

  case 143: // postfix_expr: postfix_expr DOT LABEL
#line 781 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();

            auto fnode = std::make_unique<FieldNode>();
            fnode->field = std::move(yystack_[0].value.as < std::string > ());

            temp->op = BinaryOp::ACCESS;
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(fnode);
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2533 "parser.cpp"
    break;

  case 144: // literal_expr: int_lit
#line 795 "src/parser.y"
              { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2539 "parser.cpp"
    break;

  case 145: // literal_expr: float_lit
#line 796 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2545 "parser.cpp"
    break;

  case 146: // literal_expr: char_lit
#line 797 "src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2551 "parser.cpp"
    break;

  case 147: // literal_expr: bool_lit
#line 798 "src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2557 "parser.cpp"
    break;

  case 148: // literal_expr: list_expr
#line 799 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2563 "parser.cpp"
    break;

  case 149: // literal_expr: nominal_expr
#line 800 "src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2569 "parser.cpp"
    break;

  case 150: // literal_expr: param_expr
#line 801 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2575 "parser.cpp"
    break;

  case 151: // literal_expr: LBRA value_expr RBRA
#line 802 "src/parser.y"
                           { yylhs.value.as < expr_ptr > () = std::move(yystack_[1].value.as < expr_ptr > ()); }
#line 2581 "parser.cpp"
    break;


#line 2585 "parser.cpp"

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









  const short parser::yypact_ninf_ = -190;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
    -190,    12,    96,  -190,  -190,    17,    29,    38,  -190,  -190,
    -190,  -190,    22,    31,    40,    82,    87,    90,    74,   101,
      72,  -190,    83,     7,  -190,  -190,  -190,    13,   233,    97,
      82,   233,  -190,    87,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,   233,   233,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,   233,  -190,  -190,  -190,   103,   105,  -190,   102,
    -190,    84,   233,  -190,  -190,    95,   233,  -190,   111,   139,
     138,   123,   138,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,   233,   119,  -190,  -190,  -190,  -190,   128,  -190,
    -190,   138,    10,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,   219,  -190,  -190,  -190,  -190,  -190,   155,    55,  -190,
     220,     6,   -35,   118,  -190,   121,    15,  -190,   138,  -190,
      -4,   126,    70,   136,  -190,    39,  -190,    15,   135,  -190,
    -190,   138,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,   138,   138,  -190,  -190,   138,  -190,  -190,  -190,   138,
    -190,  -190,  -190,  -190,   138,   138,   138,   167,   145,  -190,
      75,   122,   -15,  -190,  -190,    14,  -190,  -190,   138,   202,
    -190,    37,     6,   -35,   118,  -190,  -190,   144,  -190,  -190,
     147,   150,  -190,   124,   132,   126,  -190,  -190,  -190,   146,
    -190,  -190,   186,   -14,  -190,  -190,   133,  -190,  -190,  -190,
    -190,  -190,   148,  -190,  -190,  -190,  -190,  -190,  -190,   154,
    -190,  -190,  -190,     4,  -190,  -190,    88,   202,  -190,  -190,
     173,  -190,  -190,  -190,  -190,   165,  -190,   224,  -190,  -190,
    -190,  -190,  -190
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     1,     2,     0,     0,     0,     4,     5,
       6,     7,     0,     0,     0,    27,     0,     0,     0,     0,
      28,    29,     0,     0,    33,    37,    38,     0,     0,     0,
       0,     0,    36,     0,    40,    39,    26,    20,    21,    22,
      23,    16,    17,     8,     0,    31,    12,    18,    19,    13,
      14,    15,     0,    30,    35,    34,     0,     9,    10,     0,
      77,     0,     0,    24,    32,     0,     0,    11,     0,     0,
       0,     0,     0,    41,    43,    44,    42,    78,    80,    81,
      79,    25,     0,     0,    86,    87,    90,    68,   114,    88,
      89,     0,     0,   113,   112,   111,   117,   144,   145,   147,
     146,     0,   149,   148,   115,   116,   150,     0,   124,   125,
     127,   129,   131,   133,   135,   137,   139,   141,     0,    76,
       0,     0,     0,     0,   118,     0,   120,   140,     0,    92,
      91,     0,    99,   100,   101,    95,    96,    97,    98,    93,
      94,     0,     0,   102,   103,     0,   104,   105,   106,     0,
     107,   108,   109,   110,     0,     0,     0,     0,     0,    77,
       0,     0,     0,    46,   122,     0,   151,   119,     0,     0,
     126,   128,   130,   132,   134,   136,   138,     0,   143,    82,
       0,     0,    85,     0,     0,     0,    45,   123,   121,    63,
      62,    61,     0,     0,    51,    60,     0,    58,    59,    66,
      65,    67,    73,    55,    56,    57,    54,   142,    84,     0,
      77,    77,    47,     0,    64,    70,     0,     0,    50,    77,
       0,    83,    49,    48,    74,     0,    69,     0,    52,    53,
      75,    72,    71
  };

  const short
  parser::yypgoto_[] =
  {
    -190,  -190,  -190,  -190,  -190,  -190,   106,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,  -190,   169,  -190,  -190,   152,  -190,
     170,  -190,  -190,  -158,  -190,  -190,  -190,    16,  -190,  -190,
     -17,  -189,  -190,  -190,  -190,  -163,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,  -190,  -190,  -162,  -161,  -160,  -159,
    -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,    80,  -190,   -70,  -190,    79,    73,    69,    68,    66,
     -32,  -190,   115,  -190
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     1,     2,     8,    56,    57,    45,    46,    47,    48,
      49,    50,    51,    19,    20,    21,     9,    23,    24,    10,
      26,    27,    11,    64,    73,    74,   162,   163,    75,   193,
     194,   195,   196,   197,   198,    96,   200,   216,   201,   202,
      76,    65,    77,    78,    79,    80,    97,    98,    99,   100,
     131,   141,   142,   145,   149,   154,   101,   102,   103,   104,
     105,   125,   106,   126,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117
  };

  const unsigned char
  parser::yytable_[] =
  {
     107,   180,   119,   215,   146,   147,   199,   203,   204,   205,
     206,   224,     3,    84,    85,    86,    87,    88,   185,   217,
      25,   123,   186,   218,    12,   159,   148,    89,    90,   199,
     203,   204,   205,   206,   160,   225,    13,    32,   232,    91,
      33,    92,   124,    34,   187,    14,   156,   168,   158,   157,
      93,    15,   222,   223,   199,   203,   204,   205,   206,    94,
      16,   229,   143,   144,   199,   203,   204,   205,   206,    17,
      95,   167,   168,    84,    85,    86,    87,    88,    84,    85,
      86,    87,    88,   132,   133,   134,   177,    89,    90,    18,
     182,   184,    89,    90,    22,   181,     4,    25,   188,    91,
     164,    92,    68,    69,    91,    30,    92,     5,    70,    28,
      93,     6,     7,   129,   130,    93,    71,    72,    31,    94,
     226,   227,   175,   176,    94,    84,    85,    86,    87,    88,
      95,    29,    52,    61,    63,    95,   183,    54,    62,    89,
      90,    84,    85,    86,    87,    88,    82,    66,    83,    58,
      59,    91,   118,    92,   121,    89,    90,   122,    60,   150,
     151,   152,    93,   153,   128,   155,   166,    91,    67,    92,
     169,    94,    81,   161,   178,   179,   207,   208,    93,   209,
     230,   213,    95,   220,   221,    55,   210,    94,   120,    84,
      85,    86,    87,   189,   211,   219,   231,    35,    95,    53,
     228,   212,   165,    89,    90,    84,    85,    86,    87,   189,
     170,   172,   190,   173,   171,   174,   127,   192,   214,    89,
      90,   191,    84,    85,    86,    87,    88,    84,    85,    86,
      87,   189,     0,   192,     0,     0,    89,    90,     0,     0,
      36,    89,    90,     0,     0,     0,     0,     0,    91,     0,
      92,     0,     0,     0,     0,   192,    37,    38,    39,    40,
      41,    42,    43,     0,    44,     0,   132,   133,   134,     0,
     135,   136,   137,   138,   139,   140
  };

  const short
  parser::yycheck_[] =
  {
      70,   159,    72,   192,    39,    40,   169,   169,   169,   169,
     169,     7,     0,     3,     4,     5,     6,     7,    33,    33,
       7,    91,    37,    37,     7,    29,    61,    17,    18,   192,
     192,   192,   192,   192,    38,    31,     7,    30,   227,    29,
      33,    31,    32,    30,    30,     7,    31,    33,   118,    34,
      40,    29,   210,   211,   217,   217,   217,   217,   217,    49,
      29,   219,    56,    57,   227,   227,   227,   227,   227,    29,
      60,    32,    33,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,    46,    47,    48,   156,    17,    18,     7,
     160,   161,    17,    18,     7,    20,     0,     7,   168,    29,
      30,    31,     7,     8,    29,    33,    31,    11,    13,    35,
      40,    15,    16,    58,    59,    40,    21,    22,    35,    49,
      32,    33,   154,   155,    49,     3,     4,     5,     6,     7,
      60,    30,    35,    30,    32,    60,    14,    31,    33,    17,
      18,     3,     4,     5,     6,     7,    35,    63,     9,    43,
      44,    29,    29,    31,    35,    17,    18,    29,    52,    41,
      42,    43,    40,    45,     9,    44,    30,    29,    62,    31,
      35,    49,    66,    47,     7,    30,    32,    30,    40,    29,
       7,    35,    60,    35,    30,    33,    62,    49,    82,     3,
       4,     5,     6,     7,    62,    62,    31,    27,    60,    30,
     217,   185,   122,    17,    18,     3,     4,     5,     6,     7,
     131,   142,    10,   145,   141,   149,   101,    31,    32,    17,
      18,    19,     3,     4,     5,     6,     7,     3,     4,     5,
       6,     7,    -1,    31,    -1,    -1,    17,    18,    -1,    -1,
       7,    17,    18,    -1,    -1,    -1,    -1,    -1,    29,    -1,
      31,    -1,    -1,    -1,    -1,    31,    23,    24,    25,    26,
      27,    28,    29,    -1,    31,    -1,    46,    47,    48,    -1,
      50,    51,    52,    53,    54,    55
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    65,    66,     0,     0,    11,    15,    16,    67,    80,
      83,    86,     7,     7,     7,    29,    29,    29,     7,    77,
      78,    79,     7,    81,    82,     7,    84,    85,    35,    30,
      33,    35,    30,    33,    30,    84,     7,    23,    24,    25,
      26,    27,    28,    29,    31,    70,    71,    72,    73,    74,
      75,    76,    35,    79,    70,    82,    68,    69,    70,    70,
      70,    30,    33,    32,    87,   105,    63,    70,     7,     8,
      13,    21,    22,    88,    89,    92,   104,   106,   107,   108,
     109,    70,    35,     9,     3,     4,     5,     6,     7,    17,
      18,    29,    31,    40,    49,    60,    99,   110,   111,   112,
     113,   120,   121,   122,   123,   124,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,    29,   127,
      70,    35,    29,   127,    32,   125,   127,   136,     9,    58,
      59,   114,    46,    47,    48,    50,    51,    52,    53,    54,
      55,   115,   116,    56,    57,   117,    39,    40,    61,   118,
      41,    42,    43,    45,   119,    44,    31,    34,   127,    29,
      38,    47,    90,    91,    30,   125,    30,    32,    33,    35,
     129,   130,   131,   132,   133,   134,   134,   127,     7,    30,
      87,    20,   127,    14,   127,    33,    37,    30,   127,     7,
      10,    19,    31,    93,    94,    95,    96,    97,    98,    99,
     100,   102,   103,   110,   111,   112,   113,    32,    30,    29,
      62,    62,    91,    35,    32,    95,   101,    33,    37,    62,
      35,    30,    87,    87,     7,    31,    32,    33,    94,    87,
       7,    31,    95
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    64,    65,    66,    66,    67,    67,    67,    68,    68,
      69,    69,    70,    70,    70,    70,    71,    71,    71,    71,
      72,    72,    73,    73,    74,    75,    76,    77,    77,    78,
      78,    79,    80,    81,    81,    82,    83,    84,    85,    85,
      86,    87,    88,    88,    88,    89,    90,    90,    91,    91,
      92,    93,    93,    94,    95,    95,    95,    95,    95,    95,
      96,    96,    96,    97,    98,    98,    98,    98,    99,   100,
     101,   101,   102,   102,   103,   103,   104,   105,   105,   106,
     106,   106,   107,   108,   109,   109,   110,   111,   112,   112,
     113,   114,   114,   115,   115,   115,   115,   115,   115,   116,
     116,   116,   117,   117,   118,   118,   118,   119,   119,   119,
     119,   120,   120,   120,   121,   122,   122,   122,   123,   124,
     125,   125,   126,   126,   127,   128,   128,   129,   129,   130,
     130,   131,   131,   132,   132,   133,   133,   134,   134,   135,
     135,   136,   136,   136,   137,   137,   137,   137,   137,   137,
     137,   137
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     2,     1,     1,     1,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     5,     1,     0,     1,     1,
       3,     3,     8,     1,     3,     3,     5,     1,     1,     2,
       5,     2,     1,     1,     1,     5,     1,     3,     4,     4,
       6,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     3,
       1,     3,     4,     1,     3,     3,     2,     0,     2,     1,
       1,     1,     4,     7,     6,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       1,     3,     3,     4,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       2,     1,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     3
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
  "RBRA", "SQ_LBRA", "SQ_RBRA", "COMMA", "DOT", "TSEP", "EMPTY", "PEND",
  "ASSGN", "ADD", "SUB", "MUL", "DIV", "MOD", "POW", "FLR", "LAND", "BAR",
  "LXOR", "LNEG", "CGT", "CLT", "CGEQ", "CLEQ", "CEQ", "CNEQ", "LSL",
  "LSR", "BAND", "BOR", "BNOT", "CONCAT", "ARROW", "PROD", "$accept",
  "module", "definitions", "definition", "opt_types", "types", "type",
  "literal_type", "int_lit_type", "float_lit_type", "list_type",
  "func_type", "nominal_type", "opt_params", "params", "param",
  "function_def", "fields", "field", "struct_def", "evar", "evars",
  "enum_def", "program", "branch_expr", "guard_expr", "guards", "guard",
  "case_expr", "patterns", "pattern_branch", "literal", "pattern",
  "enum_lit", "list_pattern", "string_lit", "list_lit", "list_pattern_lit",
  "size_patterns", "size_pattern_two", "return_expr", "helpers",
  "helper_expr", "print_expr", "read_expr", "assign_expr", "int_lit",
  "float_lit", "bool_lit", "char_lit", "bool_op", "comp_op", "bitwise_op",
  "shift_op", "additive_op", "mult_op", "unary_op", "nominal_expr",
  "list_expr", "empty_list", "list_con", "expr_list", "param_expr",
  "value_expr", "bool_expr", "comp_expr", "bitwise_expr", "shift_expr",
  "additive_expr", "mult_expr", "pow_expr", "unary_expr", "postfix_expr",
  "literal_expr", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   173,   173,   181,   183,   191,   192,   193,   196,   197,
     200,   201,   207,   208,   209,   210,   214,   215,   216,   217,
     221,   222,   225,   226,   229,   232,   235,   238,   239,   242,
     243,   250,   259,   270,   272,   280,   288,   297,   300,   301,
     309,   318,   327,   328,   329,   333,   341,   346,   354,   360,
     371,   380,   385,   393,   402,   403,   404,   405,   406,   407,
     411,   412,   413,   417,   425,   431,   432,   433,   442,   445,
     453,   458,   466,   471,   475,   481,   488,   491,   492,   500,
     501,   502,   506,   514,   523,   530,   540,   548,   556,   562,
     571,   579,   580,   584,   585,   586,   587,   588,   589,   593,
     594,   595,   598,   599,   602,   603,   604,   608,   609,   610,
     611,   615,   616,   617,   621,   629,   630,   631,   635,   638,
     642,   647,   655,   663,   673,   676,   677,   688,   689,   700,
     701,   712,   713,   724,   725,   736,   737,   748,   749,   760,
     761,   771,   772,   780,   795,   796,   797,   798,   799,   800,
     801,   802
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


#line 32 "src/parser.y"
} // yy
#line 3089 "parser.cpp"

