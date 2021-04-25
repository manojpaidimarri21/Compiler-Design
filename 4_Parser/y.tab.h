/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    PROGRAMtoken = 258,
    VARtoken = 259,
    BEGINtoken = 260,
    ENDtoken = 261,
    ENDDOTtoken = 262,
    INTEGERtoken = 263,
    REALDectoken = 264,
    FORtoken = 265,
    READtoken = 266,
    WRITEtoken = 267,
    TOtoken = 268,
    DOtoken = 269,
    SEMICOLONtoken = 270,
    COLONtoken = 271,
    REALtoken = 272,
    COMMAtoken = 273,
    COLEQUALtoken = 274,
    PLUStoken = 275,
    MINUStoken = 276,
    ASTERISKtoken = 277,
    DIVtoken = 278,
    LEFTPARENTHESIStoken = 279,
    RIGHTPARENTHESIStoken = 280,
    INTtoken = 281,
    IDtoken = 282
  };
#endif
/* Tokens.  */
#define PROGRAMtoken 258
#define VARtoken 259
#define BEGINtoken 260
#define ENDtoken 261
#define ENDDOTtoken 262
#define INTEGERtoken 263
#define REALDectoken 264
#define FORtoken 265
#define READtoken 266
#define WRITEtoken 267
#define TOtoken 268
#define DOtoken 269
#define SEMICOLONtoken 270
#define COLONtoken 271
#define REALtoken 272
#define COMMAtoken 273
#define COLEQUALtoken 274
#define PLUStoken 275
#define MINUStoken 276
#define ASTERISKtoken 277
#define DIVtoken 278
#define LEFTPARENTHESIStoken 279
#define RIGHTPARENTHESIStoken 280
#define INTtoken 281
#define IDtoken 282

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 53 "pascal_parser.y" /* yacc.c:1909  */

  char * IDstring;
    struct node * head;
    int id_val;


#line 115 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
