/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

    #include<stdio.h>
    extern FILE *yyin;
    extern FILE *yyout;
    extern int yylex();
    extern int yylineno;
    extern char *yytext;
    void yyerror(char *str){
        printf("%d:%s:%s\n",yylineno,str,yytext);
    };

#line 78 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CONST = 258,
    INT = 259,
    VOID = 260,
    IF = 261,
    ELSE = 262,
    WHILE = 263,
    BREAK = 264,
    CONTINUE = 265,
    RETURN = 266,
    LE = 267,
    GE = 268,
    EQ = 269,
    NE = 270,
    AND = 271,
    OR = 272,
    IDENT = 273,
    INT_CONST = 274
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 13 "parser.y" /* yacc.c:355  */

    int val;

#line 142 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 159 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   206

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  159

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   274

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    20,     2,     2,     2,    19,     2,     2,
      21,    22,    17,    15,    28,    16,     2,    18,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    27,
      14,    12,    13,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    23,     2,    24,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,    26,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    29,    30,    31,
      32,    33,    34,    35,    36
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    26,    26,    27,    28,    29,    32,    33,    36,    39,
      40,    43,    44,    47,    50,    51,    54,    55,    56,    59,
      60,    63,    66,    67,    70,    71,    74,    75,    76,    79,
      80,    83,    84,    87,    88,    91,    92,    95,    98,    99,
     102,   103,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   119,   122,   125,   126,   129,   130,   131,
     134,   137,   138,   139,   140,   143,   144,   145,   148,   149,
     152,   153,   154,   155,   158,   159,   160,   163,   164,   165,
     166,   167,   170,   171,   172,   175,   176,   179,   180,   183
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONST", "INT", "VOID", "IF", "ELSE",
  "WHILE", "BREAK", "CONTINUE", "RETURN", "'='", "'>'", "'<'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "'!'", "'('", "')'", "'['", "']'", "'{'",
  "'}'", "';'", "','", "LE", "GE", "EQ", "NE", "AND", "OR", "IDENT",
  "INT_CONST", "$accept", "CompUnit", "Decl", "ConstDecl", "ConstDef_temp",
  "BType", "ConstDef", "ConstExp_temp", "ConstInitVal",
  "ConstInitVal_temp", "VarDecl", "VarDef_temp", "VarDef", "InitVal",
  "InitVal_temp", "FuncDef", "FuncFParams", "FuncFParam", "Block",
  "BlockItem_temp", "BlockItem", "Stmt", "Exp", "Cond", "LVal",
  "PrimaryExp", "Number", "UnaryExp", "UnaryOp", "FuncRParams", "MulExp",
  "AddExp", "RelExp", "EqExp", "LAndExp", "LOrExp", "ConstExp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,    61,    62,    60,    43,    45,    42,    47,    37,
      33,    40,    41,    91,    93,   123,   125,    59,    44,   267,
     268,   269,   270,   271,   272,   273,   274
};
# endif

#define YYPACT_NINF -125

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-125)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      99,    71,  -125,  -125,    96,  -125,  -125,   -22,  -125,  -125,
     -17,  -125,  -125,  -125,    32,    70,  -125,  -125,   135,  -125,
      44,    -1,  -125,   -12,    29,  -125,   -17,    66,    25,    28,
    -125,    19,   158,  -125,  -125,    57,  -125,  -125,  -125,    41,
      66,    71,  -125,  -125,  -125,   158,    -6,   112,  -125,  -125,
    -125,    94,  -125,  -125,  -125,   158,   105,   160,   160,   104,
      11,  -125,  -125,   110,   115,  -125,  -125,   122,  -125,  -125,
     101,   134,   158,  -125,   158,   158,   158,   158,   158,  -125,
    -125,  -125,   106,   130,   137,   144,   150,   145,  -125,  -125,
    -125,   -12,  -125,  -125,  -125,   161,    39,  -125,  -125,  -125,
      19,  -125,  -125,    35,   140,  -125,  -125,  -125,   105,   105,
    -125,    57,   158,   158,  -125,  -125,  -125,   162,  -125,   158,
     167,  -125,  -125,   158,  -125,  -125,   169,   160,    56,   151,
     159,   163,   173,  -125,   171,  -125,   132,   158,   158,   158,
     158,   158,   158,   158,   158,   132,  -125,   189,   160,   160,
     160,   160,    56,    56,   151,   159,  -125,   132,  -125
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    11,    12,     0,     4,     6,     0,     7,     5,
       0,     1,     2,     3,    15,     0,    22,    15,     0,     9,
       0,    24,    21,     0,     0,     8,     0,     0,     0,     0,
      33,     0,     0,    15,    23,     0,    10,    39,    32,    36,
       0,     0,    65,    66,    67,     0,     0,    55,    60,    25,
      26,    58,    61,    59,    70,     0,    74,    53,    89,     0,
       0,    13,    16,     0,     0,    31,    34,     0,    27,    29,
       0,     0,     0,    64,     0,     0,     0,     0,     0,    14,
      17,    19,     0,     0,     0,     0,     0,     0,    37,    44,
      40,     0,    45,    38,    41,     0,    58,    15,    57,    28,
       0,    63,    68,     0,     0,    71,    72,    73,    75,    76,
      18,     0,     0,     0,    49,    50,    52,     0,    43,     0,
      35,    30,    62,     0,    56,    20,     0,    77,    82,    85,
      87,    54,     0,    51,     0,    69,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    42,    47,    79,    78,
      80,    81,    83,    84,    86,    88,    48,     0,    46
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -125,  -125,     2,  -125,  -125,     4,   174,   -13,   -52,  -125,
    -125,  -125,   176,   -39,  -125,   197,  -125,   164,    -2,  -125,
    -125,  -124,   -29,    89,   -62,  -125,  -125,    13,  -125,  -125,
     107,   -32,    45,    60,    62,  -125,   172
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    18,     7,    19,    21,    61,    82,
       8,    15,    16,    49,    70,     9,    29,    30,    92,    63,
      93,    94,    95,   126,    51,    52,    53,    54,    55,   103,
      56,    57,   128,   129,   130,   131,    62
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      58,    96,    50,    58,    24,    10,    12,    69,    81,    42,
      43,    31,   147,    14,    44,    45,    67,    50,    17,    46,
      68,   156,    32,    33,    28,    38,    42,    43,    58,    47,
      48,    44,    45,   158,    42,    43,    60,    80,    65,    44,
      45,    35,   102,   104,    46,    28,    47,    48,     2,     3,
      40,   119,    32,    20,    47,    48,    41,   122,   117,   125,
      39,   121,    72,   123,    64,    90,    27,    91,    73,   137,
     138,    50,    42,    43,    96,     2,     3,    44,    45,    58,
     127,   127,    60,    96,   120,   139,   140,   105,   106,   107,
     134,    37,    47,    48,   135,    96,    11,    22,    23,     1,
       2,     3,     1,     2,     3,   148,   149,   150,   151,   127,
     127,   127,   127,     1,     2,     3,    83,    72,    84,    85,
      86,    87,    74,    75,    76,    42,    43,    99,    79,   100,
      44,    45,   110,    71,   111,    37,    88,    89,    83,    97,
      84,    85,    86,    87,    98,    47,    48,    42,    43,    42,
      43,   112,    44,    45,    44,    45,   101,    37,   113,    89,
      42,    43,    25,    26,   124,    44,    45,    47,    48,    47,
      48,   114,   116,    42,    43,    77,    78,   115,    44,    45,
      47,    48,   141,   142,   108,   109,   152,   153,   118,   133,
      32,   136,   143,    47,    48,   145,   157,   144,   146,    34,
      36,    13,   132,   154,    59,    66,   155
};

static const yytype_uint8 yycheck[] =
{
      32,    63,    31,    35,    17,     1,     4,    46,    60,    15,
      16,    12,   136,    35,    20,    21,    45,    46,    35,    25,
      26,   145,    23,    35,    20,    27,    15,    16,    60,    35,
      36,    20,    21,   157,    15,    16,    25,    26,    40,    20,
      21,    12,    71,    72,    25,    41,    35,    36,     4,     5,
      22,    12,    23,    21,    35,    36,    28,    22,    87,   111,
      35,   100,    23,    28,    23,    63,    22,    63,    55,    13,
      14,   100,    15,    16,   136,     4,     5,    20,    21,   111,
     112,   113,    25,   145,    97,    29,    30,    74,    75,    76,
     119,    25,    35,    36,   123,   157,     0,    27,    28,     3,
       4,     5,     3,     4,     5,   137,   138,   139,   140,   141,
     142,   143,   144,     3,     4,     5,     6,    23,     8,     9,
      10,    11,    17,    18,    19,    15,    16,    26,    24,    28,
      20,    21,    26,    21,    28,    25,    26,    27,     6,    24,
       8,     9,    10,    11,    22,    35,    36,    15,    16,    15,
      16,    21,    20,    21,    20,    21,    22,    25,    21,    27,
      15,    16,    27,    28,    24,    20,    21,    35,    36,    35,
      36,    27,    27,    15,    16,    15,    16,    27,    20,    21,
      35,    36,    31,    32,    77,    78,   141,   142,    27,    27,
      23,    22,    33,    35,    36,    22,     7,    34,    27,    23,
      26,     4,   113,   143,    32,    41,   144
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,    38,    39,    40,    42,    47,    52,
      42,     0,    39,    52,    35,    48,    49,    35,    41,    43,
      21,    44,    27,    28,    44,    27,    28,    22,    42,    53,
      54,    12,    23,    35,    49,    12,    43,    25,    55,    35,
      22,    28,    15,    16,    20,    21,    25,    35,    36,    50,
      59,    61,    62,    63,    64,    65,    67,    68,    68,    73,
      25,    45,    73,    56,    23,    55,    54,    59,    26,    50,
      51,    21,    23,    64,    17,    18,    19,    15,    16,    24,
      26,    45,    46,     6,     8,     9,    10,    11,    26,    27,
      39,    42,    55,    57,    58,    59,    61,    24,    22,    26,
      28,    22,    59,    66,    59,    64,    64,    64,    67,    67,
      26,    28,    21,    21,    27,    27,    27,    59,    27,    12,
      44,    50,    22,    28,    24,    45,    60,    68,    69,    70,
      71,    72,    60,    27,    59,    59,    22,    13,    14,    29,
      30,    31,    32,    33,    34,    22,    27,    58,    68,    68,
      68,    68,    69,    69,    70,    71,    58,     7,    58
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    38,    38,    38,    39,    39,    40,    41,
      41,    42,    42,    43,    44,    44,    45,    45,    45,    46,
      46,    47,    48,    48,    49,    49,    50,    50,    50,    51,
      51,    52,    52,    53,    53,    54,    54,    55,    56,    56,
      57,    57,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    59,    60,    61,    61,    62,    62,    62,
      63,    64,    64,    64,    64,    65,    65,    65,    66,    66,
      67,    67,    67,    67,    68,    68,    68,    69,    69,    69,
      69,    69,    70,    70,    70,    71,    71,    72,    72,    73
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     1,     4,     1,
       3,     1,     1,     4,     4,     0,     1,     2,     3,     1,
       3,     3,     1,     3,     2,     4,     1,     2,     3,     1,
       3,     6,     5,     1,     3,     5,     2,     3,     2,     0,
       1,     1,     4,     2,     1,     1,     7,     5,     5,     2,
       2,     3,     2,     1,     1,     1,     4,     3,     1,     1,
       1,     1,     4,     3,     2,     1,     1,     1,     1,     3,
       1,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     1,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 26 "parser.y" /* yacc.c:1646  */
    {printf("r CompUnit\n");}
#line 1353 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 27 "parser.y" /* yacc.c:1646  */
    {printf("r CompUnit\n");}
#line 1359 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 28 "parser.y" /* yacc.c:1646  */
    {printf("r CompUnit\n");}
#line 1365 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 29 "parser.y" /* yacc.c:1646  */
    {printf("r CompUnit\n");}
#line 1371 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 32 "parser.y" /* yacc.c:1646  */
    {printf("r Decl\n");}
#line 1377 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 33 "parser.y" /* yacc.c:1646  */
    {printf("r Decl\n");}
#line 1383 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 36 "parser.y" /* yacc.c:1646  */
    {printf("r ConstDecl\n");}
#line 1389 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 39 "parser.y" /* yacc.c:1646  */
    {printf("r ConstDef_temp\n");}
#line 1395 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 40 "parser.y" /* yacc.c:1646  */
    {printf("r ConstDef_temp\n");}
#line 1401 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 43 "parser.y" /* yacc.c:1646  */
    {printf("r BType\n");}
#line 1407 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 44 "parser.y" /* yacc.c:1646  */
    {printf("r BType\n");}
#line 1413 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 47 "parser.y" /* yacc.c:1646  */
    {printf("r ConstDef\n");}
#line 1419 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 50 "parser.y" /* yacc.c:1646  */
    {printf("r ConstExp_temp\n");}
#line 1425 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 51 "parser.y" /* yacc.c:1646  */
    {printf("r ConstExp_temp\n");}
#line 1431 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 54 "parser.y" /* yacc.c:1646  */
    {printf("r ConstInitVal\n");}
#line 1437 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 55 "parser.y" /* yacc.c:1646  */
    {printf("r ConstInitVal\n");}
#line 1443 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 56 "parser.y" /* yacc.c:1646  */
    {printf("r ConstInitVal\n");}
#line 1449 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 59 "parser.y" /* yacc.c:1646  */
    {printf("r ConstInitVal_temp\n");}
#line 1455 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 60 "parser.y" /* yacc.c:1646  */
    {printf("r ConstInitVal_temp\n");}
#line 1461 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 63 "parser.y" /* yacc.c:1646  */
    {printf("r VarDecl\n");}
#line 1467 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 66 "parser.y" /* yacc.c:1646  */
    {printf("r VarDef_temp\n");}
#line 1473 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 67 "parser.y" /* yacc.c:1646  */
    {printf("r VarDef_temp\n");}
#line 1479 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 70 "parser.y" /* yacc.c:1646  */
    {printf("r VarDef\n");}
#line 1485 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 71 "parser.y" /* yacc.c:1646  */
    {printf("r VarDef\n");}
#line 1491 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 74 "parser.y" /* yacc.c:1646  */
    {printf("r InitVal\n");}
#line 1497 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 75 "parser.y" /* yacc.c:1646  */
    {printf("r InitVal\n");}
#line 1503 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 76 "parser.y" /* yacc.c:1646  */
    {printf("r InitVal\n");}
#line 1509 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 79 "parser.y" /* yacc.c:1646  */
    {printf("r InitVal_temp\n");}
#line 1515 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 80 "parser.y" /* yacc.c:1646  */
    {printf("r InitVal_temp\n");}
#line 1521 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 83 "parser.y" /* yacc.c:1646  */
    {printf("r FuncDef\n");}
#line 1527 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 84 "parser.y" /* yacc.c:1646  */
    {printf("r FuncDef\n");}
#line 1533 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 87 "parser.y" /* yacc.c:1646  */
    {printf("r FuncFParams\n");}
#line 1539 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 88 "parser.y" /* yacc.c:1646  */
    {printf("r FuncFParams\n");}
#line 1545 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 91 "parser.y" /* yacc.c:1646  */
    {printf("r FuncFParam\n");}
#line 1551 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 92 "parser.y" /* yacc.c:1646  */
    {printf("r FuncFParam\n");}
#line 1557 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 95 "parser.y" /* yacc.c:1646  */
    {printf("r Block\n");}
#line 1563 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 98 "parser.y" /* yacc.c:1646  */
    {printf("r BlockItem_temp\n");}
#line 1569 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 99 "parser.y" /* yacc.c:1646  */
    {printf("r BlockItem_temp\n");}
#line 1575 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 102 "parser.y" /* yacc.c:1646  */
    {printf("r BlockItem\n");}
#line 1581 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 103 "parser.y" /* yacc.c:1646  */
    {printf("r BlockItem\n");}
#line 1587 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 106 "parser.y" /* yacc.c:1646  */
    {printf("r Stmt\n");}
#line 1593 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 107 "parser.y" /* yacc.c:1646  */
    {printf("r Stmt\n");}
#line 1599 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 108 "parser.y" /* yacc.c:1646  */
    {printf("r Stmt\n");}
#line 1605 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 109 "parser.y" /* yacc.c:1646  */
    {printf("r Stmt\n");}
#line 1611 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 110 "parser.y" /* yacc.c:1646  */
    {printf("r Stmt\n");}
#line 1617 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 111 "parser.y" /* yacc.c:1646  */
    {printf("r Stmt\n");}
#line 1623 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 112 "parser.y" /* yacc.c:1646  */
    {printf("r Stmt\n");}
#line 1629 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 113 "parser.y" /* yacc.c:1646  */
    {printf("r Stmt\n");}
#line 1635 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 114 "parser.y" /* yacc.c:1646  */
    {printf("r Stmt\n");}
#line 1641 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 115 "parser.y" /* yacc.c:1646  */
    {printf("r Stmt\n");}
#line 1647 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 116 "parser.y" /* yacc.c:1646  */
    {printf("r Stmt\n");}
#line 1653 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 119 "parser.y" /* yacc.c:1646  */
    {printf("r Exp\n");}
#line 1659 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 122 "parser.y" /* yacc.c:1646  */
    {printf("r Cond\n");}
#line 1665 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 125 "parser.y" /* yacc.c:1646  */
    {printf("r LVal\n");}
#line 1671 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 126 "parser.y" /* yacc.c:1646  */
    {printf("r LVal\n");}
#line 1677 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 129 "parser.y" /* yacc.c:1646  */
    {printf("r PrimaryExp\n");}
#line 1683 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 130 "parser.y" /* yacc.c:1646  */
    {printf("r PrimaryExp\n");}
#line 1689 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 131 "parser.y" /* yacc.c:1646  */
    {printf("r PrimaryExp\n");}
#line 1695 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 134 "parser.y" /* yacc.c:1646  */
    {printf("r Number\n");}
#line 1701 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 137 "parser.y" /* yacc.c:1646  */
    {printf("r UnaryExp\n");}
#line 1707 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 138 "parser.y" /* yacc.c:1646  */
    {printf("r UnaryExp\n");}
#line 1713 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 139 "parser.y" /* yacc.c:1646  */
    {printf("r UnaryExp\n");}
#line 1719 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 140 "parser.y" /* yacc.c:1646  */
    {printf("r UnaryExp\n");}
#line 1725 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 143 "parser.y" /* yacc.c:1646  */
    {printf("r UnaryOp\n");}
#line 1731 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 144 "parser.y" /* yacc.c:1646  */
    {printf("r UnaryOp\n");}
#line 1737 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 145 "parser.y" /* yacc.c:1646  */
    {printf("r UnaryOp\n");}
#line 1743 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 148 "parser.y" /* yacc.c:1646  */
    {printf("r FuncRParams\n");}
#line 1749 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 149 "parser.y" /* yacc.c:1646  */
    {printf("r FuncRParams\n");}
#line 1755 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 152 "parser.y" /* yacc.c:1646  */
    {printf("r MulExp\n");}
#line 1761 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 153 "parser.y" /* yacc.c:1646  */
    {printf("r MulExp\n");}
#line 1767 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 154 "parser.y" /* yacc.c:1646  */
    {printf("r MulExp\n");}
#line 1773 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 155 "parser.y" /* yacc.c:1646  */
    {printf("r MulExp\n");}
#line 1779 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 158 "parser.y" /* yacc.c:1646  */
    {printf("r AddExp\n");}
#line 1785 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 159 "parser.y" /* yacc.c:1646  */
    {printf("r AddExp\n");}
#line 1791 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 160 "parser.y" /* yacc.c:1646  */
    {printf("r AddExp\n");}
#line 1797 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 163 "parser.y" /* yacc.c:1646  */
    {printf("r RelExp\n");}
#line 1803 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 164 "parser.y" /* yacc.c:1646  */
    {printf("r RelExp\n");}
#line 1809 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 165 "parser.y" /* yacc.c:1646  */
    {printf("r RelExp\n");}
#line 1815 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 166 "parser.y" /* yacc.c:1646  */
    {printf("r RelExp\n");}
#line 1821 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 167 "parser.y" /* yacc.c:1646  */
    {printf("r RelExp\n");}
#line 1827 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 170 "parser.y" /* yacc.c:1646  */
    {printf("r EqExp\n");}
#line 1833 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 171 "parser.y" /* yacc.c:1646  */
    {printf("r EqExp\n");}
#line 1839 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 172 "parser.y" /* yacc.c:1646  */
    {printf("r EqExp\n");}
#line 1845 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 175 "parser.y" /* yacc.c:1646  */
    {printf("r LAndExp\n");}
#line 1851 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 176 "parser.y" /* yacc.c:1646  */
    {printf("r LAndExp\n");}
#line 1857 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 179 "parser.y" /* yacc.c:1646  */
    {printf("r LOrExp\n");}
#line 1863 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 180 "parser.y" /* yacc.c:1646  */
    {printf("r LOrExp\n");}
#line 1869 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 183 "parser.y" /* yacc.c:1646  */
    {printf("r ConstExp\n");}
#line 1875 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 1879 "parser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 186 "parser.y" /* yacc.c:1906  */


int yywrap(){
    return 1;
}
