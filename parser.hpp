// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file parser.hpp
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 1 "src/parser.y"

    #include <string>
    #include "src/ast.hpp"

#line 54 "parser.hpp"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

#line 39 "src/parser.y"
namespace yy {
#line 190 "parser.hpp"




  /// A Bison parser.
  class parser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // bool_op
      // comp_op
      // bitwise_op
      // shift_op
      // additive_op
      // mult_op
      char dummy1[sizeof (BinaryOp)];

      // field
      char dummy2[sizeof (Field)];

      // param
      char dummy3[sizeof (Param)];

      // unary_op
      char dummy4[sizeof (UnaryOp)];

      // pattern_branch
      char dummy5[sizeof (c_branch_ptr)];

      // case_expr
      char dummy6[sizeof (case_ptr)];

      // CHAR
      char dummy7[sizeof (char)];

      // definition
      // helper_expr
      // assign_expr
      char dummy8[sizeof (decl_ptr)];

      // FLOAT
      char dummy9[sizeof (double)];

      // enum_def
      char dummy10[sizeof (enum_decl_ptr)];

      // branch_expr
      // return_expr
      // nominal_expr
      // list_expr
      // call_expr
      // struct_expr
      // value_expr
      // bool_expr
      // comp_expr
      // bitwise_expr
      // shift_expr
      // additive_expr
      // mult_expr
      // pow_expr
      // unary_expr
      // postfix_expr
      // literal_expr
      char dummy11[sizeof (expr_ptr)];

      // function_def
      char dummy12[sizeof (func_decl_ptr)];

      // guard
      char dummy13[sizeof (g_branch_ptr)];

      // guard_expr
      char dummy14[sizeof (guard_ptr)];

      // empty_list
      // list_con
      char dummy15[sizeof (list_ptr)];

      // literal
      // pattern
      // enum_lit
      // list_pattern
      // string_lit
      // list_lit
      // int_lit
      // float_lit
      // bool_lit
      // char_lit
      char dummy16[sizeof (literal_ptr)];

      // module
      char dummy17[sizeof (module_ptr)];

      // print_expr
      char dummy18[sizeof (print_ptr)];

      // program
      char dummy19[sizeof (prog_ptr)];

      // read_expr
      char dummy20[sizeof (read_ptr)];

      // STRING
      // LABEL
      // evar
      char dummy21[sizeof (std::string)];

      // fields
      char dummy22[sizeof (std::vector<Field>)];

      // opt_params
      // params
      char dummy23[sizeof (std::vector<Param>)];

      // patterns
      char dummy24[sizeof (std::vector<c_branch_ptr>)];

      // definitions
      // helpers
      char dummy25[sizeof (std::vector<decl_ptr>)];

      // expr_list
      char dummy26[sizeof (std::vector<expr_ptr>)];

      // guards
      char dummy27[sizeof (std::vector<g_branch_ptr>)];

      // list_pattern_lit
      char dummy28[sizeof (std::vector<literal_ptr>)];

      // evars
      // size_patterns
      char dummy29[sizeof (std::vector<std::string>)];

      // opt_types
      // types
      char dummy30[sizeof (std::vector<type_ptr>)];

      // struct_def
      char dummy31[sizeof (struct_decl_ptr)];

      // non_function_type
      // type
      // literal_type
      // int_lit_type
      // float_lit_type
      // list_type
      // func_type
      // nominal_type
      char dummy32[sizeof (type_ptr)];

      // INT
      char dummy33[sizeof (uint64_t)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    KEOF = 0,                      // KEOF
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    INT = 258,                     // INT
    FLOAT = 259,                   // FLOAT
    CHAR = 260,                    // CHAR
    STRING = 261,                  // STRING
    LABEL = 262,                   // LABEL
    CASE = 263,                    // CASE
    OF = 264,                      // OF
    DEFAULT = 265,                 // DEFAULT
    FUNC = 266,                    // FUNC
    LAMB = 267,                    // LAMB
    MARK = 268,                    // MARK
    ELSE = 269,                    // ELSE
    STRUCT = 270,                  // STRUCT
    ENUM = 271,                    // ENUM
    TRUE = 272,                    // TRUE
    FALSE = 273,                   // FALSE
    NIL = 274,                     // NIL
    READ = 275,                    // READ
    PRINT = 276,                   // PRINT
    RETURN = 277,                  // RETURN
    T_INT = 278,                   // T_INT
    T_LONG = 279,                  // T_LONG
    T_FLOAT = 280,                 // T_FLOAT
    T_DOUBLE = 281,                // T_DOUBLE
    T_CHAR = 282,                  // T_CHAR
    T_BOOL = 283,                  // T_BOOL
    LBRA = 284,                    // LBRA
    RBRA = 285,                    // RBRA
    SQ_LBRA = 286,                 // SQ_LBRA
    SQ_RBRA = 287,                 // SQ_RBRA
    C_LBRA = 288,                  // C_LBRA
    C_RBRA = 289,                  // C_RBRA
    COMMA = 290,                   // COMMA
    DOT = 291,                     // DOT
    TSEP = 292,                    // TSEP
    EMPTY = 293,                   // EMPTY
    PEND = 294,                    // PEND
    ASSGN = 295,                   // ASSGN
    ADD = 296,                     // ADD
    SUB = 297,                     // SUB
    MUL = 298,                     // MUL
    DIV = 299,                     // DIV
    MOD = 300,                     // MOD
    POW = 301,                     // POW
    FLR = 302,                     // FLR
    LAND = 303,                    // LAND
    BAR = 304,                     // BAR
    LXOR = 305,                    // LXOR
    LNEG = 306,                    // LNEG
    CGT = 307,                     // CGT
    CLT = 308,                     // CLT
    CGEQ = 309,                    // CGEQ
    CLEQ = 310,                    // CLEQ
    CEQ = 311,                     // CEQ
    CNEQ = 312,                    // CNEQ
    LSL = 313,                     // LSL
    LSR = 314,                     // LSR
    BAND = 315,                    // BAND
    BOR = 316,                     // BOR
    BNOT = 317,                    // BNOT
    CONCAT = 318,                  // CONCAT
    ARROW = 319,                   // ARROW
    PROD = 320                     // PROD
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 66, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // KEOF
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_INT = 3,                               // INT
        S_FLOAT = 4,                             // FLOAT
        S_CHAR = 5,                              // CHAR
        S_STRING = 6,                            // STRING
        S_LABEL = 7,                             // LABEL
        S_CASE = 8,                              // CASE
        S_OF = 9,                                // OF
        S_DEFAULT = 10,                          // DEFAULT
        S_FUNC = 11,                             // FUNC
        S_LAMB = 12,                             // LAMB
        S_MARK = 13,                             // MARK
        S_ELSE = 14,                             // ELSE
        S_STRUCT = 15,                           // STRUCT
        S_ENUM = 16,                             // ENUM
        S_TRUE = 17,                             // TRUE
        S_FALSE = 18,                            // FALSE
        S_NIL = 19,                              // NIL
        S_READ = 20,                             // READ
        S_PRINT = 21,                            // PRINT
        S_RETURN = 22,                           // RETURN
        S_T_INT = 23,                            // T_INT
        S_T_LONG = 24,                           // T_LONG
        S_T_FLOAT = 25,                          // T_FLOAT
        S_T_DOUBLE = 26,                         // T_DOUBLE
        S_T_CHAR = 27,                           // T_CHAR
        S_T_BOOL = 28,                           // T_BOOL
        S_LBRA = 29,                             // LBRA
        S_RBRA = 30,                             // RBRA
        S_SQ_LBRA = 31,                          // SQ_LBRA
        S_SQ_RBRA = 32,                          // SQ_RBRA
        S_C_LBRA = 33,                           // C_LBRA
        S_C_RBRA = 34,                           // C_RBRA
        S_COMMA = 35,                            // COMMA
        S_DOT = 36,                              // DOT
        S_TSEP = 37,                             // TSEP
        S_EMPTY = 38,                            // EMPTY
        S_PEND = 39,                             // PEND
        S_ASSGN = 40,                            // ASSGN
        S_ADD = 41,                              // ADD
        S_SUB = 42,                              // SUB
        S_MUL = 43,                              // MUL
        S_DIV = 44,                              // DIV
        S_MOD = 45,                              // MOD
        S_POW = 46,                              // POW
        S_FLR = 47,                              // FLR
        S_LAND = 48,                             // LAND
        S_BAR = 49,                              // BAR
        S_LXOR = 50,                             // LXOR
        S_LNEG = 51,                             // LNEG
        S_CGT = 52,                              // CGT
        S_CLT = 53,                              // CLT
        S_CGEQ = 54,                             // CGEQ
        S_CLEQ = 55,                             // CLEQ
        S_CEQ = 56,                              // CEQ
        S_CNEQ = 57,                             // CNEQ
        S_LSL = 58,                              // LSL
        S_LSR = 59,                              // LSR
        S_BAND = 60,                             // BAND
        S_BOR = 61,                              // BOR
        S_BNOT = 62,                             // BNOT
        S_CONCAT = 63,                           // CONCAT
        S_ARROW = 64,                            // ARROW
        S_PROD = 65,                             // PROD
        S_YYACCEPT = 66,                         // $accept
        S_module = 67,                           // module
        S_definitions = 68,                      // definitions
        S_definition = 69,                       // definition
        S_opt_types = 70,                        // opt_types
        S_types = 71,                            // types
        S_non_function_type = 72,                // non_function_type
        S_type = 73,                             // type
        S_literal_type = 74,                     // literal_type
        S_int_lit_type = 75,                     // int_lit_type
        S_float_lit_type = 76,                   // float_lit_type
        S_list_type = 77,                        // list_type
        S_func_type = 78,                        // func_type
        S_nominal_type = 79,                     // nominal_type
        S_opt_params = 80,                       // opt_params
        S_params = 81,                           // params
        S_param = 82,                            // param
        S_function_def = 83,                     // function_def
        S_fields = 84,                           // fields
        S_field = 85,                            // field
        S_struct_def = 86,                       // struct_def
        S_evar = 87,                             // evar
        S_evars = 88,                            // evars
        S_enum_def = 89,                         // enum_def
        S_program = 90,                          // program
        S_branch_expr = 91,                      // branch_expr
        S_guard_expr = 92,                       // guard_expr
        S_guards = 93,                           // guards
        S_guard = 94,                            // guard
        S_case_expr = 95,                        // case_expr
        S_patterns = 96,                         // patterns
        S_pattern_branch = 97,                   // pattern_branch
        S_literal = 98,                          // literal
        S_pattern = 99,                          // pattern
        S_enum_lit = 100,                        // enum_lit
        S_list_pattern = 101,                    // list_pattern
        S_string_lit = 102,                      // string_lit
        S_list_lit = 103,                        // list_lit
        S_list_pattern_lit = 104,                // list_pattern_lit
        S_size_patterns = 105,                   // size_patterns
        S_return_expr = 106,                     // return_expr
        S_helpers = 107,                         // helpers
        S_helper_expr = 108,                     // helper_expr
        S_print_expr = 109,                      // print_expr
        S_read_expr = 110,                       // read_expr
        S_assign_expr = 111,                     // assign_expr
        S_int_lit = 112,                         // int_lit
        S_float_lit = 113,                       // float_lit
        S_bool_lit = 114,                        // bool_lit
        S_char_lit = 115,                        // char_lit
        S_bool_op = 116,                         // bool_op
        S_comp_op = 117,                         // comp_op
        S_bitwise_op = 118,                      // bitwise_op
        S_shift_op = 119,                        // shift_op
        S_additive_op = 120,                     // additive_op
        S_mult_op = 121,                         // mult_op
        S_unary_op = 122,                        // unary_op
        S_nominal_expr = 123,                    // nominal_expr
        S_list_expr = 124,                       // list_expr
        S_empty_list = 125,                      // empty_list
        S_list_con = 126,                        // list_con
        S_expr_list = 127,                       // expr_list
        S_call_expr = 128,                       // call_expr
        S_struct_expr = 129,                     // struct_expr
        S_value_expr = 130,                      // value_expr
        S_bool_expr = 131,                       // bool_expr
        S_comp_expr = 132,                       // comp_expr
        S_bitwise_expr = 133,                    // bitwise_expr
        S_shift_expr = 134,                      // shift_expr
        S_additive_expr = 135,                   // additive_expr
        S_mult_expr = 136,                       // mult_expr
        S_pow_expr = 137,                        // pow_expr
        S_unary_expr = 138,                      // unary_expr
        S_postfix_expr = 139,                    // postfix_expr
        S_literal_expr = 140                     // literal_expr
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_bool_op: // bool_op
      case symbol_kind::S_comp_op: // comp_op
      case symbol_kind::S_bitwise_op: // bitwise_op
      case symbol_kind::S_shift_op: // shift_op
      case symbol_kind::S_additive_op: // additive_op
      case symbol_kind::S_mult_op: // mult_op
        value.move< BinaryOp > (std::move (that.value));
        break;

      case symbol_kind::S_field: // field
        value.move< Field > (std::move (that.value));
        break;

      case symbol_kind::S_param: // param
        value.move< Param > (std::move (that.value));
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.move< UnaryOp > (std::move (that.value));
        break;

      case symbol_kind::S_pattern_branch: // pattern_branch
        value.move< c_branch_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.move< case_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.move< char > (std::move (that.value));
        break;

      case symbol_kind::S_definition: // definition
      case symbol_kind::S_helper_expr: // helper_expr
      case symbol_kind::S_assign_expr: // assign_expr
        value.move< decl_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.move< double > (std::move (that.value));
        break;

      case symbol_kind::S_enum_def: // enum_def
        value.move< enum_decl_ptr > (std::move (that.value));
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
        value.move< expr_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_function_def: // function_def
        value.move< func_decl_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_guard: // guard
        value.move< g_branch_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_guard_expr: // guard_expr
        value.move< guard_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_empty_list: // empty_list
      case symbol_kind::S_list_con: // list_con
        value.move< list_ptr > (std::move (that.value));
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
        value.move< literal_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_module: // module
        value.move< module_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_print_expr: // print_expr
        value.move< print_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< prog_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_read_expr: // read_expr
        value.move< read_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_LABEL: // LABEL
      case symbol_kind::S_evar: // evar
        value.move< std::string > (std::move (that.value));
        break;

      case symbol_kind::S_fields: // fields
        value.move< std::vector<Field> > (std::move (that.value));
        break;

      case symbol_kind::S_opt_params: // opt_params
      case symbol_kind::S_params: // params
        value.move< std::vector<Param> > (std::move (that.value));
        break;

      case symbol_kind::S_patterns: // patterns
        value.move< std::vector<c_branch_ptr> > (std::move (that.value));
        break;

      case symbol_kind::S_definitions: // definitions
      case symbol_kind::S_helpers: // helpers
        value.move< std::vector<decl_ptr> > (std::move (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< std::vector<expr_ptr> > (std::move (that.value));
        break;

      case symbol_kind::S_guards: // guards
        value.move< std::vector<g_branch_ptr> > (std::move (that.value));
        break;

      case symbol_kind::S_list_pattern_lit: // list_pattern_lit
        value.move< std::vector<literal_ptr> > (std::move (that.value));
        break;

      case symbol_kind::S_evars: // evars
      case symbol_kind::S_size_patterns: // size_patterns
        value.move< std::vector<std::string> > (std::move (that.value));
        break;

      case symbol_kind::S_opt_types: // opt_types
      case symbol_kind::S_types: // types
        value.move< std::vector<type_ptr> > (std::move (that.value));
        break;

      case symbol_kind::S_struct_def: // struct_def
        value.move< struct_decl_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_non_function_type: // non_function_type
      case symbol_kind::S_type: // type
      case symbol_kind::S_literal_type: // literal_type
      case symbol_kind::S_int_lit_type: // int_lit_type
      case symbol_kind::S_float_lit_type: // float_lit_type
      case symbol_kind::S_list_type: // list_type
      case symbol_kind::S_func_type: // func_type
      case symbol_kind::S_nominal_type: // nominal_type
        value.move< type_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< uint64_t > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, BinaryOp&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const BinaryOp& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Field&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Field& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Param&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Param& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, UnaryOp&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const UnaryOp& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, c_branch_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const c_branch_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, case_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const case_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, char&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const char& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, decl_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const decl_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, double&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const double& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, enum_decl_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const enum_decl_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, expr_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const expr_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, func_decl_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const func_decl_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, g_branch_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const g_branch_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, guard_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const guard_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, list_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const list_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, literal_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const literal_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, module_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const module_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, print_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const print_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, prog_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const prog_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, read_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const read_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<Field>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<Field>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<Param>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<Param>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<c_branch_ptr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<c_branch_ptr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<decl_ptr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<decl_ptr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<expr_ptr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<expr_ptr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<g_branch_ptr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<g_branch_ptr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<literal_ptr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<literal_ptr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<std::string>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<std::string>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<type_ptr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<type_ptr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, struct_decl_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const struct_decl_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, type_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const type_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, uint64_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const uint64_t& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_bool_op: // bool_op
      case symbol_kind::S_comp_op: // comp_op
      case symbol_kind::S_bitwise_op: // bitwise_op
      case symbol_kind::S_shift_op: // shift_op
      case symbol_kind::S_additive_op: // additive_op
      case symbol_kind::S_mult_op: // mult_op
        value.template destroy< BinaryOp > ();
        break;

      case symbol_kind::S_field: // field
        value.template destroy< Field > ();
        break;

      case symbol_kind::S_param: // param
        value.template destroy< Param > ();
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.template destroy< UnaryOp > ();
        break;

      case symbol_kind::S_pattern_branch: // pattern_branch
        value.template destroy< c_branch_ptr > ();
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.template destroy< case_ptr > ();
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.template destroy< char > ();
        break;

      case symbol_kind::S_definition: // definition
      case symbol_kind::S_helper_expr: // helper_expr
      case symbol_kind::S_assign_expr: // assign_expr
        value.template destroy< decl_ptr > ();
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.template destroy< double > ();
        break;

      case symbol_kind::S_enum_def: // enum_def
        value.template destroy< enum_decl_ptr > ();
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
        value.template destroy< expr_ptr > ();
        break;

      case symbol_kind::S_function_def: // function_def
        value.template destroy< func_decl_ptr > ();
        break;

      case symbol_kind::S_guard: // guard
        value.template destroy< g_branch_ptr > ();
        break;

      case symbol_kind::S_guard_expr: // guard_expr
        value.template destroy< guard_ptr > ();
        break;

      case symbol_kind::S_empty_list: // empty_list
      case symbol_kind::S_list_con: // list_con
        value.template destroy< list_ptr > ();
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
        value.template destroy< literal_ptr > ();
        break;

      case symbol_kind::S_module: // module
        value.template destroy< module_ptr > ();
        break;

      case symbol_kind::S_print_expr: // print_expr
        value.template destroy< print_ptr > ();
        break;

      case symbol_kind::S_program: // program
        value.template destroy< prog_ptr > ();
        break;

      case symbol_kind::S_read_expr: // read_expr
        value.template destroy< read_ptr > ();
        break;

      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_LABEL: // LABEL
      case symbol_kind::S_evar: // evar
        value.template destroy< std::string > ();
        break;

      case symbol_kind::S_fields: // fields
        value.template destroy< std::vector<Field> > ();
        break;

      case symbol_kind::S_opt_params: // opt_params
      case symbol_kind::S_params: // params
        value.template destroy< std::vector<Param> > ();
        break;

      case symbol_kind::S_patterns: // patterns
        value.template destroy< std::vector<c_branch_ptr> > ();
        break;

      case symbol_kind::S_definitions: // definitions
      case symbol_kind::S_helpers: // helpers
        value.template destroy< std::vector<decl_ptr> > ();
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.template destroy< std::vector<expr_ptr> > ();
        break;

      case symbol_kind::S_guards: // guards
        value.template destroy< std::vector<g_branch_ptr> > ();
        break;

      case symbol_kind::S_list_pattern_lit: // list_pattern_lit
        value.template destroy< std::vector<literal_ptr> > ();
        break;

      case symbol_kind::S_evars: // evars
      case symbol_kind::S_size_patterns: // size_patterns
        value.template destroy< std::vector<std::string> > ();
        break;

      case symbol_kind::S_opt_types: // opt_types
      case symbol_kind::S_types: // types
        value.template destroy< std::vector<type_ptr> > ();
        break;

      case symbol_kind::S_struct_def: // struct_def
        value.template destroy< struct_decl_ptr > ();
        break;

      case symbol_kind::S_non_function_type: // non_function_type
      case symbol_kind::S_type: // type
      case symbol_kind::S_literal_type: // literal_type
      case symbol_kind::S_int_lit_type: // int_lit_type
      case symbol_kind::S_float_lit_type: // float_lit_type
      case symbol_kind::S_list_type: // list_type
      case symbol_kind::S_func_type: // func_type
      case symbol_kind::S_nominal_type: // nominal_type
        value.template destroy< type_ptr > ();
        break;

      case symbol_kind::S_INT: // INT
        value.template destroy< uint64_t > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

#if YYDEBUG || 0
      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }
#endif // #if YYDEBUG || 0


      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type (token_kind_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type (token_kind_type (tok), l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, char v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const char& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, double v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const double& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, uint64_t v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const uint64_t& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
    };

    /// Build a parser object.
    parser ();
    virtual ~parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser (const parser&) = delete;
    /// Non copyable.
    parser& operator= (const parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

#if YYDEBUG || 0
    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);
#endif // #if YYDEBUG || 0


    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEOF (location_type l)
      {
        return symbol_type (token::KEOF, std::move (l));
      }
#else
      static
      symbol_type
      make_KEOF (const location_type& l)
      {
        return symbol_type (token::KEOF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT (uint64_t v, location_type l)
      {
        return symbol_type (token::INT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INT (const uint64_t& v, const location_type& l)
      {
        return symbol_type (token::INT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT (double v, location_type l)
      {
        return symbol_type (token::FLOAT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FLOAT (const double& v, const location_type& l)
      {
        return symbol_type (token::FLOAT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHAR (char v, location_type l)
      {
        return symbol_type (token::CHAR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CHAR (const char& v, const location_type& l)
      {
        return symbol_type (token::CHAR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING (std::string v, location_type l)
      {
        return symbol_type (token::STRING, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STRING (const std::string& v, const location_type& l)
      {
        return symbol_type (token::STRING, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LABEL (std::string v, location_type l)
      {
        return symbol_type (token::LABEL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LABEL (const std::string& v, const location_type& l)
      {
        return symbol_type (token::LABEL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CASE (location_type l)
      {
        return symbol_type (token::CASE, std::move (l));
      }
#else
      static
      symbol_type
      make_CASE (const location_type& l)
      {
        return symbol_type (token::CASE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OF (location_type l)
      {
        return symbol_type (token::OF, std::move (l));
      }
#else
      static
      symbol_type
      make_OF (const location_type& l)
      {
        return symbol_type (token::OF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEFAULT (location_type l)
      {
        return symbol_type (token::DEFAULT, std::move (l));
      }
#else
      static
      symbol_type
      make_DEFAULT (const location_type& l)
      {
        return symbol_type (token::DEFAULT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FUNC (location_type l)
      {
        return symbol_type (token::FUNC, std::move (l));
      }
#else
      static
      symbol_type
      make_FUNC (const location_type& l)
      {
        return symbol_type (token::FUNC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LAMB (location_type l)
      {
        return symbol_type (token::LAMB, std::move (l));
      }
#else
      static
      symbol_type
      make_LAMB (const location_type& l)
      {
        return symbol_type (token::LAMB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MARK (location_type l)
      {
        return symbol_type (token::MARK, std::move (l));
      }
#else
      static
      symbol_type
      make_MARK (const location_type& l)
      {
        return symbol_type (token::MARK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE (location_type l)
      {
        return symbol_type (token::ELSE, std::move (l));
      }
#else
      static
      symbol_type
      make_ELSE (const location_type& l)
      {
        return symbol_type (token::ELSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRUCT (location_type l)
      {
        return symbol_type (token::STRUCT, std::move (l));
      }
#else
      static
      symbol_type
      make_STRUCT (const location_type& l)
      {
        return symbol_type (token::STRUCT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENUM (location_type l)
      {
        return symbol_type (token::ENUM, std::move (l));
      }
#else
      static
      symbol_type
      make_ENUM (const location_type& l)
      {
        return symbol_type (token::ENUM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TRUE (location_type l)
      {
        return symbol_type (token::TRUE, std::move (l));
      }
#else
      static
      symbol_type
      make_TRUE (const location_type& l)
      {
        return symbol_type (token::TRUE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FALSE (location_type l)
      {
        return symbol_type (token::FALSE, std::move (l));
      }
#else
      static
      symbol_type
      make_FALSE (const location_type& l)
      {
        return symbol_type (token::FALSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NIL (location_type l)
      {
        return symbol_type (token::NIL, std::move (l));
      }
#else
      static
      symbol_type
      make_NIL (const location_type& l)
      {
        return symbol_type (token::NIL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_READ (location_type l)
      {
        return symbol_type (token::READ, std::move (l));
      }
#else
      static
      symbol_type
      make_READ (const location_type& l)
      {
        return symbol_type (token::READ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PRINT (location_type l)
      {
        return symbol_type (token::PRINT, std::move (l));
      }
#else
      static
      symbol_type
      make_PRINT (const location_type& l)
      {
        return symbol_type (token::PRINT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETURN (location_type l)
      {
        return symbol_type (token::RETURN, std::move (l));
      }
#else
      static
      symbol_type
      make_RETURN (const location_type& l)
      {
        return symbol_type (token::RETURN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_INT (location_type l)
      {
        return symbol_type (token::T_INT, std::move (l));
      }
#else
      static
      symbol_type
      make_T_INT (const location_type& l)
      {
        return symbol_type (token::T_INT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_LONG (location_type l)
      {
        return symbol_type (token::T_LONG, std::move (l));
      }
#else
      static
      symbol_type
      make_T_LONG (const location_type& l)
      {
        return symbol_type (token::T_LONG, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_FLOAT (location_type l)
      {
        return symbol_type (token::T_FLOAT, std::move (l));
      }
#else
      static
      symbol_type
      make_T_FLOAT (const location_type& l)
      {
        return symbol_type (token::T_FLOAT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_DOUBLE (location_type l)
      {
        return symbol_type (token::T_DOUBLE, std::move (l));
      }
#else
      static
      symbol_type
      make_T_DOUBLE (const location_type& l)
      {
        return symbol_type (token::T_DOUBLE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_CHAR (location_type l)
      {
        return symbol_type (token::T_CHAR, std::move (l));
      }
#else
      static
      symbol_type
      make_T_CHAR (const location_type& l)
      {
        return symbol_type (token::T_CHAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_BOOL (location_type l)
      {
        return symbol_type (token::T_BOOL, std::move (l));
      }
#else
      static
      symbol_type
      make_T_BOOL (const location_type& l)
      {
        return symbol_type (token::T_BOOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRA (location_type l)
      {
        return symbol_type (token::LBRA, std::move (l));
      }
#else
      static
      symbol_type
      make_LBRA (const location_type& l)
      {
        return symbol_type (token::LBRA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRA (location_type l)
      {
        return symbol_type (token::RBRA, std::move (l));
      }
#else
      static
      symbol_type
      make_RBRA (const location_type& l)
      {
        return symbol_type (token::RBRA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SQ_LBRA (location_type l)
      {
        return symbol_type (token::SQ_LBRA, std::move (l));
      }
#else
      static
      symbol_type
      make_SQ_LBRA (const location_type& l)
      {
        return symbol_type (token::SQ_LBRA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SQ_RBRA (location_type l)
      {
        return symbol_type (token::SQ_RBRA, std::move (l));
      }
#else
      static
      symbol_type
      make_SQ_RBRA (const location_type& l)
      {
        return symbol_type (token::SQ_RBRA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_C_LBRA (location_type l)
      {
        return symbol_type (token::C_LBRA, std::move (l));
      }
#else
      static
      symbol_type
      make_C_LBRA (const location_type& l)
      {
        return symbol_type (token::C_LBRA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_C_RBRA (location_type l)
      {
        return symbol_type (token::C_RBRA, std::move (l));
      }
#else
      static
      symbol_type
      make_C_RBRA (const location_type& l)
      {
        return symbol_type (token::C_RBRA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (location_type l)
      {
        return symbol_type (token::COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const location_type& l)
      {
        return symbol_type (token::COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOT (location_type l)
      {
        return symbol_type (token::DOT, std::move (l));
      }
#else
      static
      symbol_type
      make_DOT (const location_type& l)
      {
        return symbol_type (token::DOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TSEP (location_type l)
      {
        return symbol_type (token::TSEP, std::move (l));
      }
#else
      static
      symbol_type
      make_TSEP (const location_type& l)
      {
        return symbol_type (token::TSEP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EMPTY (location_type l)
      {
        return symbol_type (token::EMPTY, std::move (l));
      }
#else
      static
      symbol_type
      make_EMPTY (const location_type& l)
      {
        return symbol_type (token::EMPTY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PEND (location_type l)
      {
        return symbol_type (token::PEND, std::move (l));
      }
#else
      static
      symbol_type
      make_PEND (const location_type& l)
      {
        return symbol_type (token::PEND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSGN (location_type l)
      {
        return symbol_type (token::ASSGN, std::move (l));
      }
#else
      static
      symbol_type
      make_ASSGN (const location_type& l)
      {
        return symbol_type (token::ASSGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ADD (location_type l)
      {
        return symbol_type (token::ADD, std::move (l));
      }
#else
      static
      symbol_type
      make_ADD (const location_type& l)
      {
        return symbol_type (token::ADD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB (location_type l)
      {
        return symbol_type (token::SUB, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB (const location_type& l)
      {
        return symbol_type (token::SUB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MUL (location_type l)
      {
        return symbol_type (token::MUL, std::move (l));
      }
#else
      static
      symbol_type
      make_MUL (const location_type& l)
      {
        return symbol_type (token::MUL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIV (location_type l)
      {
        return symbol_type (token::DIV, std::move (l));
      }
#else
      static
      symbol_type
      make_DIV (const location_type& l)
      {
        return symbol_type (token::DIV, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MOD (location_type l)
      {
        return symbol_type (token::MOD, std::move (l));
      }
#else
      static
      symbol_type
      make_MOD (const location_type& l)
      {
        return symbol_type (token::MOD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_POW (location_type l)
      {
        return symbol_type (token::POW, std::move (l));
      }
#else
      static
      symbol_type
      make_POW (const location_type& l)
      {
        return symbol_type (token::POW, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLR (location_type l)
      {
        return symbol_type (token::FLR, std::move (l));
      }
#else
      static
      symbol_type
      make_FLR (const location_type& l)
      {
        return symbol_type (token::FLR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LAND (location_type l)
      {
        return symbol_type (token::LAND, std::move (l));
      }
#else
      static
      symbol_type
      make_LAND (const location_type& l)
      {
        return symbol_type (token::LAND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BAR (location_type l)
      {
        return symbol_type (token::BAR, std::move (l));
      }
#else
      static
      symbol_type
      make_BAR (const location_type& l)
      {
        return symbol_type (token::BAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LXOR (location_type l)
      {
        return symbol_type (token::LXOR, std::move (l));
      }
#else
      static
      symbol_type
      make_LXOR (const location_type& l)
      {
        return symbol_type (token::LXOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LNEG (location_type l)
      {
        return symbol_type (token::LNEG, std::move (l));
      }
#else
      static
      symbol_type
      make_LNEG (const location_type& l)
      {
        return symbol_type (token::LNEG, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CGT (location_type l)
      {
        return symbol_type (token::CGT, std::move (l));
      }
#else
      static
      symbol_type
      make_CGT (const location_type& l)
      {
        return symbol_type (token::CGT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLT (location_type l)
      {
        return symbol_type (token::CLT, std::move (l));
      }
#else
      static
      symbol_type
      make_CLT (const location_type& l)
      {
        return symbol_type (token::CLT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CGEQ (location_type l)
      {
        return symbol_type (token::CGEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_CGEQ (const location_type& l)
      {
        return symbol_type (token::CGEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLEQ (location_type l)
      {
        return symbol_type (token::CLEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_CLEQ (const location_type& l)
      {
        return symbol_type (token::CLEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CEQ (location_type l)
      {
        return symbol_type (token::CEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_CEQ (const location_type& l)
      {
        return symbol_type (token::CEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CNEQ (location_type l)
      {
        return symbol_type (token::CNEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_CNEQ (const location_type& l)
      {
        return symbol_type (token::CNEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LSL (location_type l)
      {
        return symbol_type (token::LSL, std::move (l));
      }
#else
      static
      symbol_type
      make_LSL (const location_type& l)
      {
        return symbol_type (token::LSL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LSR (location_type l)
      {
        return symbol_type (token::LSR, std::move (l));
      }
#else
      static
      symbol_type
      make_LSR (const location_type& l)
      {
        return symbol_type (token::LSR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BAND (location_type l)
      {
        return symbol_type (token::BAND, std::move (l));
      }
#else
      static
      symbol_type
      make_BAND (const location_type& l)
      {
        return symbol_type (token::BAND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOR (location_type l)
      {
        return symbol_type (token::BOR, std::move (l));
      }
#else
      static
      symbol_type
      make_BOR (const location_type& l)
      {
        return symbol_type (token::BOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BNOT (location_type l)
      {
        return symbol_type (token::BNOT, std::move (l));
      }
#else
      static
      symbol_type
      make_BNOT (const location_type& l)
      {
        return symbol_type (token::BNOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONCAT (location_type l)
      {
        return symbol_type (token::CONCAT, std::move (l));
      }
#else
      static
      symbol_type
      make_CONCAT (const location_type& l)
      {
        return symbol_type (token::CONCAT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARROW (location_type l)
      {
        return symbol_type (token::ARROW, std::move (l));
      }
#else
      static
      symbol_type
      make_ARROW (const location_type& l)
      {
        return symbol_type (token::ARROW, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PROD (location_type l)
      {
        return symbol_type (token::PROD, std::move (l));
      }
#else
      static
      symbol_type
      make_PROD (const location_type& l)
      {
        return symbol_type (token::PROD, l);
      }
#endif


  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

#if YYDEBUG || 0
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif // #if YYDEBUG || 0


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const unsigned char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const unsigned char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const unsigned char yytable_[];

    static const unsigned char yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const unsigned char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const unsigned char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 272,     ///< Last index in yytable_.
      yynnts_ = 75,  ///< Number of nonterminal symbols.
      yyfinal_ = 3 ///< Termination state number.
    };



  };

  inline
  parser::symbol_kind_type
  parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65
    };
    // Last valid token kind.
    const int code_max = 320;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_bool_op: // bool_op
      case symbol_kind::S_comp_op: // comp_op
      case symbol_kind::S_bitwise_op: // bitwise_op
      case symbol_kind::S_shift_op: // shift_op
      case symbol_kind::S_additive_op: // additive_op
      case symbol_kind::S_mult_op: // mult_op
        value.copy< BinaryOp > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field: // field
        value.copy< Field > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.copy< Param > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.copy< UnaryOp > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_pattern_branch: // pattern_branch
        value.copy< c_branch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.copy< case_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.copy< char > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
      case symbol_kind::S_helper_expr: // helper_expr
      case symbol_kind::S_assign_expr: // assign_expr
        value.copy< decl_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.copy< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_def: // enum_def
        value.copy< enum_decl_ptr > (YY_MOVE (that.value));
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
        value.copy< expr_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_def: // function_def
        value.copy< func_decl_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_guard: // guard
        value.copy< g_branch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_guard_expr: // guard_expr
        value.copy< guard_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_empty_list: // empty_list
      case symbol_kind::S_list_con: // list_con
        value.copy< list_ptr > (YY_MOVE (that.value));
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
        value.copy< literal_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_module: // module
        value.copy< module_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_print_expr: // print_expr
        value.copy< print_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.copy< prog_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_read_expr: // read_expr
        value.copy< read_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_LABEL: // LABEL
      case symbol_kind::S_evar: // evar
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fields: // fields
        value.copy< std::vector<Field> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_params: // opt_params
      case symbol_kind::S_params: // params
        value.copy< std::vector<Param> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_patterns: // patterns
        value.copy< std::vector<c_branch_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definitions: // definitions
      case symbol_kind::S_helpers: // helpers
        value.copy< std::vector<decl_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.copy< std::vector<expr_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_guards: // guards
        value.copy< std::vector<g_branch_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_list_pattern_lit: // list_pattern_lit
        value.copy< std::vector<literal_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_evars: // evars
      case symbol_kind::S_size_patterns: // size_patterns
        value.copy< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_types: // opt_types
      case symbol_kind::S_types: // types
        value.copy< std::vector<type_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_def: // struct_def
        value.copy< struct_decl_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_non_function_type: // non_function_type
      case symbol_kind::S_type: // type
      case symbol_kind::S_literal_type: // literal_type
      case symbol_kind::S_int_lit_type: // int_lit_type
      case symbol_kind::S_float_lit_type: // float_lit_type
      case symbol_kind::S_list_type: // list_type
      case symbol_kind::S_func_type: // func_type
      case symbol_kind::S_nominal_type: // nominal_type
        value.copy< type_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.copy< uint64_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_bool_op: // bool_op
      case symbol_kind::S_comp_op: // comp_op
      case symbol_kind::S_bitwise_op: // bitwise_op
      case symbol_kind::S_shift_op: // shift_op
      case symbol_kind::S_additive_op: // additive_op
      case symbol_kind::S_mult_op: // mult_op
        value.move< BinaryOp > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_field: // field
        value.move< Field > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_param: // param
        value.move< Param > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.move< UnaryOp > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_pattern_branch: // pattern_branch
        value.move< c_branch_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.move< case_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.move< char > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_definition: // definition
      case symbol_kind::S_helper_expr: // helper_expr
      case symbol_kind::S_assign_expr: // assign_expr
        value.move< decl_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.move< double > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_enum_def: // enum_def
        value.move< enum_decl_ptr > (YY_MOVE (s.value));
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
        value.move< expr_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_function_def: // function_def
        value.move< func_decl_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_guard: // guard
        value.move< g_branch_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_guard_expr: // guard_expr
        value.move< guard_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_empty_list: // empty_list
      case symbol_kind::S_list_con: // list_con
        value.move< list_ptr > (YY_MOVE (s.value));
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
        value.move< literal_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_module: // module
        value.move< module_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_print_expr: // print_expr
        value.move< print_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_program: // program
        value.move< prog_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_read_expr: // read_expr
        value.move< read_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_LABEL: // LABEL
      case symbol_kind::S_evar: // evar
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_fields: // fields
        value.move< std::vector<Field> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_opt_params: // opt_params
      case symbol_kind::S_params: // params
        value.move< std::vector<Param> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_patterns: // patterns
        value.move< std::vector<c_branch_ptr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_definitions: // definitions
      case symbol_kind::S_helpers: // helpers
        value.move< std::vector<decl_ptr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< std::vector<expr_ptr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_guards: // guards
        value.move< std::vector<g_branch_ptr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_list_pattern_lit: // list_pattern_lit
        value.move< std::vector<literal_ptr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_evars: // evars
      case symbol_kind::S_size_patterns: // size_patterns
        value.move< std::vector<std::string> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_opt_types: // opt_types
      case symbol_kind::S_types: // types
        value.move< std::vector<type_ptr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_struct_def: // struct_def
        value.move< struct_decl_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_non_function_type: // non_function_type
      case symbol_kind::S_type: // type
      case symbol_kind::S_literal_type: // literal_type
      case symbol_kind::S_int_lit_type: // int_lit_type
      case symbol_kind::S_float_lit_type: // float_lit_type
      case symbol_kind::S_list_type: // list_type
      case symbol_kind::S_func_type: // func_type
      case symbol_kind::S_nominal_type: // nominal_type
        value.move< type_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< uint64_t > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


#line 39 "src/parser.y"
} // yy
#line 3705 "parser.hpp"




#endif // !YY_YY_PARSER_HPP_INCLUDED
