/* Her, Kong */

%{

#include "error.h"    // gpl file, using now to get use to it
#include "parser.h"   // gpl file, using now to get use to it

// #include <ctype.h>
#include <iostream>
using namespace std;

Error error_handler; // error reporting object

// The following variable keeps track of what input line flex is reading.
// It will be used for reporting the line numbers of errors.
// 
// It will be used by other parts of the program via the "extern" construct
//   If another .cpp file declares "extern int line_count" that line_count
//   in that file will be the line_count in this file (it becomes global)
int line_count = 1;

//-------------------------------------------------------------------
void get_int_value()
{
  yylval.union_int = atoi(yytext);
}

//-------------------------------------------------------------------
void get_double_value()
{
  //putting a double to the union
  yylval.union_double = atof(yytext);
} 
//-------------------------------------------------------------------
void get_string_value()
{
  // Would like to put a string in the union, but the way the union works
  // it has to be a pointer to a string.
  // This is a potential memory leak.  Think carefully about where and when
  // this memory should be deleted.
  if (yytext[yyleng-1] == '\"') 
  {
    yytext[yyleng-1] = 0; 
    yytext++;
  }
  yylval.union_string = new string(yytext);
}
//-------------------------------------------------------------------
void error()
{
  // have the error handling object report the problem
  // note: it uses line_count as a global variable
  error_handler.error(Error::ILLEGAL_TOKEN, yytext);

  // create a string to hold the current text
  // put that string in the yylval union so it can be used by parser (.y file)
  yylval.union_string = new string(yytext);
}
//-------------------------------------------------------------------

// the %} below indicates the end of the C/C++ code section

%}

/*
The %% below indicates the start of the rules flex/lex will use
The left-hand-side (LHS) specifies a regular expression
The right-hand-side (RHS) specifies an action (code to execute) when
  the regular expression is matched.
*/

%%


[\n]            line_count++; // count the lines for error reporting
[ \t\r]         ; // ignore spaces, tabs and the microsoft line feed (\r)


"int"           return T_INT;
"double"        return T_DOUBLE;
"string"        return T_STRING;
"triangle"      return T_TRIANGLE;
"pixmap"        return T_PIXMAP;
"circle"        return T_CIRCLE;
"rectangle"     return T_RECTANGLE;
"textbox"       return T_TEXTBOX;
"forward"       return T_FORWARD;
"initialization"  return T_INITIALIZATION;      

"true"          return T_TRUE;
"false"         return T_FALSE;

"on"            return T_ON;
"space"         return T_SPACE;
"leftarrow"     return T_LEFTARROW;
"rightarrow"    return T_RIGHTARROW;
"uparrow"       return T_UPARROW;
"downarrow"     return T_DOWNARROW;
"leftmouse_down"  return T_LEFTMOUSE_DOWN;
"middlemouse_down"  return T_MIDDLEMOUSE_DOWN;
"rightmouse_down"   return T_RIGHTMOUSE_DOWN;
"leftmouse_up"  return T_LEFTMOUSE_UP;
"middlemouse_up"  return T_MIDDLEMOUSE_UP;
"rightmouse_up" return T_RIGHTMOUSE_UP;
"mouse_move"    return T_MOUSE_MOVE;
"mouse_drag"    return T_MOUSE_DRAG;
"f1"            return T_F1;
"akey"          return T_AKEY;
"skey"          return T_SKEY;
"dkey"          return T_DKEY;
"fkey"          return T_FKEY;
"hkey"          return T_HKEY;
"jkey"          return T_JKEY;
"kkey"          return T_KKEY;
"lkey"          return T_LKEY;
"wkey"          return T_WKEY;

"touches"       return T_TOUCHES;
"near"          return T_NEAR;

"animation"     return T_ANIMATION;

"if"            return T_IF;
"for"           return T_FOR;
"else"          return T_ELSE;
"print"         return T_PRINT;
"exit"          return T_EXIT;

"("             return T_LPAREN;
")"             return T_RPAREN;
"{"             return T_LBRACE;
"}"             return T_RBRACE;
"["             return T_LBRACKET;
"]"             return T_RBRACKET;
";"             return T_SEMIC;
","             return T_COMMA;
"."             return T_PERIOD;

"="             return T_ASSIGN;
"+="            return T_PLUS_ASSIGN;
"-="            return T_MINUS_ASSIGN;
"++"            return T_PLUS_PLUS;
"--"            return T_MINUS_MINUS;

"*"             return T_ASTERISK;
"/"             return T_DIVIDE;
"%"             return T_MOD;
"+"             return T_PLUS;
"-"             return T_MINUS;
"sin"           return T_SIN;
"cos"           return T_COS;
"tan"           return T_TAN;
"asin"          return T_ASIN;
"acos"          return T_ACOS;
"atan"          return T_ATAN;
"sqrt"          return T_SQRT;
"floor"         return T_FLOOR;
"abs"           return T_ABS;
"random"        return T_RANDOM;

"<"             return T_LESS;
">"             return T_GREATER;
"<="            return T_LESS_EQUAL;
">="            return T_GREATER_EQUAL;
"=="            return T_EQUAL;
"!="            return T_NOT_EQUAL;

"&&"            return T_AND;
"||"            return T_OR;
"!"             return T_NOT;


[\/][\/].* 
[0-9]+           get_int_value(); return T_INT_CONSTANT; 
[0-9]*\.?[0-9]+  get_double_value(); return T_DOUBLE_CONSTANT;
(^[int|double|string])|([a-zA-Z_]+|[a-zA-Z_]+|[a-zA-Z_0-9]*)    get_string_value(); return T_ID;    
\"[^\"]+\"  get_string_value(); return T_STRING_CONSTANT; 


.               error(); return T_ERROR;
