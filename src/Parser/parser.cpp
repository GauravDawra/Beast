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
#line 1 "main.ypp"


// g++-11 lex.yy.cpp main.tab.cpp -D__EXTERN_C__ -ly -ll -o main
// g++-11 lex.yy.cc parser.cpp -o main -lfl -I/opt/homebrew/opt/flex/include -L/opt/homebrew/opt/flex/lib
// #include <iostream>
// #include <vector>
#include <string>
#include "scanner.h"
#include "Memory.h"
#include "Logger.h"
#include "Error.h"
extern "C" {
    int yywrap(yyscan_t yyscanner) { return 1; }
};

extern "C" int line_num;

static Beast::BuildRule s_ScratchTable;
static std::vector<std::string> s_ScratchBuildShellCommands;

#line 62 "parser.cpp"


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

#line 26 "main.ypp"
namespace Beast {
#line 160 "parser.cpp"

  /// Build a parser object.
  Parser::Parser (yyscan_t scanner_yyarg, Beast::BuildFile& buildFile_yyarg, Beast::Parser::location_type& loc_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      buildFile (buildFile_yyarg),
      loc (loc_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_build_grp: // build_grp
        value.copy< Beast::BuildRule > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.copy< MULTI_TYPE > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        value.copy< assign_type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_build_head: // build_head
        value.copy< io_dependancy > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_WORD: // WORD
      case symbol_kind::S_DEREF: // DEREF
      case symbol_kind::S_COMMAND: // COMMAND
      case symbol_kind::S_FILENAME: // FILENAME
      case symbol_kind::S_STRING_LIT: // STRING_LIT
      case symbol_kind::S_file: // file
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_build_head_file_list: // build_head_file_list
      case symbol_kind::S_build_cmds: // build_cmds
        value.copy< string_list > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_build_grp: // build_grp
        value.move< Beast::BuildRule > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr: // expr
        value.move< MULTI_TYPE > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        value.move< assign_type > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_build_head: // build_head
        value.move< io_dependancy > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_WORD: // WORD
      case symbol_kind::S_DEREF: // DEREF
      case symbol_kind::S_COMMAND: // COMMAND
      case symbol_kind::S_FILENAME: // FILENAME
      case symbol_kind::S_STRING_LIT: // STRING_LIT
      case symbol_kind::S_file: // file
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_build_head_file_list: // build_head_file_list
      case symbol_kind::S_build_cmds: // build_cmds
        value.move< string_list > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_build_grp: // build_grp
        value.YY_MOVE_OR_COPY< Beast::BuildRule > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.YY_MOVE_OR_COPY< MULTI_TYPE > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        value.YY_MOVE_OR_COPY< assign_type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_build_head: // build_head
        value.YY_MOVE_OR_COPY< io_dependancy > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_WORD: // WORD
      case symbol_kind::S_DEREF: // DEREF
      case symbol_kind::S_COMMAND: // COMMAND
      case symbol_kind::S_FILENAME: // FILENAME
      case symbol_kind::S_STRING_LIT: // STRING_LIT
      case symbol_kind::S_file: // file
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_build_head_file_list: // build_head_file_list
      case symbol_kind::S_build_cmds: // build_cmds
        value.YY_MOVE_OR_COPY< string_list > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_build_grp: // build_grp
        value.move< Beast::BuildRule > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.move< MULTI_TYPE > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        value.move< assign_type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_build_head: // build_head
        value.move< io_dependancy > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_WORD: // WORD
      case symbol_kind::S_DEREF: // DEREF
      case symbol_kind::S_COMMAND: // COMMAND
      case symbol_kind::S_FILENAME: // FILENAME
      case symbol_kind::S_STRING_LIT: // STRING_LIT
      case symbol_kind::S_file: // file
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_build_head_file_list: // build_head_file_list
      case symbol_kind::S_build_cmds: // build_cmds
        value.move< string_list > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_build_grp: // build_grp
        value.copy< Beast::BuildRule > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.copy< MULTI_TYPE > (that.value);
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        value.copy< assign_type > (that.value);
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_build_head: // build_head
        value.copy< io_dependancy > (that.value);
        break;

      case symbol_kind::S_WORD: // WORD
      case symbol_kind::S_DEREF: // DEREF
      case symbol_kind::S_COMMAND: // COMMAND
      case symbol_kind::S_FILENAME: // FILENAME
      case symbol_kind::S_STRING_LIT: // STRING_LIT
      case symbol_kind::S_file: // file
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_build_head_file_list: // build_head_file_list
      case symbol_kind::S_build_cmds: // build_cmds
        value.copy< string_list > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_build_grp: // build_grp
        value.move< Beast::BuildRule > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.move< MULTI_TYPE > (that.value);
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        value.move< assign_type > (that.value);
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.move< int > (that.value);
        break;

      case symbol_kind::S_build_head: // build_head
        value.move< io_dependancy > (that.value);
        break;

      case symbol_kind::S_WORD: // WORD
      case symbol_kind::S_DEREF: // DEREF
      case symbol_kind::S_COMMAND: // COMMAND
      case symbol_kind::S_FILENAME: // FILENAME
      case symbol_kind::S_STRING_LIT: // STRING_LIT
      case symbol_kind::S_file: // file
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_build_head_file_list: // build_head_file_list
      case symbol_kind::S_build_cmds: // build_cmds
        value.move< string_list > (that.value);
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
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
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
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location, scanner));
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
      case symbol_kind::S_build_grp: // build_grp
        yylhs.value.emplace< Beast::BuildRule > ();
        break;

      case symbol_kind::S_expr: // expr
        yylhs.value.emplace< MULTI_TYPE > ();
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        yylhs.value.emplace< assign_type > ();
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_build_head: // build_head
        yylhs.value.emplace< io_dependancy > ();
        break;

      case symbol_kind::S_WORD: // WORD
      case symbol_kind::S_DEREF: // DEREF
      case symbol_kind::S_COMMAND: // COMMAND
      case symbol_kind::S_FILENAME: // FILENAME
      case symbol_kind::S_STRING_LIT: // STRING_LIT
      case symbol_kind::S_file: // file
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_build_head_file_list: // build_head_file_list
      case symbol_kind::S_build_cmds: // build_cmds
        yylhs.value.emplace< string_list > ();
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
  case 2: // stmts: %empty
#line 88 "main.ypp"
                            {;}
#line 889 "parser.cpp"
    break;

  case 3: // stmts: stmts stmt
#line 89 "main.ypp"
                            {LOG_DEBUG("STMT detected " + std::to_string(line_num));}
#line 895 "parser.cpp"
    break;

  case 4: // stmt: build_grp
#line 93 "main.ypp"
                             {;}
#line 901 "parser.cpp"
    break;

  case 5: // stmt: assign_stmt ENDL
#line 95 "main.ypp"
                             {buildFile.set(yystack_[1].value.as < assign_type > ().first, yystack_[1].value.as < assign_type > ().second);}
#line 907 "parser.cpp"
    break;

  case 7: // build_grp: build_head ENDL build_cmds
#line 100 "main.ypp"
                                    {
        LOG_DEBUG("BUILD detected for " + yystack_[2].value.as < io_dependancy > ().first);
        // $$.setTable(s_ScratchTable);
        // $$.setDependencies($1.first, $1.second);
        // $$.setCommands(s_ScratchBuildShellCommands);
        s_ScratchTable.setCommands(s_ScratchBuildShellCommands); // newly added
        // buildFile.addBuildRule($$);
        buildFile.addBuildRule(s_ScratchTable);
        s_ScratchTable.clear();
        s_ScratchBuildShellCommands.clear();
        yylhs.location = yystack_[2].location;
    }
#line 924 "parser.cpp"
    break;

  case 8: // build_head: BUILD build_head_file_list COLON build_head_file_list
#line 115 "main.ypp"
                                                          {
            if (yystack_[2].value.as < string_list > ().size() != 1) 
                error(yystack_[2].location, "exactly one output target is required");
            yylhs.value.as < io_dependancy > ().first = yystack_[2].value.as < string_list > () [0];
            yylhs.value.as < io_dependancy > ().second = yystack_[0].value.as < string_list > ();
            s_ScratchTable.setDependencies(yylhs.value.as < io_dependancy > ().first, yylhs.value.as < io_dependancy > ().second);
            LOG_DEBUG("build head detected for " + yystack_[2].value.as < string_list > () [0]);
            yylhs.location = yystack_[3].location;
        }
#line 938 "parser.cpp"
    break;

  case 10: // build_head_file_list: build_head_file_list file
#line 127 "main.ypp"
                                        {yylhs.value.as < string_list > () = yystack_[1].value.as < string_list > (); yylhs.value.as < string_list > ().push_back(yystack_[0].value.as < std::string > ());}
#line 944 "parser.cpp"
    break;

  case 11: // file: WORD
#line 137 "main.ypp"
                                                                        {yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); buildFile.resolve(yylhs.value.as < std::string > (), SymbolTable());}
#line 950 "parser.cpp"
    break;

  case 12: // file: FILENAME
#line 138 "main.ypp"
                                            {yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); buildFile.resolve(yylhs.value.as < std::string > (), SymbolTable());}
#line 956 "parser.cpp"
    break;

  case 13: // file: STRING_LIT
#line 139 "main.ypp"
                                            {yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); buildFile.resolve(yylhs.value.as < std::string > (), SymbolTable());}
#line 962 "parser.cpp"
    break;

  case 14: // file: DEREF
#line 140 "main.ypp"
                                            {yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); buildFile.resolve(yylhs.value.as < std::string > (), SymbolTable());}
#line 968 "parser.cpp"
    break;

  case 15: // file: BUILD
#line 141 "main.ypp"
                                        {yylhs.value.as < std::string > () = "build";}
#line 974 "parser.cpp"
    break;

  case 17: // build_cmds: build_cmds TAB COMMAND
#line 145 "main.ypp"
                                 {s_ScratchBuildShellCommands.push_back(yystack_[0].value.as < std::string > ()); }
#line 980 "parser.cpp"
    break;

  case 18: // build_cmds: build_cmds TAB assign_stmt
#line 147 "main.ypp"
                                 {s_ScratchTable.set(yystack_[0].value.as < assign_type > ().first, yystack_[0].value.as < assign_type > ().second);}
#line 986 "parser.cpp"
    break;

  case 19: // build_cmds: build_cmds ENDL
#line 148 "main.ypp"
      { yylhs.value.as < string_list > () = yystack_[1].value.as < string_list > (); }
#line 992 "parser.cpp"
    break;

  case 20: // build_cmds: build_cmds TAB
#line 149 "main.ypp"
      { yylhs.value.as < string_list > () = yystack_[1].value.as < string_list > (); }
#line 998 "parser.cpp"
    break;

  case 21: // assign_stmt: WORD ASSIGN expr
#line 174 "main.ypp"
                              {yylhs.value.as < assign_type > () = {yystack_[2].value.as < std::string > (), yystack_[0].value.as < MULTI_TYPE > ()}; LOG_DEBUG( "assignment detected");}
#line 1004 "parser.cpp"
    break;

  case 22: // expr: WORD
#line 184 "main.ypp"
                                    {if(s_ScratchTable.exists(yystack_[0].value.as < std::string > ())) yylhs.value.as < MULTI_TYPE > () = s_ScratchTable.get(yystack_[0].value.as < std::string > ()); else if(buildFile.exists(yystack_[0].value.as < std::string > ())) yylhs.value.as < MULTI_TYPE > () = buildFile.get(yystack_[0].value.as < std::string > ()); else error(yystack_[0].location, "Symbol " + yystack_[0].value.as < std::string > () + " not found");}
#line 1010 "parser.cpp"
    break;

  case 23: // expr: NUMBER
#line 185 "main.ypp"
                                    {yylhs.value.as < MULTI_TYPE > () = yystack_[0].value.as < int > ();}
#line 1016 "parser.cpp"
    break;

  case 24: // expr: STRING_LIT
#line 186 "main.ypp"
                                    {yylhs.value.as < MULTI_TYPE > () = yystack_[0].value.as < std::string > (); s_ScratchTable.resolve(std::get<type::STRING>(yylhs.value.as < MULTI_TYPE > ()), buildFile);}
#line 1022 "parser.cpp"
    break;

  case 25: // expr: expr ADD expr
#line 188 "main.ypp"
                                    {yylhs.value.as < MULTI_TYPE > () = add(yystack_[2].value.as < MULTI_TYPE > (), yystack_[0].value.as < MULTI_TYPE > ()); LOG_DEBUG("value after addition is " + toString(yylhs.value.as < MULTI_TYPE > ())); }
#line 1028 "parser.cpp"
    break;

  case 26: // expr: expr MULTIPLY expr
#line 189 "main.ypp"
                                    {yylhs.value.as < MULTI_TYPE > () = multiply(yystack_[2].value.as < MULTI_TYPE > (), yystack_[0].value.as < MULTI_TYPE > ()); LOG_DEBUG("value after multiplication is " + toString(yylhs.value.as < MULTI_TYPE > ()));}
#line 1034 "parser.cpp"
    break;

  case 27: // expr: expr DIVIDE expr
#line 190 "main.ypp"
                                    {yylhs.value.as < MULTI_TYPE > () = divide(yystack_[2].value.as < MULTI_TYPE > (), yystack_[0].value.as < MULTI_TYPE > ()); LOG_DEBUG("value after division is " + toString(yylhs.value.as < MULTI_TYPE > ()));}
#line 1040 "parser.cpp"
    break;

  case 28: // expr: expr SUBTRACT expr
#line 191 "main.ypp"
                                    {yylhs.value.as < MULTI_TYPE > () = subtract(yystack_[2].value.as < MULTI_TYPE > (), yystack_[0].value.as < MULTI_TYPE > ()); LOG_DEBUG("value after subtract is " + toString(yylhs.value.as < MULTI_TYPE > ()));}
#line 1046 "parser.cpp"
    break;


#line 1050 "parser.cpp"

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
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char Parser::yypact_ninf_ = -14;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
     -14,    21,   -14,   -14,   -14,    -7,   -14,   -14,    -8,     6,
      -3,   -13,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,
     -14,   -14,   -14,   -14,    -1,    17,     3,   -13,   -13,   -13,
     -13,   -14,    14,   -14,     4,   -14,     4,   -14,   -14
  };

  const signed char
  Parser::yydefact_[] =
  {
       2,     0,     1,     9,     6,     0,     3,     4,     0,     0,
       0,     0,    16,     5,    15,     9,    11,    14,    12,    13,
      10,    22,    23,    24,    21,     7,     8,     0,     0,     0,
       0,    19,    20,    26,    25,    27,    28,    17,    18
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -14,   -14,   -14,   -14,   -14,    18,   -14,   -14,     5,    -2
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     1,     6,     7,     8,    10,    20,    25,     9,    24
  };

  const signed char
  Parser::yytable_[] =
  {
      14,    11,    21,    22,    15,    12,    14,    23,    27,    28,
      29,    30,    16,    27,    17,    29,    18,    19,    16,    13,
      17,     2,    18,    19,     3,    33,    34,    35,    36,     5,
      31,    32,    37,    26,     4,     0,     5,    38
  };

  const signed char
  Parser::yycheck_[] =
  {
       3,     8,    15,    16,     7,    13,     3,    20,     9,    10,
      11,    12,    15,     9,    17,    11,    19,    20,    15,    13,
      17,     0,    19,    20,     3,    27,    28,    29,    30,    15,
      13,    14,    18,    15,    13,    -1,    15,    32
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    22,     0,     3,    13,    15,    23,    24,    25,    29,
      26,     8,    13,    13,     3,     7,    15,    17,    19,    20,
      27,    15,    16,    20,    30,    28,    26,     9,    10,    11,
      12,    13,    14,    30,    30,    30,    30,    18,    29
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    21,    22,    22,    23,    23,    23,    24,    25,    26,
      26,    27,    27,    27,    27,    27,    28,    28,    28,    28,
      28,    29,    30,    30,    30,    30,    30,    30,    30
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     0,     2,     1,     2,     1,     3,     4,     0,
       2,     1,     1,     1,     1,     1,     0,     3,     3,     2,
       2,     3,     1,     1,     1,     3,     3,     3,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "BUILD", "QUOTE",
  "SBRAC", "EBRAC", "COLON", "ASSIGN", "MULTIPLY", "ADD", "DIVIDE",
  "SUBTRACT", "ENDL", "TAB", "WORD", "NUMBER", "DEREF", "COMMAND",
  "FILENAME", "STRING_LIT", "$accept", "stmts", "stmt", "build_grp",
  "build_head", "build_head_file_list", "file", "build_cmds",
  "assign_stmt", "expr", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,    88,    88,    89,    93,    95,    96,   100,   115,   126,
     127,   137,   138,   139,   140,   141,   144,   145,   147,   148,
     149,   174,   184,   185,   186,   188,   189,   190,   191
  };

  void
  Parser::yy_stack_print_ () const
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
  Parser::yy_reduce_print_ (int yyrule) const
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

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
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
      15,    16,    17,    18,    19,    20
    };
    // Last valid token kind.
    const int code_max = 275;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 26 "main.ypp"
} // Beast
#line 1424 "parser.cpp"

#line 215 "main.ypp"



void Beast::Parser::error(const location_type& loc, const std::string& msg) {
    RAISE_ERROR_AND_EXIT("parse error at line " + std::to_string(loc.begin.line) + ": " + msg, 1);
}

#ifdef PARSER_TEST
int main() {
    yyscan_t scanner;
    yylex_init(&scanner);
    /* std::vector<std::string> v; */
    Beast::BuildFile buildFile;
    Beast::Parser parser{scanner, buildFile};
    #if YYDEBUG == 1
        std::cout << "DEBUGGING..." << std::endl;
        parser.set_debug_level(true);
    #endif
    std::cout << "Scanner and parser generated" << std::endl;
    parser.parse();
    /* for(std::string& i : buildFile.m_BuildRules[0].m_InputTargets) {
        std::cout << i << std::endl;
    }
    std::cout << buildFile.m_BuildRules[0].m_OutputTarget << std::endl; */
    yylex_destroy(scanner);
    return 0;
}
#endif

namespace Beast {
	void readBuildFile(Beast::BuildFile& buildFile, const std::string& inputFile) {
		yyscan_t scanner;
		yylex_init(&scanner);
		Parser::location_type loc;
		FILE* inputFile_pointer = fopen(inputFile.c_str(), "r");
		if (inputFile_pointer){
			yyset_in(inputFile_pointer, scanner);
		}
		else{
			RAISE_ERROR_AND_EXIT("couldn't open file " + inputFile, 10);
		}
		Beast::Parser parser{scanner, buildFile, loc};
		#if YYDEBUG == 1
			LOG_DEBUG("DEBUGGING...");
			parser.set_debug_level(true);
		#endif
		LOG_DEBUG("Scanner and parser generated");
		parser.parse();
		yylex_destroy(scanner);
		buildFile.resolveBuildRules();
	}
}
