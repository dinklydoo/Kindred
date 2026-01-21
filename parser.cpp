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
#line 142 "parser.cpp"

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
    : super_type (YY_MOVE (that.state))
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

      case symbol_kind::S_assign_expr: // assign_expr
        value.YY_MOVE_OR_COPY< bin_ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_helper_expr: // helper_expr
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
        value.YY_MOVE_OR_COPY< std::vector<decl_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_helpers: // helpers
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

      case symbol_kind::S_var_decl: // var_decl
        value.YY_MOVE_OR_COPY< var_ptr > (YY_MOVE (that.value));
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
    : super_type (s)
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

      case symbol_kind::S_assign_expr: // assign_expr
        value.move< bin_ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_helper_expr: // helper_expr
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
        value.move< std::vector<decl_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_helpers: // helpers
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

      case symbol_kind::S_var_decl: // var_decl
        value.move< var_ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_assign_expr: // assign_expr
        value.copy< bin_ptr > (that.value);
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
      case symbol_kind::S_helper_expr: // helper_expr
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
        value.copy< std::vector<decl_ptr> > (that.value);
        break;

      case symbol_kind::S_helpers: // helpers
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

      case symbol_kind::S_var_decl: // var_decl
        value.copy< var_ptr > (that.value);
        break;

      default:
        break;
    }

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

      case symbol_kind::S_assign_expr: // assign_expr
        value.move< bin_ptr > (that.value);
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
      case symbol_kind::S_helper_expr: // helper_expr
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
        value.move< std::vector<decl_ptr> > (that.value);
        break;

      case symbol_kind::S_helpers: // helpers
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

      case symbol_kind::S_var_decl: // var_decl
        value.move< var_ptr > (that.value);
        break;

      default:
        break;
    }

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
            << ' ' << yysym.name () << " (";
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

      case symbol_kind::S_assign_expr: // assign_expr
        yylhs.value.emplace< bin_ptr > ();
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
      case symbol_kind::S_helper_expr: // helper_expr
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
        yylhs.value.emplace< std::vector<decl_ptr> > ();
        break;

      case symbol_kind::S_helpers: // helpers
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

      case symbol_kind::S_var_decl: // var_decl
        yylhs.value.emplace< var_ptr > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // module: definitions
#line 174 "src/parser.y"
        { 
            yylhs.value.as < module_ptr > () = std::make_unique<ModuleNode>();
            yylhs.value.as < module_ptr > ()->decl = std::move(yystack_[0].value.as < std::vector<decl_ptr> > ());
        }
#line 1446 "parser.cpp"
    break;

  case 3: // definitions: %empty
#line 182 "src/parser.y"
        { yylhs.value.as < std::vector<decl_ptr> > () = std::vector<decl_ptr>{}; }
#line 1452 "parser.cpp"
    break;

  case 4: // definitions: definitions definition
#line 184 "src/parser.y"
        { 
            yystack_[1].value.as < std::vector<decl_ptr> > ().push_back(std::move(yystack_[0].value.as < decl_ptr > ()));
            yylhs.value.as < std::vector<decl_ptr> > () = std::move(yystack_[1].value.as < std::vector<decl_ptr> > ());
        }
#line 1461 "parser.cpp"
    break;

  case 5: // definition: function_def
#line 191 "src/parser.y"
                  { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < func_decl_ptr > ()); }
#line 1467 "parser.cpp"
    break;

  case 6: // definition: struct_def
#line 192 "src/parser.y"
                { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < struct_decl_ptr > ()); }
#line 1473 "parser.cpp"
    break;

  case 7: // definition: enum_def
#line 193 "src/parser.y"
              { yylhs.value.as < decl_ptr > () = std::move(yystack_[0].value.as < enum_decl_ptr > ()); }
#line 1479 "parser.cpp"
    break;

  case 8: // opt_types: %empty
#line 196 "src/parser.y"
             { yylhs.value.as < std::vector<type_ptr> > () = std::vector<type_ptr>{}; }
#line 1485 "parser.cpp"
    break;

  case 9: // opt_types: types
#line 197 "src/parser.y"
            { yylhs.value.as < std::vector<type_ptr> > () = std::move(yystack_[0].value.as < std::vector<type_ptr> > ()); }
#line 1491 "parser.cpp"
    break;

  case 10: // types: type
#line 200 "src/parser.y"
           { yylhs.value.as < std::vector<type_ptr> > () = std::vector<type_ptr>{yystack_[0].value.as < type_ptr > ()}; }
#line 1497 "parser.cpp"
    break;

  case 11: // types: types COMMA type
#line 201 "src/parser.y"
                       {
        yystack_[2].value.as < std::vector<type_ptr> > ().push_back(std::move(yystack_[0].value.as < type_ptr > ()));
        yylhs.value.as < std::vector<type_ptr> > () = std::move(yystack_[2].value.as < std::vector<type_ptr> > ());
    }
#line 1506 "parser.cpp"
    break;

  case 12: // type: literal_type
#line 207 "src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1512 "parser.cpp"
    break;

  case 13: // type: list_type
#line 208 "src/parser.y"
                { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1518 "parser.cpp"
    break;

  case 14: // type: func_type
#line 209 "src/parser.y"
                { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1524 "parser.cpp"
    break;

  case 15: // type: nominal_type
#line 210 "src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1530 "parser.cpp"
    break;

  case 16: // literal_type: T_CHAR
#line 214 "src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.char_type(); }
#line 1536 "parser.cpp"
    break;

  case 17: // literal_type: T_BOOL
#line 215 "src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.bool_type(); }
#line 1542 "parser.cpp"
    break;

  case 18: // literal_type: int_lit_type
#line 216 "src/parser.y"
                   { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1548 "parser.cpp"
    break;

  case 19: // literal_type: float_lit_type
#line 217 "src/parser.y"
                     { yylhs.value.as < type_ptr > () = std::move(yystack_[0].value.as < type_ptr > ()); }
#line 1554 "parser.cpp"
    break;

  case 20: // int_lit_type: T_INT
#line 221 "src/parser.y"
            { yylhs.value.as < type_ptr > () = type_s.int_type(); }
#line 1560 "parser.cpp"
    break;

  case 21: // int_lit_type: T_LONG
#line 222 "src/parser.y"
             { yylhs.value.as < type_ptr > () = type_s.long_type(); }
#line 1566 "parser.cpp"
    break;

  case 22: // float_lit_type: T_FLOAT
#line 225 "src/parser.y"
              { yylhs.value.as < type_ptr > () = type_s.float_type(); }
#line 1572 "parser.cpp"
    break;

  case 23: // float_lit_type: T_DOUBLE
#line 226 "src/parser.y"
               { yylhs.value.as < type_ptr > () = type_s.double_type(); }
#line 1578 "parser.cpp"
    break;

  case 24: // list_type: SQ_LBRA type SQ_RBRA
#line 229 "src/parser.y"
                           { yylhs.value.as < type_ptr > () = type_s.list_type(yystack_[1].value.as < type_ptr > ()); }
#line 1584 "parser.cpp"
    break;

  case 25: // func_type: LBRA opt_types RBRA PROD type
#line 232 "src/parser.y"
                                    { yylhs.value.as < type_ptr > () = type_s.func_type(yystack_[3].value.as < std::vector<type_ptr> > (), yystack_[0].value.as < type_ptr > ()); }
#line 1590 "parser.cpp"
    break;

  case 26: // nominal_type: LABEL
#line 235 "src/parser.y"
            { yylhs.value.as < type_ptr > () = type_s.nominal_type(yystack_[0].value.as < std::string > ()); }
#line 1596 "parser.cpp"
    break;

  case 27: // opt_params: %empty
#line 238 "src/parser.y"
             { yylhs.value.as < std::vector<Param> > () = std::vector<Param>{}; }
#line 1602 "parser.cpp"
    break;

  case 28: // opt_params: params
#line 239 "src/parser.y"
             { yylhs.value.as < std::vector<Param> > () = std::move(yystack_[0].value.as < std::vector<Param> > ()); }
#line 1608 "parser.cpp"
    break;

  case 29: // params: param
#line 242 "src/parser.y"
            { yylhs.value.as < std::vector<Param> > () = std::vector<Param>{yystack_[0].value.as < Param > ()}; }
#line 1614 "parser.cpp"
    break;

  case 30: // params: params COMMA param
#line 244 "src/parser.y"
        {
            yystack_[2].value.as < std::vector<Param> > ().push_back(std::move(yystack_[0].value.as < Param > ()));
            yylhs.value.as < std::vector<Param> > () = std::move(yystack_[2].value.as < std::vector<Param> > ());
        }
#line 1623 "parser.cpp"
    break;

  case 31: // param: LABEL TSEP type
#line 251 "src/parser.y"
        { 
            yylhs.value.as < Param > () = Param(); 
            yylhs.value.as < Param > ().name = std::move(yystack_[2].value.as < std::string > ());
            yylhs.value.as < Param > ().type = std::move(yystack_[0].value.as < type_ptr > ());
        }
#line 1633 "parser.cpp"
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
#line 1645 "parser.cpp"
    break;

  case 33: // fields: field
#line 271 "src/parser.y"
        {   yylhs.value.as < std::vector<Field> > () = std::vector<Field>{}; yylhs.value.as < std::vector<Field> > ().push_back(std::move(yystack_[0].value.as < Field > ())); }
#line 1651 "parser.cpp"
    break;

  case 34: // fields: fields COMMA field
#line 273 "src/parser.y"
        { 
            yystack_[2].value.as < std::vector<Field> > ().push_back(std::move(yystack_[0].value.as < Field > ()));
            yylhs.value.as < std::vector<Field> > () = std::move(yystack_[2].value.as < std::vector<Field> > ());
        }
#line 1660 "parser.cpp"
    break;

  case 35: // field: LABEL TSEP type
#line 281 "src/parser.y"
        {
            yylhs.value.as < Field > () = Field();
            yylhs.value.as < Field > ().name = std::move(yystack_[2].value.as < std::string > ());
            yylhs.value.as < Field > ().type = std::move(yystack_[0].value.as < type_ptr > ());
        }
#line 1670 "parser.cpp"
    break;

  case 36: // struct_def: STRUCT LABEL LBRA fields RBRA
#line 289 "src/parser.y"
        {
            yylhs.value.as < struct_decl_ptr > () = std::make_unique<StructDecl>();
            yylhs.value.as < struct_decl_ptr > ()->name = std::move(yystack_[3].value.as < std::string > ());
            yylhs.value.as < struct_decl_ptr > ()->fields = std::move(yystack_[1].value.as < std::vector<Field> > ());
        }
#line 1680 "parser.cpp"
    break;

  case 37: // evar: LABEL
#line 297 "src/parser.y"
            { yylhs.value.as < std::string > () = std::move(yystack_[0].value.as < std::string > ()); }
#line 1686 "parser.cpp"
    break;

  case 38: // evars: evar
#line 300 "src/parser.y"
           { yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{yystack_[0].value.as < std::string > ()}; }
#line 1692 "parser.cpp"
    break;

  case 39: // evars: evars evar
#line 302 "src/parser.y"
        {
            yystack_[1].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));
            yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[1].value.as < std::vector<std::string> > ());
        }
#line 1701 "parser.cpp"
    break;

  case 40: // enum_def: ENUM LABEL LBRA evars RBRA
#line 310 "src/parser.y"
        { 
            yylhs.value.as < enum_decl_ptr > () = std::make_unique<EnumDecl>(); 
            yylhs.value.as < enum_decl_ptr > ()->name = std::move(yystack_[3].value.as < std::string > ());
            yylhs.value.as < enum_decl_ptr > ()->evar = std::move(yystack_[1].value.as < std::vector<std::string> > ());
        }
#line 1711 "parser.cpp"
    break;

  case 41: // program: helpers branch_expr
#line 319 "src/parser.y"
        {
            yylhs.value.as < prog_ptr > () = std::make_unique<ProgramNode>();
            yylhs.value.as < prog_ptr > ()->program = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ());
            yylhs.value.as < prog_ptr > ()->ret = std::move(yystack_[0].value.as < expr_ptr > ());
        }
#line 1721 "parser.cpp"
    break;

  case 42: // branch_expr: return_expr
#line 327 "src/parser.y"
                  { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 1727 "parser.cpp"
    break;

  case 43: // branch_expr: guard_expr
#line 328 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < guard_ptr > ()); }
#line 1733 "parser.cpp"
    break;

  case 44: // branch_expr: case_expr
#line 329 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < case_ptr > ()); }
#line 1739 "parser.cpp"
    break;

  case 45: // guard_expr: MARK value_expr OF TSEP guards PEND
#line 334 "src/parser.y"
        {
            yylhs.value.as < guard_ptr > () = std::make_unique<GuardNode>();
            yylhs.value.as < guard_ptr > ()->target = std::move(yystack_[4].value.as < expr_ptr > ());
            yylhs.value.as < guard_ptr > ()->branches = std::move(yystack_[1].value.as < std::vector<g_branch_ptr> > ());
        }
#line 1749 "parser.cpp"
    break;

  case 46: // guards: guard
#line 343 "src/parser.y"
        { 
            yylhs.value.as < std::vector<g_branch_ptr> > () = std::vector<g_branch_ptr>{}; 
            yylhs.value.as < std::vector<g_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < g_branch_ptr > ()));
        }
#line 1758 "parser.cpp"
    break;

  case 47: // guards: guards COMMA guard
#line 348 "src/parser.y"
        {
            yystack_[2].value.as < std::vector<g_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < g_branch_ptr > ()));
            yylhs.value.as < std::vector<g_branch_ptr> > () = std::move(yystack_[2].value.as < std::vector<g_branch_ptr> > ());
        }
#line 1767 "parser.cpp"
    break;

  case 48: // guard: BAR value_expr ARROW branch_expr
#line 356 "src/parser.y"
        {
            yylhs.value.as < g_branch_ptr > () = std::make_unique<GuardBranchNode>();
            yylhs.value.as < g_branch_ptr > ()->match = std::move(yystack_[2].value.as < expr_ptr > ());
            yylhs.value.as < g_branch_ptr > ()->body = std::move(yystack_[0].value.as < expr_ptr > ());
        }
#line 1777 "parser.cpp"
    break;

  case 49: // guard: BAR ELSE ARROW branch_expr
#line 362 "src/parser.y"
        {
            yylhs.value.as < g_branch_ptr > () = std::make_unique<GuardBranchNode>();
            auto temp = std::make_unique<BoolLit>();
            temp->value = true;
            yylhs.value.as < g_branch_ptr > ()->match = std::move(temp);
            yylhs.value.as < g_branch_ptr > ()->body = std::move(yystack_[0].value.as < expr_ptr > ());
        }
#line 1789 "parser.cpp"
    break;

  case 50: // case_expr: CASE value_expr OF TSEP patterns PEND
#line 373 "src/parser.y"
        {
            yylhs.value.as < case_ptr > () = std::make_unique<CaseNode>();
            yylhs.value.as < case_ptr > ()->target = std::move(yystack_[4].value.as < expr_ptr > ());
            yylhs.value.as < case_ptr > ()->patterns = std::move(yystack_[1].value.as < std::vector<c_branch_ptr> > ());
        }
#line 1799 "parser.cpp"
    break;

  case 51: // patterns: pattern_branch
#line 382 "src/parser.y"
        { 
            yylhs.value.as < std::vector<c_branch_ptr> > () = std::vector<c_branch_ptr>{}; 
            yylhs.value.as < std::vector<c_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < c_branch_ptr > ())); 
        }
#line 1808 "parser.cpp"
    break;

  case 52: // patterns: patterns COMMA pattern_branch
#line 387 "src/parser.y"
        {
            yystack_[2].value.as < std::vector<c_branch_ptr> > ().push_back(std::move(yystack_[0].value.as < c_branch_ptr > ()));
            yylhs.value.as < std::vector<c_branch_ptr> > () = std::move(yystack_[2].value.as < std::vector<c_branch_ptr> > ());
        }
#line 1817 "parser.cpp"
    break;

  case 53: // pattern_branch: pattern ARROW branch_expr
#line 395 "src/parser.y"
        {
            yylhs.value.as < c_branch_ptr > () = std::make_unique<CaseBranchNode>();
            yylhs.value.as < c_branch_ptr > ()->pattern = std::move(yystack_[2].value.as < literal_ptr > ());
            yylhs.value.as < c_branch_ptr > ()->body = std::move(yystack_[0].value.as < expr_ptr > ());
        }
#line 1827 "parser.cpp"
    break;

  case 54: // literal: char_lit
#line 403 "src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1833 "parser.cpp"
    break;

  case 55: // literal: int_lit
#line 404 "src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1839 "parser.cpp"
    break;

  case 56: // literal: float_lit
#line 405 "src/parser.y"
                { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1845 "parser.cpp"
    break;

  case 57: // literal: bool_lit
#line 406 "src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1851 "parser.cpp"
    break;

  case 58: // literal: enum_lit
#line 407 "src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1857 "parser.cpp"
    break;

  case 59: // literal: list_pattern
#line 408 "src/parser.y"
                   { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1863 "parser.cpp"
    break;

  case 60: // pattern: literal
#line 412 "src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1869 "parser.cpp"
    break;

  case 61: // pattern: NIL
#line 413 "src/parser.y"
          { yylhs.value.as < literal_ptr > () = std::make_unique<NilLit>(); }
#line 1875 "parser.cpp"
    break;

  case 62: // pattern: DEFAULT
#line 414 "src/parser.y"
              { yylhs.value.as < literal_ptr > () = std::make_unique<DefaultLit>(); }
#line 1881 "parser.cpp"
    break;

  case 63: // enum_lit: LABEL
#line 419 "src/parser.y"
        { 
            auto temp = std::make_unique<EnumLit>();
            temp->elem = std::move(yystack_[0].value.as < std::string > ()); 
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 1891 "parser.cpp"
    break;

  case 64: // list_pattern: SQ_LBRA SQ_RBRA
#line 427 "src/parser.y"
        { 
            auto temp = std::make_unique<ListLit>();
            temp->elems = std::vector<literal_ptr>{}; 
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 1901 "parser.cpp"
    break;

  case 65: // list_pattern: list_lit
#line 432 "src/parser.y"
               { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1907 "parser.cpp"
    break;

  case 66: // list_pattern: string_lit
#line 433 "src/parser.y"
                 { yylhs.value.as < literal_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 1913 "parser.cpp"
    break;

  case 67: // list_pattern: size_patterns
#line 435 "src/parser.y"
        {
            auto temp = std::make_unique<ListPatternLit>(); 
            temp->patterns = std::move(yystack_[0].value.as < std::vector<std::string> > ());
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 1923 "parser.cpp"
    break;

  case 68: // string_lit: STRING
#line 443 "src/parser.y"
             {yylhs.value.as < literal_ptr > () = str_to_chlist(yystack_[0].value.as < std::string > ()); }
#line 1929 "parser.cpp"
    break;

  case 69: // list_lit: SQ_LBRA list_pattern_lit SQ_RBRA
#line 447 "src/parser.y"
        { 
            auto temp = std::make_unique<ListLit>(); 
            temp->elems = std::move(yystack_[1].value.as < std::vector<literal_ptr> > ()); 
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 1939 "parser.cpp"
    break;

  case 70: // list_pattern_lit: literal
#line 455 "src/parser.y"
        { 
            yylhs.value.as < std::vector<literal_ptr> > () = std::vector<literal_ptr>{}; 
            yylhs.value.as < std::vector<literal_ptr> > ().push_back(std::move(yystack_[0].value.as < literal_ptr > ()));
        }
#line 1948 "parser.cpp"
    break;

  case 71: // list_pattern_lit: list_pattern_lit COMMA literal
#line 460 "src/parser.y"
        { 
            yystack_[2].value.as < std::vector<literal_ptr> > ().push_back(std::move(yystack_[0].value.as < literal_ptr > ()));
            yylhs.value.as < std::vector<literal_ptr> > () = std::move(yystack_[2].value.as < std::vector<literal_ptr> > ());
        }
#line 1957 "parser.cpp"
    break;

  case 72: // size_patterns: LABEL TSEP SQ_LBRA SQ_LBRA
#line 468 "src/parser.y"
        { 
            yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{}; 
            yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[3].value.as < std::string > ()));
        }
#line 1966 "parser.cpp"
    break;

  case 73: // size_patterns: size_pattern_two
#line 472 "src/parser.y"
                       { yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[0].value.as < std::vector<std::string> > ()); }
#line 1972 "parser.cpp"
    break;

  case 74: // size_pattern_two: LABEL TSEP LABEL
#line 477 "src/parser.y"
        { 
            yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>{};
            yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[2].value.as < std::string > ()));
            yylhs.value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ())); 
        }
#line 1982 "parser.cpp"
    break;

  case 75: // size_pattern_two: size_pattern_two TSEP LABEL
#line 482 "src/parser.y"
                                  {
        yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));
        yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ());
    }
#line 1991 "parser.cpp"
    break;

  case 76: // return_expr: RETURN value_expr
#line 489 "src/parser.y"
                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 1997 "parser.cpp"
    break;

  case 77: // helpers: %empty
#line 492 "src/parser.y"
             { yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>{}; }
#line 2003 "parser.cpp"
    break;

  case 78: // helpers: helpers helper_expr
#line 494 "src/parser.y"
        {
            yystack_[1].value.as < std::vector<expr_ptr> > ().push_back(std::move(yystack_[0].value.as < expr_ptr > ()));
            yylhs.value.as < std::vector<expr_ptr> > () = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ());
        }
#line 2012 "parser.cpp"
    break;

  case 79: // helper_expr: assign_expr
#line 501 "src/parser.y"
                  { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < bin_ptr > ()); }
#line 2018 "parser.cpp"
    break;

  case 80: // helper_expr: print_expr
#line 502 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < print_ptr > ()); }
#line 2024 "parser.cpp"
    break;

  case 81: // helper_expr: read_expr
#line 503 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < read_ptr > ()); }
#line 2030 "parser.cpp"
    break;

  case 82: // print_expr: PRINT LBRA value_expr RBRA
#line 508 "src/parser.y"
        { 
            yylhs.value.as < print_ptr > () = std::make_unique<PrintNode>();
            yylhs.value.as < print_ptr > ()->msg = std::move(yystack_[1].value.as < expr_ptr > ());
        }
#line 2039 "parser.cpp"
    break;

  case 83: // read_expr: var_decl ASSGN READ LBRA RBRA
#line 516 "src/parser.y"
        {
            yylhs.value.as < read_ptr > () = std::make_unique<ReadNode>();
            yylhs.value.as < read_ptr > ()->var = std::move(yystack_[4].value.as < var_ptr > ());
        }
#line 2048 "parser.cpp"
    break;

  case 84: // var_decl: LABEL TSEP type
#line 523 "src/parser.y"
        {
            yylhs.value.as < var_ptr > () = std::make_unique<VarNode>();
            yylhs.value.as < var_ptr > ()->label = std::move(yystack_[2].value.as < std::string > ());
            yylhs.value.as < var_ptr > ()->type = std::move(yystack_[0].value.as < type_ptr > ());
        }
#line 2058 "parser.cpp"
    break;

  case 85: // assign_expr: var_decl LBRA program RBRA
#line 532 "src/parser.y"
        { 
            yylhs.value.as < bin_ptr > () = std::make_unique<BinaryNode>();
            yylhs.value.as < bin_ptr > ()->op = BinaryOp::ASSIGN;
            yylhs.value.as < bin_ptr > ()->l_exp = std::move(yystack_[3].value.as < var_ptr > ());
            yylhs.value.as < bin_ptr > ()->r_exp = std::move(yystack_[1].value.as < prog_ptr > ());
        }
#line 2069 "parser.cpp"
    break;

  case 86: // assign_expr: var_decl ASSGN value_expr
#line 539 "src/parser.y"
        {
            yylhs.value.as < bin_ptr > () = std::make_unique<BinaryNode>();
            yylhs.value.as < bin_ptr > ()->op = BinaryOp::ASSIGN;
            yylhs.value.as < bin_ptr > ()->l_exp = std::move(yystack_[2].value.as < var_ptr > ());
            yylhs.value.as < bin_ptr > ()->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
        }
#line 2080 "parser.cpp"
    break;

  case 87: // int_lit: INT
#line 549 "src/parser.y"
        { 
            auto temp = std::make_unique<IntLit>();
            temp->value = yystack_[0].value.as < uint64_t > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 2090 "parser.cpp"
    break;

  case 88: // float_lit: FLOAT
#line 557 "src/parser.y"
        {
            auto temp = std::make_unique<IntLit>();
            temp->value = yystack_[0].value.as < double > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 2100 "parser.cpp"
    break;

  case 89: // bool_lit: TRUE
#line 565 "src/parser.y"
        { 
            auto temp = std::make_unique<BoolLit>();
            temp->value = true;
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 2110 "parser.cpp"
    break;

  case 90: // bool_lit: FALSE
#line 571 "src/parser.y"
        { 
            auto temp = std::make_unique<BoolLit>();
            temp->value = false;
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 2120 "parser.cpp"
    break;

  case 91: // char_lit: CHAR
#line 580 "src/parser.y"
        { 
            auto temp = std::make_unique<CharLit>();
            temp->value = yystack_[0].value.as < char > ();
            yylhs.value.as < literal_ptr > () = std::move(temp);
        }
#line 2130 "parser.cpp"
    break;

  case 92: // bool_op: BOR
#line 587 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::BOR; }
#line 2136 "parser.cpp"
    break;

  case 93: // bool_op: BAND
#line 588 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::BAND; }
#line 2142 "parser.cpp"
    break;

  case 94: // comp_op: CEQ
#line 592 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CEQ; }
#line 2148 "parser.cpp"
    break;

  case 95: // comp_op: CNEQ
#line 593 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CNEQ; }
#line 2154 "parser.cpp"
    break;

  case 96: // comp_op: CGT
#line 594 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CGT; }
#line 2160 "parser.cpp"
    break;

  case 97: // comp_op: CLT
#line 595 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::CLT; }
#line 2166 "parser.cpp"
    break;

  case 98: // comp_op: CGEQ
#line 596 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CGEQ; }
#line 2172 "parser.cpp"
    break;

  case 99: // comp_op: CLEQ
#line 597 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::CLEQ; }
#line 2178 "parser.cpp"
    break;

  case 100: // bitwise_op: LAND
#line 601 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::LAND; }
#line 2184 "parser.cpp"
    break;

  case 101: // bitwise_op: BAR
#line 602 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LOR; }
#line 2190 "parser.cpp"
    break;

  case 102: // bitwise_op: LXOR
#line 603 "src/parser.y"
           { yylhs.value.as < BinaryOp > () = BinaryOp::LXOR; }
#line 2196 "parser.cpp"
    break;

  case 103: // shift_op: LSL
#line 606 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LSL; }
#line 2202 "parser.cpp"
    break;

  case 104: // shift_op: LSR
#line 607 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::LSR; }
#line 2208 "parser.cpp"
    break;

  case 105: // additive_op: ADD
#line 610 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::ADD; }
#line 2214 "parser.cpp"
    break;

  case 106: // additive_op: SUB
#line 611 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::SUB; }
#line 2220 "parser.cpp"
    break;

  case 107: // additive_op: CONCAT
#line 612 "src/parser.y"
             { yylhs.value.as < BinaryOp > () = BinaryOp::CONCAT; }
#line 2226 "parser.cpp"
    break;

  case 108: // mult_op: MUL
#line 616 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::MUL; }
#line 2232 "parser.cpp"
    break;

  case 109: // mult_op: DIV
#line 617 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::DIV; }
#line 2238 "parser.cpp"
    break;

  case 110: // mult_op: MOD
#line 618 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::MOD; }
#line 2244 "parser.cpp"
    break;

  case 111: // mult_op: FLR
#line 619 "src/parser.y"
          { yylhs.value.as < BinaryOp > () = BinaryOp::FLR; }
#line 2250 "parser.cpp"
    break;

  case 112: // unary_op: BNOT
#line 623 "src/parser.y"
           { yylhs.value.as < UnaryOp > () = UnaryOp::BNOT; }
#line 2256 "parser.cpp"
    break;

  case 113: // unary_op: LNEG
#line 624 "src/parser.y"
           { yylhs.value.as < UnaryOp > () = UnaryOp::LNEG; }
#line 2262 "parser.cpp"
    break;

  case 114: // unary_op: SUB
#line 625 "src/parser.y"
          { yylhs.value.as < UnaryOp > () = UnaryOp::MINUS; }
#line 2268 "parser.cpp"
    break;

  case 115: // nominal_expr: LABEL
#line 630 "src/parser.y"
        { 
            auto temp = std::make_unique<NominalNode>();
            temp->label = std::move(yystack_[0].value.as < std::string > ()); 
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2278 "parser.cpp"
    break;

  case 116: // list_expr: empty_list
#line 637 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < list_ptr > ()); }
#line 2284 "parser.cpp"
    break;

  case 117: // list_expr: list_con
#line 638 "src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < list_ptr > ()); }
#line 2290 "parser.cpp"
    break;

  case 118: // list_expr: string_lit
#line 639 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2296 "parser.cpp"
    break;

  case 119: // empty_list: SQ_LBRA SQ_RBRA
#line 643 "src/parser.y"
                      { yylhs.value.as < list_ptr > () = std::make_unique<ListNode>(); yylhs.value.as < list_ptr > ()->elems = std::vector<expr_ptr>{}; }
#line 2302 "parser.cpp"
    break;

  case 120: // list_con: SQ_LBRA expr_list SQ_RBRA
#line 647 "src/parser.y"
        { yylhs.value.as < list_ptr > () = std::make_unique<ListNode>(); yylhs.value.as < list_ptr > ()->elems = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ()); }
#line 2308 "parser.cpp"
    break;

  case 121: // expr_list: value_expr
#line 651 "src/parser.y"
        { 
            yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>{};
            yylhs.value.as < std::vector<expr_ptr> > ().push_back(std::move(yystack_[0].value.as < expr_ptr > ())); 
        }
#line 2317 "parser.cpp"
    break;

  case 122: // expr_list: expr_list COMMA value_expr
#line 656 "src/parser.y"
        {
            yystack_[2].value.as < std::vector<expr_ptr> > ().push_back(std::move(yystack_[0].value.as < expr_ptr > ()));
            yylhs.value.as < std::vector<expr_ptr> > () = std::move(yystack_[2].value.as < std::vector<expr_ptr> > ());
        }
#line 2326 "parser.cpp"
    break;

  case 123: // param_expr: LABEL LBRA RBRA
#line 664 "src/parser.y"
        {
            auto temp = std::make_unique<FunCallNode>();
            temp->func = std::move(yystack_[2].value.as < std::string > ());
            temp->args = std::vector<expr_ptr>{};
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2337 "parser.cpp"
    break;

  case 124: // param_expr: LABEL LBRA expr_list RBRA
#line 671 "src/parser.y"
        {
            auto temp = std::make_unique<ParamNode>(); 
            temp->label = std::move(yystack_[3].value.as < std::string > ());
            temp->params = std::move(yystack_[1].value.as < std::vector<expr_ptr> > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2348 "parser.cpp"
    break;

  case 125: // value_expr: bool_expr
#line 680 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2354 "parser.cpp"
    break;

  case 126: // bool_expr: comp_expr
#line 683 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2360 "parser.cpp"
    break;

  case 127: // bool_expr: bool_expr bool_op comp_expr
#line 685 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2372 "parser.cpp"
    break;

  case 128: // comp_expr: bitwise_expr
#line 695 "src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2378 "parser.cpp"
    break;

  case 129: // comp_expr: bitwise_expr comp_op bitwise_expr
#line 697 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2390 "parser.cpp"
    break;

  case 130: // bitwise_expr: shift_expr
#line 707 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2396 "parser.cpp"
    break;

  case 131: // bitwise_expr: bitwise_expr bitwise_op shift_expr
#line 709 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2408 "parser.cpp"
    break;

  case 132: // shift_expr: additive_expr
#line 719 "src/parser.y"
                    { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2414 "parser.cpp"
    break;

  case 133: // shift_expr: shift_expr shift_op additive_expr
#line 721 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2426 "parser.cpp"
    break;

  case 134: // additive_expr: mult_expr
#line 731 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2432 "parser.cpp"
    break;

  case 135: // additive_expr: additive_expr additive_op mult_expr
#line 733 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2444 "parser.cpp"
    break;

  case 136: // mult_expr: pow_expr
#line 743 "src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2450 "parser.cpp"
    break;

  case 137: // mult_expr: mult_expr mult_op pow_expr
#line 745 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = yystack_[1].value.as < BinaryOp > ();
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2462 "parser.cpp"
    break;

  case 138: // pow_expr: unary_expr
#line 755 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2468 "parser.cpp"
    break;

  case 139: // pow_expr: unary_expr POW pow_expr
#line 757 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = BinaryOp::POW;
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2480 "parser.cpp"
    break;

  case 140: // unary_expr: postfix_expr
#line 767 "src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2486 "parser.cpp"
    break;

  case 141: // unary_expr: unary_op postfix_expr
#line 769 "src/parser.y"
        {
            auto temp = std::make_unique<UnaryNode>();
            temp->op = yystack_[1].value.as < UnaryOp > ();
            temp->exp = std::move(yystack_[0].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2497 "parser.cpp"
    break;

  case 142: // postfix_expr: literal_expr
#line 778 "src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2503 "parser.cpp"
    break;

  case 143: // postfix_expr: postfix_expr SQ_LBRA value_expr SQ_RBRA
#line 780 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();
            temp->op = BinaryOp::INDEX;
            temp->l_exp = std::move(yystack_[3].value.as < expr_ptr > ());
            temp->r_exp = std::move(yystack_[1].value.as < expr_ptr > ());
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2515 "parser.cpp"
    break;

  case 144: // postfix_expr: postfix_expr DOT LABEL
#line 788 "src/parser.y"
        {
            auto temp = std::make_unique<BinaryNode>();

            auto fnode = std::make_unique<FieldNode>();
            fnode->field = std::move(yystack_[0].value.as < std::string > ());

            temp->op = BinaryOp::ACCESS;
            temp->l_exp = std::move(yystack_[2].value.as < expr_ptr > ());
            temp->r_exp = std::move(fnode);
            yylhs.value.as < expr_ptr > () = std::move(temp);
        }
#line 2531 "parser.cpp"
    break;

  case 145: // literal_expr: int_lit
#line 802 "src/parser.y"
              { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2537 "parser.cpp"
    break;

  case 146: // literal_expr: float_lit
#line 803 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2543 "parser.cpp"
    break;

  case 147: // literal_expr: char_lit
#line 804 "src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2549 "parser.cpp"
    break;

  case 148: // literal_expr: bool_lit
#line 805 "src/parser.y"
               { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < literal_ptr > ()); }
#line 2555 "parser.cpp"
    break;

  case 149: // literal_expr: list_expr
#line 806 "src/parser.y"
                { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2561 "parser.cpp"
    break;

  case 150: // literal_expr: nominal_expr
#line 807 "src/parser.y"
                   { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2567 "parser.cpp"
    break;

  case 151: // literal_expr: param_expr
#line 808 "src/parser.y"
                 { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2573 "parser.cpp"
    break;

  case 152: // literal_expr: LBRA value_expr RBRA
#line 809 "src/parser.y"
                           { yylhs.value.as < expr_ptr > () = std::move(yystack_[1].value.as < expr_ptr > ()); }
#line 2579 "parser.cpp"
    break;


#line 2583 "parser.cpp"

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
        error (YY_MOVE (msg));
      }


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

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


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
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const short parser::yypact_ninf_ = -175;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
    -175,     2,    83,  -175,     9,    62,    66,  -175,  -175,  -175,
    -175,    -1,    57,    67,    96,   106,   115,   100,   110,   112,
    -175,   113,    15,  -175,  -175,  -175,     8,   217,   125,    96,
     217,  -175,   106,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,   217,   217,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,   217,  -175,  -175,  -175,   132,   117,  -175,   134,  -175,
     103,   217,  -175,  -175,    80,   217,  -175,   129,   120,   120,
     139,   120,  -175,  -175,  -175,  -175,  -175,  -175,  -175,    51,
    -175,  -175,   217,  -175,  -175,  -175,  -175,   142,  -175,  -175,
     120,     1,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
     203,  -175,  -175,  -175,  -175,  -175,   163,    32,  -175,   202,
      60,    14,    68,  -175,   133,   108,  -175,   171,   120,  -175,
    -175,     6,  -175,    54,   149,  -175,   121,  -175,   108,   147,
    -175,  -175,   120,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,   120,   120,  -175,  -175,   120,  -175,  -175,  -175,
     120,  -175,  -175,  -175,  -175,   120,   120,   120,   176,   150,
     154,   164,   166,  -175,  -175,   111,  -175,  -175,   120,   186,
    -175,    81,    60,    14,    68,  -175,  -175,   165,  -175,   151,
    -175,  -175,   168,  -175,  -175,   181,  -175,  -175,   170,    -2,
    -175,  -175,   137,  -175,  -175,  -175,  -175,  -175,   183,  -175,
    -175,  -175,  -175,  -175,   102,    44,  -175,  -175,    10,  -175,
    -175,   124,   186,  -175,    21,   212,   159,   160,   151,  -175,
    -175,   196,  -175,   208,  -175,  -175,  -175,    21,    21,  -175,
    -175,  -175,  -175,  -175
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     2,     1,     0,     0,     0,     4,     5,     6,
       7,     0,     0,     0,    27,     0,     0,     0,     0,    28,
      29,     0,     0,    33,    37,    38,     0,     0,     0,     0,
       0,    36,     0,    40,    39,    26,    20,    21,    22,    23,
      16,    17,     8,     0,    31,    12,    18,    19,    13,    14,
      15,     0,    30,    35,    34,     0,     9,    10,     0,    77,
       0,     0,    24,    32,     0,     0,    11,     0,     0,     0,
       0,     0,    41,    43,    44,    42,    78,    80,    81,     0,
      79,    25,     0,    87,    88,    91,    68,   115,    89,    90,
       0,     0,   114,   113,   112,   118,   145,   146,   148,   147,
       0,   150,   149,   116,   117,   151,     0,   125,   126,   128,
     130,   132,   134,   136,   138,   140,   142,     0,     0,    76,
      77,     0,    84,     0,     0,   119,     0,   121,   141,     0,
      93,    92,     0,   100,   101,   102,    96,    97,    98,    99,
      94,    95,     0,     0,   103,   104,     0,   105,   106,   107,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,    86,   123,     0,   152,   120,     0,     0,
     127,   129,   131,   133,   135,   137,   139,     0,   144,     0,
      82,    85,     0,   124,   122,    63,    62,    61,     0,     0,
      51,    60,     0,    58,    59,    66,    65,    67,    73,    55,
      56,    57,    54,   143,     0,     0,    46,    83,     0,    64,
      70,     0,     0,    50,     0,     0,     0,     0,     0,    45,
      74,     0,    69,     0,    52,    53,    75,     0,     0,    47,
      72,    71,    49,    48
  };

  const short
  parser::yypgoto_[] =
  {
    -175,  -175,  -175,  -175,  -175,  -175,   104,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,   199,  -175,  -175,   197,  -175,
     204,  -175,  -175,   116,  -162,  -175,  -175,    13,  -175,  -175,
      23,  -174,  -175,  -175,  -175,  -149,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,  -148,  -144,  -142,
     -91,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,   114,  -175,   -68,  -175,   101,   105,    95,   118,
     109,     3,  -175,   152,  -175
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     1,     2,     7,    55,    56,    44,    45,    46,    47,
      48,    49,    50,    18,    19,    20,     8,    22,    23,     9,
      25,    26,    10,    63,    72,    73,   205,   206,    74,   189,
     190,   191,   192,   193,   194,    95,   196,   211,   197,   198,
      75,    64,    76,    77,    78,    79,    80,    96,    97,    98,
      99,   132,   142,   143,   146,   150,   155,   100,   101,   102,
     103,   104,   126,   105,   127,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116
  };

  const unsigned char
  parser::yytable_[] =
  {
     106,   117,     3,   119,    83,    84,    85,    86,    87,    83,
      84,    85,    86,    87,   210,    24,    11,   220,    88,    89,
     195,   199,   124,    88,    89,   200,   162,   201,    14,    68,
      90,   212,    91,   125,    69,    90,   213,    91,    33,   195,
     199,   221,    92,    71,   200,    31,   201,    92,    32,   231,
     160,    93,   225,   163,   147,   148,    93,    83,    84,    85,
      86,    87,    94,   195,   199,   232,   233,    94,   200,    12,
     201,    88,    89,    13,   195,   199,   149,   218,   202,   200,
     120,   201,   219,    90,   164,    91,    15,    67,    68,   177,
     121,   130,   131,    69,     4,    92,    16,   202,     5,     6,
     184,    70,    71,    17,    93,    83,    84,    85,    86,    87,
     151,   152,   153,    21,   154,    94,   216,   144,   145,    88,
      89,   202,    24,    83,    84,    85,    86,    87,   133,   134,
     135,    90,   202,    91,    53,    27,   217,    88,    89,   157,
      28,   183,   158,    92,   168,    29,    57,    58,    30,    90,
      61,    91,    93,   167,   168,    59,   222,   223,   175,   176,
      51,    92,    60,    94,    82,    66,    62,    65,   118,    81,
      93,   123,   129,    83,    84,    85,    86,   185,   156,   166,
     159,    94,   169,   178,   180,   179,   122,    88,    89,    83,
      84,    85,    86,   185,   181,   182,   186,   203,   207,   204,
     214,   188,   209,    88,    89,   187,    83,    84,    85,    86,
      87,    83,    84,    85,    86,   185,   208,   188,   215,   226,
      88,    89,   227,   228,    35,    88,    89,   230,    52,    54,
      34,   229,    90,   170,    91,   224,   161,   165,   172,   188,
      36,    37,    38,    39,    40,    41,    42,   171,    43,   133,
     134,   135,   128,   136,   137,   138,   139,   140,   141,   174,
       0,     0,     0,     0,   173
  };

  const short
  parser::yycheck_[] =
  {
      68,    69,     0,    71,     3,     4,     5,     6,     7,     3,
       4,     5,     6,     7,   188,     7,     7,     7,    17,    18,
     169,   169,    90,    17,    18,   169,    20,   169,    29,     8,
      29,    33,    31,    32,    13,    29,    38,    31,    30,   188,
     188,    31,    41,    22,   188,    30,   188,    41,    33,   223,
     118,    50,   214,   121,    40,    41,    50,     3,     4,     5,
       6,     7,    61,   212,   212,   227,   228,    61,   212,     7,
     212,    17,    18,     7,   223,   223,    62,    33,   169,   223,
      29,   223,    38,    29,    30,    31,    29,     7,     8,   157,
      39,    59,    60,    13,    11,    41,    29,   188,    15,    16,
     168,    21,    22,     7,    50,     3,     4,     5,     6,     7,
      42,    43,    44,     7,    46,    61,    14,    57,    58,    17,
      18,   212,     7,     3,     4,     5,     6,     7,    47,    48,
      49,    29,   223,    31,    30,    35,   204,    17,    18,    31,
      30,    30,    34,    41,    33,    33,    42,    43,    35,    29,
      33,    31,    50,    32,    33,    51,    32,    33,   155,   156,
      35,    41,    30,    61,    35,    61,    32,    64,    29,    65,
      50,    29,     9,     3,     4,     5,     6,     7,    45,    30,
       9,    61,    35,     7,    30,    35,    82,    17,    18,     3,
       4,     5,     6,     7,    30,    29,    10,    32,    30,    48,
      63,    31,    32,    17,    18,    19,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,    35,    31,    35,     7,
      17,    18,    63,    63,     7,    17,    18,    31,    29,    32,
      26,   218,    29,   132,    31,   212,   120,   123,   143,    31,
      23,    24,    25,    26,    27,    28,    29,   142,    31,    47,
      48,    49,   100,    51,    52,    53,    54,    55,    56,   150,
      -1,    -1,    -1,    -1,   146
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    66,    67,     0,    11,    15,    16,    68,    81,    84,
      87,     7,     7,     7,    29,    29,    29,     7,    78,    79,
      80,     7,    82,    83,     7,    85,    86,    35,    30,    33,
      35,    30,    33,    30,    85,     7,    23,    24,    25,    26,
      27,    28,    29,    31,    71,    72,    73,    74,    75,    76,
      77,    35,    80,    71,    83,    69,    70,    71,    71,    71,
      30,    33,    32,    88,   106,    64,    71,     7,     8,    13,
      21,    22,    89,    90,    93,   105,   107,   108,   109,   110,
     111,    71,    35,     3,     4,     5,     6,     7,    17,    18,
      29,    31,    41,    50,    61,   100,   112,   113,   114,   115,
     122,   123,   124,   125,   126,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   129,    29,   129,
      29,    39,    71,    29,   129,    32,   127,   129,   138,     9,
      59,    60,   116,    47,    48,    49,    51,    52,    53,    54,
      55,    56,   117,   118,    57,    58,   119,    40,    41,    62,
     120,    42,    43,    44,    46,   121,    45,    31,    34,     9,
     129,    88,    20,   129,    30,   127,    30,    32,    33,    35,
     131,   132,   133,   134,   135,   136,   136,   129,     7,    35,
      30,    30,    29,    30,   129,     7,    10,    19,    31,    94,
      95,    96,    97,    98,    99,   100,   101,   103,   104,   112,
     113,   114,   115,    32,    48,    91,    92,    30,    35,    32,
      96,   102,    33,    38,    63,    35,    14,   129,    33,    38,
       7,    31,    32,    33,    95,    89,     7,    63,    63,    92,
      31,    96,    89,    89
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    65,    66,    67,    67,    68,    68,    68,    69,    69,
      70,    70,    71,    71,    71,    71,    72,    72,    72,    72,
      73,    73,    74,    74,    75,    76,    77,    78,    78,    79,
      79,    80,    81,    82,    82,    83,    84,    85,    86,    86,
      87,    88,    89,    89,    89,    90,    91,    91,    92,    92,
      93,    94,    94,    95,    96,    96,    96,    96,    96,    96,
      97,    97,    97,    98,    99,    99,    99,    99,   100,   101,
     102,   102,   103,   103,   104,   104,   105,   106,   106,   107,
     107,   107,   108,   109,   110,   111,   111,   112,   113,   114,
     114,   115,   116,   116,   117,   117,   117,   117,   117,   117,
     118,   118,   118,   119,   119,   120,   120,   120,   121,   121,
     121,   121,   122,   122,   122,   123,   124,   124,   124,   125,
     126,   127,   127,   128,   128,   129,   130,   130,   131,   131,
     132,   132,   133,   133,   134,   134,   135,   135,   136,   136,
     137,   137,   138,   138,   138,   139,   139,   139,   139,   139,
     139,   139,   139
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     1,     1,     1,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     5,     1,     0,     1,     1,
       3,     3,     8,     1,     3,     3,     5,     1,     1,     2,
       5,     2,     1,     1,     1,     6,     1,     3,     4,     4,
       6,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     3,
       1,     3,     4,     1,     3,     3,     2,     0,     2,     1,
       1,     1,     4,     5,     3,     4,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     1,     3,     3,     4,     1,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     2,     1,     4,     3,     1,     1,     1,     1,     1,
       1,     1,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "CHAR",
  "STRING", "LABEL", "CASE", "OF", "DEFAULT", "FUNC", "LAMB", "MARK",
  "ELSE", "STRUCT", "ENUM", "TRUE", "FALSE", "NIL", "READ", "PRINT",
  "RETURN", "T_INT", "T_LONG", "T_FLOAT", "T_DOUBLE", "T_CHAR", "T_BOOL",
  "LBRA", "RBRA", "SQ_LBRA", "SQ_RBRA", "COMMA", "DOT", "TSEP", "EMPTY",
  "KEOF", "PEND", "ASSGN", "ADD", "SUB", "MUL", "DIV", "MOD", "POW", "FLR",
  "LAND", "BAR", "LXOR", "LNEG", "CGT", "CLT", "CGEQ", "CLEQ", "CEQ",
  "CNEQ", "LSL", "LSR", "BAND", "BOR", "BNOT", "CONCAT", "ARROW", "PROD",
  "$accept", "module", "definitions", "definition", "opt_types", "types",
  "type", "literal_type", "int_lit_type", "float_lit_type", "list_type",
  "func_type", "nominal_type", "opt_params", "params", "param",
  "function_def", "fields", "field", "struct_def", "evar", "evars",
  "enum_def", "program", "branch_expr", "guard_expr", "guards", "guard",
  "case_expr", "patterns", "pattern_branch", "literal", "pattern",
  "enum_lit", "list_pattern", "string_lit", "list_lit", "list_pattern_lit",
  "size_patterns", "size_pattern_two", "return_expr", "helpers",
  "helper_expr", "print_expr", "read_expr", "var_decl", "assign_expr",
  "int_lit", "float_lit", "bool_lit", "char_lit", "bool_op", "comp_op",
  "bitwise_op", "shift_op", "additive_op", "mult_op", "unary_op",
  "nominal_expr", "list_expr", "empty_list", "list_con", "expr_list",
  "param_expr", "value_expr", "bool_expr", "comp_expr", "bitwise_expr",
  "shift_expr", "additive_expr", "mult_expr", "pow_expr", "unary_expr",
  "postfix_expr", "literal_expr", YY_NULLPTR
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
     309,   318,   327,   328,   329,   333,   342,   347,   355,   361,
     372,   381,   386,   394,   403,   404,   405,   406,   407,   408,
     412,   413,   414,   418,   426,   432,   433,   434,   443,   446,
     454,   459,   467,   472,   476,   482,   489,   492,   493,   501,
     502,   503,   507,   515,   522,   531,   538,   548,   556,   564,
     570,   579,   587,   588,   592,   593,   594,   595,   596,   597,
     601,   602,   603,   606,   607,   610,   611,   612,   616,   617,
     618,   619,   623,   624,   625,   629,   637,   638,   639,   643,
     646,   650,   655,   663,   670,   680,   683,   684,   695,   696,
     707,   708,   719,   720,   731,   732,   743,   744,   755,   756,
     767,   768,   778,   779,   787,   802,   803,   804,   805,   806,
     807,   808,   809
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
#line 3081 "parser.cpp"

