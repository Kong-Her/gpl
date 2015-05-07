/* Her, Kong */

%{  // bison syntax to indicate the start of the header
    // the header is copied directly into y.tab.c (the generated parser)

extern int yylex();               // this lexer function returns next token
extern int yyerror(const char *); // used to print errors
extern int line_count;            // current line in the input; from record.l

#include "error.h"      // class for printing errors (used by gpl)
#include "parser.h"
#include "expression.h"
#include "variable.h"
#include "game_object.h"
#include "circle.h"
#include "pixmap.h"
#include "rectangle.h"
#include "triangle.h"
#include "textbox.h"
#include "animation_block.h"
#include "statement_block.h"
#include "assignment_stmt.h"
#include "if_stmt.h"
#include "exit_stmt.h"
#include "print_stmt.h"
#include "event_manager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
using namespace std;

stack<Statement_block *> global_statement_stack;
int undeclared = 0;
Variable *undeclared_var = new Variable(new Symbol("__undeclared", undeclared));
Symbol_table *symbol_table = Symbol_table::instance();
Event_manager *event_manager = Event_manager::instance();
Game_object *cur_object_under_construction;
string obj_class, obj_name;

// bison syntax to indicate the end of the header
%} 


%union {
 int            union_int;
 double         union_double;
 std::string    *union_string;  // MUST be a pointer to a string (this sucks!)
 Gpl_type       union_gpl_type;
 Operator_type  union_operator_type;
 class Expression  *union_expression; 
 class Variable *union_variable;
 class Symbol    *union_symbol;
 class Game_object *union_game_object;
 Window::Keystroke  union_keystroke;
 Statement_block    *union_statement_block;
}

// turn on verbose (longer) error messages
%error-verbose

%token T_INT                 "int"
%token T_DOUBLE              "double"
%token T_STRING              "string"
%token T_TRIANGLE            "triangle"
%token T_PIXMAP              "pixmap"
%token T_CIRCLE              "circle"
%token T_RECTANGLE           "rectangle"
%token T_TEXTBOX             "textbox"
%token <union_int> T_FORWARD         "forward" // value is line number
%token T_INITIALIZATION      "initialization" 

%token T_TRUE                "true"
%token T_FALSE               "false"

%token T_ON                  "on"
%token T_SPACE               "space"
%token T_LEFTARROW           "leftarrow"
%token T_RIGHTARROW          "rightarrow"
%token T_UPARROW             "uparrow"
%token T_DOWNARROW           "downarrow"
%token T_LEFTMOUSE_DOWN      "leftmouse_down"
%token T_MIDDLEMOUSE_DOWN    "middlemouse_down"
%token T_RIGHTMOUSE_DOWN     "rightmouse_down"
%token T_LEFTMOUSE_UP        "leftmouse_up"
%token T_MIDDLEMOUSE_UP      "middlemouse_up"
%token T_RIGHTMOUSE_UP       "rightmouse_up"
%token T_MOUSE_MOVE          "mouse_move"
%token T_MOUSE_DRAG          "mouse_drag"
%token T_F1                  "f1"
%token T_AKEY                "akey"
%token T_SKEY                "skey"
%token T_DKEY                "dkey"
%token T_FKEY                "fkey"
%token T_HKEY                "hkey"
%token T_JKEY                "jkey"
%token T_KKEY                "kkey"
%token T_LKEY                "lkey"
%token T_WKEY                "wkey"

%token T_TOUCHES             "touches"
%token T_NEAR                "near"

%token T_ANIMATION           "animation"

%token T_IF                  "if"
%token T_FOR                 "for"
%token T_ELSE                "else"
%token <union_int> T_PRINT           "print" // value is line number
%token <union_int> T_EXIT            "exit" // value is line number

%token T_LPAREN              "("
%token T_RPAREN              ")"
%token T_LBRACE              "{"
%token T_RBRACE              "}"
%token T_LBRACKET            "["
%token T_RBRACKET            "]"
%token T_SEMIC               ";"
%token T_COMMA               ","
%token T_PERIOD              "."

%token T_ASSIGN              "="
%token T_PLUS_ASSIGN         "+="
%token T_MINUS_ASSIGN        "-="
%token T_PLUS_PLUS           "++"
%token T_MINUS_MINUS         "--"

%token T_ASTERISK            "*"
%token T_DIVIDE              "/"
%token T_MOD                 "%"
%token T_PLUS                "+"
%token T_MINUS               "-"
%token T_SIN                 "sin"
%token T_COS                 "cos"
%token T_TAN                 "tan"
%token T_ASIN                "asin"
%token T_ACOS                "acos"
%token T_ATAN                "atan"
%token T_SQRT                "sqrt"
%token T_FLOOR               "floor"
%token T_ABS                 "abs"
%token T_RANDOM              "random"

%token T_LESS                "<"
%token T_GREATER             ">"
%token T_LESS_EQUAL          "<="
%token T_GREATER_EQUAL       ">="
%token T_EQUAL               "=="
%token T_NOT_EQUAL           "!="

%token T_AND                 "&&"
%token T_OR                  "||"
%token T_NOT                 "!"

%token <union_string> T_ID              "identifier"
%token <union_int> T_INT_CONSTANT    "int constant"
%token <union_double> T_DOUBLE_CONSTANT "double constant"
%token <union_string> T_STRING_CONSTANT "string constant"
%type <union_gpl_type> simple_type
%type <union_operator_type> math_operator
%type <union_expression> expression
%type <union_expression> primary_expression
%type <union_expression> optional_initializer
%type <union_variable> variable
%type <union_symbol> animation_parameter
%type <union_int> object_type
%type <union_keystroke> keystroke
%type <union_statement_block> statement_block
%type <union_statement_block> statement_block_creator
%type <union_statement_block> end_of_statement_block
%type <union_statement_block> if_block

// special token that does not match any production
// used for characters that are not part of the language
%token T_ERROR               "error"

//precedence
%nonassoc IF_NO_ELSE
%left T_ELSE
%left T_OR 
%left T_AND 
%left T_EQUAL T_NOT_EQUAL 
%left T_GREATER_EQUAL T_LESS_EQUAL T_GREATER T_LESS 
%left T_PLUS T_MINUS
%left T_ASTERISK T_DIVIDE T_MOD
%right T_NOT
%nonassoc UNARY_OPS

%% // indicates the start of the rules

//---------------------------------------------------------------------
program:
    declaration_list block_list
    ;

//---------------------------------------------------------------------
declaration_list:
    declaration_list declaration
    | empty
    ;

//---------------------------------------------------------------------
declaration:
    variable_declaration T_SEMIC
    | object_declaration T_SEMIC
    | forward_declaration T_SEMIC
    ;

//---------------------------------------------------------------------
variable_declaration:
    simple_type  T_ID  optional_initializer
    {
	    Symbol *new_symbol;
        Expression *init_expr = $3;
        int int_value = 0;
        double double_value = 0;
        ostringstream convert;
        Gpl_type gpl_type;

        convert << *$2 << "[0]";
        Symbol *sym = symbol_table->lookup(convert.str());
        
        if(!sym)
        {
            if ($1 == INT)
            {
                if (init_expr != NULL)
                {
                    if (init_expr->get_type() == STRING || 
                        init_expr->get_type() == DOUBLE)
                    {
                        Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, *$2, "", "");
                        new_symbol = new Symbol($1, *$2, 0);
                    }
                    else
                    {
                        int_value = init_expr->eval_int();
        	            new_symbol = new Symbol($1, *$2, int_value);
                    }
                }
                else 
                    new_symbol = new Symbol($1, *$2, 0);
        	}
           else if ($1 == DOUBLE)
           {
               if (init_expr != NULL)
               {
                   if (init_expr->get_type() == STRING)
                   {
                       Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,
                                    *$2, "", "");
                       new_symbol = new Symbol($1, *$2, 0);
                   }
                   else
                   {
                       double_value = init_expr->eval_double();
        	           new_symbol = new Symbol($1, *$2, double_value);
                   }
               }
               else
                   new_symbol = new Symbol($1, *$2, 0.0);
       	   }
           else if ($1 == STRING)
           {
               string string_value = "";
               if (init_expr != NULL)
               {
                   string_value = init_expr->eval_string();
        	       new_symbol = new Symbol($1, *$2, string_value);
               }
               else 
                   new_symbol = new Symbol($1, *$2, "");
           }
        }
        else 
        {
            new_symbol = NULL;
	        convert.clear();
	        convert.str(string());
        }

    	if (!symbol_table->insert(new_symbol, *$2))
    	{
    	    Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2, "", "");
    	}

    }
    | simple_type  T_ID  T_LBRACKET expression T_RBRACKET
    {
        Expression *init_expr = $4;
	    Symbol *new_symbol;
	    ostringstream str;
        int int_value = 0;
        double double_value;

        if (init_expr->get_type() == STRING)
        {
            string st = init_expr->eval_string();
            Error::error(Error::INVALID_ARRAY_SIZE, *$2, st, ""); 
        }
        else if (init_expr->get_type() == DOUBLE)
        {
            double db = init_expr->eval_double();
            str << db;
            Error::error(Error::INVALID_ARRAY_SIZE, *$2, str.str(), ""); 
        }
        else 
        {
            int_value = init_expr->eval_int();
            if (int_value == 0)
            {
                Error::error(Error::INVALID_ARRAY_SIZE, *$2, 
                              "0", ""); 
            }
            else
            {
                for (int i = 0; i < int_value; i++)
                {
                    if ($1 == INT)
                    {
                        str << *$2 << "[" << i << "]";
                        new_symbol = new Symbol($1, str.str(), 0);
                    }
                    else if ($1 == DOUBLE)
                    {
                        str << *$2 << "[" << i << "]";
                        new_symbol = new Symbol($1, str.str(), 0);
                    }
                    else if ($1 == STRING)
                    {
                        str << *$2 << "[" << i << "]";
                        new_symbol = new Symbol($1, str.str(), "");
                    }
                    if (!symbol_table->insert(new_symbol, *$2))
                    {
                        Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, 
                                      *$2, "", "");
                        //use break so it doesn't print all the errors 
                        //for each of the arrays
                        break;
                    }
	            //clear ostringstream str so it won't add on to the string
	            str.clear();
	            str.str(string());
                }
            }
        }
    }
    ;

//---------------------------------------------------------------------
simple_type:
    T_INT
    {
	   $$ = INT;
    }
    | T_DOUBLE
    {
	   $$ = DOUBLE;
    }
    | T_STRING
    {
	   $$ = STRING;
    }
    ;

//---------------------------------------------------------------------
optional_initializer:
    T_ASSIGN expression
    {
        $$ = $2;
    }
    | empty
    {
        $$ = NULL;
    }
    ;

//---------------------------------------------------------------------
object_declaration:
    object_type T_ID 
    {
        Symbol *new_symbol;
        
        switch ($1)
        {
            case T_TRIANGLE:
                cur_object_under_construction = new Triangle();
                obj_class = "Triangle";
                obj_name = *$2;
                break;
            case T_RECTANGLE:
                cur_object_under_construction = new Rectangle();
                obj_class = "Rectangle";
                obj_name = *$2;
                break;
            case T_CIRCLE:
                cur_object_under_construction = new Circle();
                obj_class = "Circle";
                obj_name = *$2;
                break;
            case T_TEXTBOX:
                cur_object_under_construction = new Textbox();
                obj_class = "Textbox";
                obj_name = *$2;
                break;
            case T_PIXMAP:
                cur_object_under_construction = new Pixmap();
                obj_class = "Pixmap";
                obj_name = *$2;
                break;
        }
        new_symbol = new Symbol(GAME_OBJECT, *$2, cur_object_under_construction);

        if (!symbol_table->insert(new_symbol, *$2))
        {
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2, "", "");
        }
    }
    T_LPAREN parameter_list_or_empty T_RPAREN
    {
    
    }
    | object_type T_ID 
    {
        switch ($1)
        {
            case T_TRIANGLE:
                cur_object_under_construction = new Triangle();
                obj_class = "Triangle";
                obj_name = *$2;
                break;
            case T_RECTANGLE:
                cur_object_under_construction = new Rectangle();
                obj_class = "Rectangle";
                obj_name = *$2;
                break;
            case T_CIRCLE:
                cur_object_under_construction = new Circle();
                obj_class = "Circle";
                obj_name = *$2;
                break;
            case T_TEXTBOX:
                cur_object_under_construction = new Textbox();
                obj_class = "Textbox";
                obj_name = *$2;
                break;
            case T_PIXMAP:
                cur_object_under_construction = new Pixmap();
                obj_class = "Pixmap";
                obj_name = *$2;
                break;
        }
    }
    T_LBRACKET expression T_RBRACKET
    {
        Expression *expr = $5;
        ostringstream st;
        Symbol *new_symbol;

        if (expr->get_type() == DOUBLE)
        {
            st << expr->eval_double();
            Error::error(Error::INVALID_ARRAY_SIZE, 
                         *$2, st.str(), "");
        }
        else if (expr->get_type() == STRING)
        {
            st << expr->eval_string();
            Error::error(Error::INVALID_ARRAY_SIZE, 
                         *$2, st.str(), "");
        }
        else 
        {
            int total = expr->eval_int();

            for (int i = 0; i < total; i++)
            {
                string tmp;
                st << *$2 << "[" << i << "]";
                tmp = st.str();
                st.clear();
                st.str(string());
                new_symbol = new Symbol(GAME_OBJECT, tmp, cur_object_under_construction);

                if (!symbol_table->insert(new_symbol, *$2))
                {
                    Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2, "", "");
                }
            }
        }

    }
    ;

//---------------------------------------------------------------------
object_type:
    T_TRIANGLE
    {
        $$ = T_TRIANGLE;
    }
    | T_PIXMAP
    {
        $$ = T_PIXMAP;
    }
    | T_CIRCLE
    {
        $$ = T_CIRCLE;
    }
    | T_RECTANGLE
    {
        $$ = T_RECTANGLE;
    }
    | T_TEXTBOX
    {
        $$ = T_TEXTBOX;
    }
    ;

//---------------------------------------------------------------------
parameter_list_or_empty :
    parameter_list
    | empty
    ;

//---------------------------------------------------------------------
parameter_list :
    parameter_list T_COMMA parameter
    | parameter
    ;

//---------------------------------------------------------------------
parameter:
    T_ID T_ASSIGN expression
    {
        Expression *expr = $3;
        Status status;
        Gpl_type type;

        status = cur_object_under_construction->get_member_variable_type(*$1, type);

        if (status == OK)
        {
            if (type == INT)
            {
                if (expr->get_type() != INT)
                {
                    Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, obj_name, *$1, "");
                }
                else
                {
                    int val = expr->eval_int();
                    cur_object_under_construction->set_member_variable(*$1, val);
                }
            }
            else if (type == DOUBLE)
            {
                double val = expr->eval_double();
                cur_object_under_construction->set_member_variable(*$1, val);
            }
            else if (type == STRING)
            {
                string val = expr->eval_string();
                cur_object_under_construction->set_member_variable(*$1, val);
            }
            else if (type == ANIMATION_BLOCK)
            {
                Gpl_type t;
                Animation_block *val = expr->eval_animation_block(); 
                Symbol *symbol = val->get_parameter_symbol();
                Game_object *game_obj = symbol->get_game_object_value();  

                if (game_obj->type() == cur_object_under_construction->type())
                {
                    status = cur_object_under_construction->set_member_variable(*$1, val);
                }
                else
                {
                    Error::error(Error::TYPE_MISMATCH_BETWEEN_ANIMATION_BLOCK_AND_OBJECT,
                                 obj_name, val->name(), "");
                }
            }
        }
        
        if (status == MEMBER_NOT_OF_GIVEN_TYPE)
        {
            Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, obj_name, *$1, "");   
        }
        if (status == MEMBER_NOT_DECLARED)
        {
            Error::error(Error::UNKNOWN_CONSTRUCTOR_PARAMETER, obj_class, *$1, "");
        }
    }
    ;

//---------------------------------------------------------------------
forward_declaration:
    T_FORWARD T_ANIMATION T_ID T_LPAREN animation_parameter T_RPAREN
    {
        Symbol *sym = symbol_table->lookup(*$3);
        Symbol *new_symbol;
        Game_object *game;

        if (sym)
        {
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$3, "", "");
        }
        else
        {
            Animation_block *animate = new Animation_block($5, *$3);
            new_symbol = new Symbol(ANIMATION_BLOCK, *$3, animate);

            if (!symbol_table->insert(new_symbol, *$3))
            {
                Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$3, "", "");
            }
        }
    }
    ;

//---------------------------------------------------------------------
block_list:
    block_list block
    | empty
    ;

//---------------------------------------------------------------------
block:
    initialization_block
    | animation_block
    | on_block
    ;

//---------------------------------------------------------------------
initialization_block:
    T_INITIALIZATION statement_block
    ;

//---------------------------------------------------------------------
animation_block:
    T_ANIMATION T_ID T_LPAREN check_animation_parameter T_RPAREN T_LBRACE { } statement_list T_RBRACE end_of_statement_block
    ;

//---------------------------------------------------------------------
animation_parameter:
    object_type T_ID
    {
        Symbol *new_symbol, *sym;

        switch ($1)
        {
            case T_TRIANGLE:
                cur_object_under_construction = new Triangle();
                obj_class = "Triangle";
                break;
            case T_RECTANGLE:
                cur_object_under_construction = new Rectangle();
                obj_class = "Rectangle";
                break;
            case T_CIRCLE:
                cur_object_under_construction = new Circle();
                obj_class = "Circle";
                break;
            case T_TEXTBOX:
                cur_object_under_construction = new Textbox();
                obj_class = "Textbox";
                break;
            case T_PIXMAP:
                cur_object_under_construction = new Pixmap();
                obj_class = "Pixmap";
                break;
        }
        cur_object_under_construction->never_animate();
        cur_object_under_construction->never_draw();

        sym = symbol_table->lookup(*$2);
        if (sym)
        {
            Error::error(Error::ANIMATION_PARAMETER_NAME_NOT_UNIQUE, *$2, "", "");
        }
        else
        {
            new_symbol = new Symbol(GAME_OBJECT, *$2, cur_object_under_construction);

            if (!symbol_table->insert(new_symbol, *$2))
            {
                Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2, "", "");
            }
            $$ = new_symbol;
        }
    }
    ;

//---------------------------------------------------------------------
check_animation_parameter:
    T_TRIANGLE T_ID
    | T_PIXMAP T_ID
    | T_CIRCLE T_ID
    | T_RECTANGLE T_ID
    | T_TEXTBOX T_ID
    ;

//---------------------------------------------------------------------
on_block:
    T_ON keystroke statement_block
    {
        event_manager->register_handler($2, $3);
    }
    ;

//---------------------------------------------------------------------
keystroke:
    T_SPACE
    {
        $$ = Window::SPACE;
    }
    | T_UPARROW
    {
        $$ = Window::UPARROW;
    }
    | T_DOWNARROW
    {
        $$ = Window::DOWNARROW;
    }
    | T_LEFTARROW
    {
        $$ = Window::LEFTARROW;  
    }
    | T_RIGHTARROW
    {
        $$ = Window::RIGHTARROW;
    }
    | T_LEFTMOUSE_DOWN
    {
        $$ = Window::LEFTMOUSE_DOWN;
    }
    | T_MIDDLEMOUSE_DOWN
    {
        $$ = Window::MIDDLEMOUSE_DOWN;
    }
    | T_RIGHTMOUSE_DOWN
    {
        $$ = Window::RIGHTMOUSE_DOWN;
    }
    | T_LEFTMOUSE_UP
    {
        $$ = Window::LEFTMOUSE_UP;
    }
    | T_MIDDLEMOUSE_UP
    {
        $$ = Window::MIDDLEMOUSE_UP;
    }
    | T_RIGHTMOUSE_UP
    {
        $$ = Window::RIGHTMOUSE_UP;
    }
    | T_MOUSE_MOVE
    {
        $$ = Window::MOUSE_MOVE;
    }
    | T_MOUSE_DRAG
    {
        $$ = Window::MOUSE_DRAG;
    }
    | T_AKEY 
    {
        $$ = Window::AKEY;
    }
    | T_SKEY 
    {
        $$ = Window::SKEY;
    }
    | T_DKEY 
    {
        $$ = Window::DKEY;
    }
    | T_FKEY 
    {
        $$ = Window::FKEY;
    }
    | T_HKEY 
    {
        $$ = Window::HKEY;
    }
    | T_JKEY 
    {
        $$ = Window::JKEY;
    }
    | T_KKEY 
    {
        $$ = Window::KKEY;
    }
    | T_LKEY 
    {
        $$ = Window::LKEY;
    }
    | T_WKEY 
    {
        $$ = Window::WKEY;
    }
    | T_F1
    {
        $$ = Window::F1;
    }
    ;

//---------------------------------------------------------------------
if_block:
    statement_block_creator statement end_of_statement_block
    | statement_block
    ;

//---------------------------------------------------------------------
statement_block:
    T_LBRACE statement_block_creator statement_list T_RBRACE end_of_statement_block
    {
        $$ = $5;
    }
    ;

//---------------------------------------------------------------------
statement_block_creator:
    // this goes to nothing so that you can put an action here in p7
    {
        Statement_block *new_stmt_block = new Statement_block();
        global_statement_stack.push(new_stmt_block);

        $$ = new_stmt_block;
    }
    ;

//---------------------------------------------------------------------
end_of_statement_block:
    // this goes to nothing so that you can put an action here in p7
    {
        Statement_block *top_stmt_block = global_statement_stack.top();
        global_statement_stack.pop();

        $$ = top_stmt_block;
    }
    ;

//---------------------------------------------------------------------
statement_list:
    statement_list statement
    | empty
    ;

//---------------------------------------------------------------------
statement:
    if_statement
    | for_statement
    | assign_statement T_SEMIC
    | print_statement T_SEMIC
    | exit_statement T_SEMIC
    ;

//---------------------------------------------------------------------
if_statement: 
    T_IF T_LPAREN expression T_RPAREN if_block %prec IF_NO_ELSE
    {
        Statement *new_stmt = new If_stmt($3, $5, NULL);
        global_statement_stack.top()->insert(new_stmt);
    }
    | T_IF T_LPAREN expression T_RPAREN if_block T_ELSE if_block 
    {
        Statement *new_stmt = new If_stmt($3, $5, $7);
        global_statement_stack.top()->insert(new_stmt);
    }
    ;

//---------------------------------------------------------------------
for_statement:
    T_FOR T_LPAREN statement_block_creator assign_statement end_of_statement_block T_SEMIC expression T_SEMIC statement_block_creator assign_statement end_of_statement_block T_RPAREN statement_block
    ;

//---------------------------------------------------------------------
print_statement:
    T_PRINT T_LPAREN expression T_RPAREN
    {
        Statement *new_stmt = new Print_stmt($3);
        global_statement_stack.top()->insert(new_stmt);
    }
    ;

//---------------------------------------------------------------------
exit_statement:
    T_EXIT T_LPAREN expression T_RPAREN
    {
        Statement *new_stmt = new Exit_stmt($3);
        global_statement_stack.top()->insert(new_stmt);
    }
    ;

//---------------------------------------------------------------------
assign_statement:
    variable T_ASSIGN expression
    {
        Statement *new_stmt = new Assignment_stmt($1, $3, "=");
        global_statement_stack.top()->insert(new_stmt);
    }
    | variable T_PLUS_ASSIGN expression
    {
        Statement *new_stmt = new Assignment_stmt($1, $3, "+=");
        global_statement_stack.top()->insert(new_stmt);
    }
    | variable T_MINUS_ASSIGN expression
    {
        Statement *new_stmt = new Assignment_stmt($1, $3, "-=");
        global_statement_stack.top()->insert(new_stmt);
    }
    ;

//---------------------------------------------------------------------
variable:
    T_ID
    {
        ostringstream ost;
        ost << *$1 << "[0]";
        Symbol *sym = symbol_table->lookup(*$1);
        Symbol *sym2 = symbol_table->lookup(ost.str());
        if (sym == NULL)
        {
            Error::error(Error::UNDECLARED_VARIABLE, *$1, "", "");
            $$ = undeclared_var;
        }
        else
        {
            $$ = new Variable(*$1, sym->get_type(), sym);
        }
    }
    | T_ID T_LBRACKET expression T_RBRACKET
    {
        Expression *init_expr = $3;
        string tmp, tmp2;
        ostringstream convert, convert_val, db_to_str;
        int expr_val = 0, index_val = 0;

        convert << *$1 << "[0]";
        tmp = convert.str();
        Symbol *sym = symbol_table->lookup(tmp);
        if (sym != NULL && init_expr->get_type() == INT)
        {
            index_val = init_expr->eval_int();
            convert_val << *$1 << "[" << index_val << "]";
            Symbol *sym2 = symbol_table->lookup(convert_val.str());
            if (!sym2)
            {
                db_to_str << index_val;
                tmp2 = db_to_str.str();
                Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, 
                             *$1, tmp2, "");
                $$ = undeclared_var;
            }
        }
        if (sym == NULL)
        {
            Error::error(Error::UNDECLARED_VARIABLE, *$1, "", "");
            $$ = undeclared_var;
        }
        else if (init_expr->get_type() == STRING)
        {
            Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER,
                         *$1, "A string expression", "");
            $$ = undeclared_var;
        }
        else if (init_expr->get_type() == DOUBLE)
        {
            Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER,
                         *$1, "A double expression", "");
            $$ = undeclared_var;
        }
        else
        {
            expr_val = init_expr->eval_int();
            if (init_expr->eval_int() < 0)
            {
                Error::error(Error::INVALID_ARRAY_SIZE, *$1, "", "");
                $$ = undeclared_var;
            }
            else
                $$ = new Variable(*$1, sym->get_type(), sym, init_expr);
        }
    }
    | T_ID T_PERIOD T_ID
    {
        Status status;
        Symbol *sym1 = symbol_table->lookup(*$1);

        if (sym1) 
        {
            if (sym1->get_type() != GAME_OBJECT)
            {
                Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT,
                             *$1, "", "");
                $$ = undeclared_var;
            }
            else
            {
                Gpl_type s, t;
                Symbol *new_symbol;
                Game_object *obj = sym1->get_game_object_value();
                Status status2 = obj->get_member_variable_type(*$3, t);
                //status = cur_object_under_construction->get_member_variable_type(*$3, t);
                
                if (status2 == OK) //&& status2 == OK)
                {
                    if (t == STRING)
                    {
                        string value;
                        obj->get_member_variable(*$3, value);
                        new_symbol = new Symbol(t, *$3, value);
                    }
                    else if (t == DOUBLE)
                    {
                        double value;
                        obj->get_member_variable(*$3, value);
                        new_symbol = new Symbol(t, *$3, value);
                    }
                    else if (t == INT)
                    {
                        int value;
                        obj->get_member_variable(*$3, value);
                        new_symbol = new Symbol(t, *$3, value);
                    }
                    else if (t == ANIMATION_BLOCK)
                    {
                        Animation_block *ani;
                        obj->get_member_variable(*$3, ani);
                        new_symbol = new Symbol(t, *$3, ani);
                    }
                    $$ = new Variable(*$3, t, new_symbol);
                }
                else 
                {
                     Error::error(Error::UNDECLARED_MEMBER,
                                  obj_name, *$3, ""); 
                     $$ = undeclared_var;
                }
            }
        }
        else
        {
            Error::error(Error::UNDECLARED_VARIABLE, *$1, "", "");
            $$ = undeclared_var;
        }

    }
    | T_ID T_LBRACKET expression T_RBRACKET T_PERIOD T_ID
    {
        Expression *expr = $3;
        Gpl_type t;
        ostringstream st, st2;
        Symbol *new_symbol;

        st << *$1 << "[0]";
        Symbol *sym1 = symbol_table->lookup(st.str());

        if (sym1)
        {
            if (sym1->get_type() != GAME_OBJECT)
            {
                Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT,
                             *$1, "", "");
                $$ = undeclared_var;
            }
            else if (expr->get_type() == DOUBLE)
            {
                Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER,
                             *$1, "A double expression", "");
                $$ = undeclared_var;
            }
            else if (expr->get_type() == STRING)
            {
                Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER,
                             *$1, "A string expression", "");
                $$ = undeclared_var;
            }
            else
            {
                Status status;
                int value = expr->eval_int();
                Game_object *obj = sym1->get_game_object_value();
                status = obj->get_member_variable_type(*$6, t);
                
                if (status == OK)
                {
                    if (t == INT)
                    {
                        int val;
                        obj->get_member_variable(*$6, val);
                        new_symbol = new Symbol(t, *$6, val);
                    }
                    else if (t == DOUBLE)
                    {
                        double val;
                        obj->get_member_variable(*$6, val);
                        new_symbol = new Symbol(t, *$6, val);
                    }
                    else if (t == STRING)
                    {
                        string val;
                        obj->get_member_variable(*$6, val);
                        new_symbol = new Symbol(t, *$6, val);
                    }
                    else if (t == ANIMATION_BLOCK)
                    {
                        Animation_block *ani;
                        obj->get_member_variable(*$6, ani);
                        new_symbol = new Symbol(t, *$6, ani);
                    }
                    $$ = new Variable(*$1, t, new_symbol);
                }
                if (status == MEMBER_NOT_OF_GIVEN_TYPE)
                {
                    Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, obj_name, *$1, "");   
                }
                if (status == MEMBER_NOT_DECLARED)
                {
                    Error::error(Error::UNKNOWN_CONSTRUCTOR_PARAMETER, obj_class, *$1, "");
                }         
            }
        }
        else
        {
            Error::error(Error::UNDECLARED_VARIABLE, *$1, "", "");
            $$ = undeclared_var;
        }
    }
    ;

//---------------------------------------------------------------------
expression:
    primary_expression
    {
        $$ = $1;
    }
    | expression T_OR expression 
    {
        int a, b, c;
        if ($1 == NULL)
        {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                         "or", "", "");
            $$ = new Expression(0);
        }
        else if ($3 == NULL)
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,
                         "or", "", ""); 
            $$ = new Expression(0);
        }
        else
        {
            a = $1->get_type();
            b = $3->get_type();
            c = a|b;
            if (a == STRING)
            {
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                              operator_to_string(OR), "", "");
                $$ = new Expression(0);
            }
            else if (b == STRING)
            {
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, 
                             operator_to_string(OR), "", "");
                $$ = new Expression(0);
            }
            else
            {
                $$ = new Expression(OR, LOGICAL_OP, $1, $3);
            }
        }
    }
    | expression T_AND expression 
    {
        int a, b, c;
        if ($1 == NULL)
        {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                         "and", "", "");
            $$ = new Expression(0);
        }
        else if ($3 == NULL)
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,
                         "and", "", ""); 
            $$ = new Expression(0);
        }
        else
        {
            a = $1->get_type();
            b = $3->get_type();
            c = a|b;

            if (a == STRING)
            {
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                             operator_to_string(AND), "", "");
                $$ = new Expression(0);
            }
            else if (b == STRING)
            {
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, 
                             operator_to_string(AND), "", "");
                $$ = new Expression(0);
            }
            else
            {
                $$ = new Expression(AND, LOGICAL_OP, $1, $3);
            }
        }
    }
    | expression T_LESS_EQUAL expression 
    {
        if ($1 == NULL)
        {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                         "less than equal", "", "");
            $$ = new Expression(0);
        }
        else if ($3 == NULL)
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,
                         "less than equal", "", ""); 
            $$ = new Expression(0);
        }
        else
        {
            $$ = new Expression(LESS_THAN_EQUAL, LOGICAL_OP, $1, $3);
        }
    }
    | expression T_GREATER_EQUAL  expression 
    {
        if ($1 == NULL)
        {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                         "greater than equal", "", "");
            $$ = new Expression(0);
        }
        else if ($3 == NULL)
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,
                         "greater than equal", "", ""); 
            $$ = new Expression(0);
        }
        else
        {
            $$ = new Expression(GREATER_THAN_EQUAL, LOGICAL_OP, $1, $3);
        }
    }
    | expression T_LESS expression 
    {
        if ($1 == NULL)
        {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                         "less than", "", "");
            $$ = new Expression(0);
        }
        else if ($3 == NULL)
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,
                         "less than", "", ""); 
            $$ = new Expression(0);
        }
        else
        {
            $$ = new Expression(LESS_THAN, LOGICAL_OP, $1, $3);
        }
    }
    | expression T_GREATER expression 
    {
        if ($1 == NULL)
        {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                         "greater than", "", "");
            $$ = new Expression(0);
        }
        else if ($3 == NULL)
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,
                         "greater than", "", ""); 
            $$ = new Expression(0);
        }
        else
        {
            $$ = new Expression(GREATER_THAN, LOGICAL_OP, $1, $3);
        }
    }
    | expression T_EQUAL expression 
    {
        if ($1 == NULL)
        {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                         "equal", "", "");
            $$ = new Expression(0);
        }
        else if ($3 == NULL)
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,
                         "equal", "", ""); 
            $$ = new Expression(0);
        }
        else
        {
            $$ = new Expression(EQUAL, LOGICAL_OP, $1, $3);
        }
    }
    | expression T_NOT_EQUAL expression 
    {
        if ($1 == NULL)
        {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                         "not equal", "", "");
            $$ = new Expression(0);
        }
        else if ($3 == NULL)
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,
                         "not equal", "", ""); 
            $$ = new Expression(0);
        }
        else
        {
            $$ = new Expression(NOT_EQUAL, LOGICAL_OP, $1, $3);
        }
    }
    | expression T_PLUS expression 
    {
        //check that the type of $1 and $3 are compatible
        if ($1 == NULL)
        {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                         "plus", "", "");
            $$ = new Expression(0);
        }
        else if ($3 == NULL)
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,
                         "plus", "", ""); 
            $$ = new Expression(0);
        }
        else
        {
            $$ = new Expression(PLUS, BINARY_OP, $1, $3);
        }
    }
    | expression T_MINUS expression 
    {
        int a, b, c;
        if ($1 == NULL)
        {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                         "minus", "", "");
            $$ = new Expression(0);
        }
        else if ($3 == NULL)
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,
                         "minus", "", ""); 
            $$ = new Expression(0);
        }
        else
        {
            a = $1->get_type();
            b = $3->get_type();
            c = a|b;
            if (a == STRING) 
            {
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                             operator_to_string(MINUS), "", "");
                $$ = new Expression(0);
            }
            else if (b == STRING)
            {
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, 
                             operator_to_string(MINUS), "", "");
                $$ = new Expression(0);
            }
            else
            {
               $$ = new Expression(MINUS, BINARY_OP, $1, $3);
            }
        }
    }
    | expression T_ASTERISK expression 
    {
        int a, b, c;
        a = $1->get_type();
        b = $3->get_type();

        if (a == STRING) 
        {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                         operator_to_string(MULTIPLY), "", "");
            $$ = new Expression(0);
        }
        else if (b == STRING)
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, 
                         operator_to_string(MULTIPLY), "", "");
            $$ = new Expression(0);
        }
        else
        {
            $$ = new Expression(MULTIPLY, BINARY_OP, $1, $3);
        }
    }
    | expression T_DIVIDE expression 
    {
        int a, b, c;
        if ($1 == NULL)
        {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                         "divide", "", "");
            $$ = new Expression(0);
        }
        else if ($3 == NULL)
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,
                         "divide", "", ""); 
            $$ = new Expression(0);
        }
        else
        {
            a = $1->get_type();
            b = $3->get_type();
            c = a|b;
            if (a == STRING) 
            {
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                             operator_to_string(MULTIPLY), "", "");
                $$ = new Expression(0);
            }
            else if (b == STRING)
            {
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, 
                             operator_to_string(MULTIPLY), "", "");
                $$ = new Expression(0);
            }
            else if ($3->eval_double() == 0)
            {
                Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME, "", "", "");
                $$ = new Expression(0);
            }
            else
            {
                $$ = new Expression(DIVIDE, BINARY_OP, $1, $3);
            }
        }
    }
    | expression T_MOD expression 
    {
        int a, b, c;
        if ($1->get_type()  != INT)
        {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, 
                         "mod", "", "");
            $$ = new Expression(0);
        }
        else if ($3->get_type() != INT)
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,
                         "mod", "", "");
            $$ = new Expression(0);
        }
        else if ($3->eval_int() == 0)
        {
            Error::error(Error::MOD_BY_ZERO_AT_PARSE_TIME, "", "", "");
            $$ = new Expression(0);
        }
        else
        {
            $$ = new Expression(MOD, BINARY_OP, $1, $3);
        }
    }
    | T_MINUS  expression %prec UNARY_OPS
    {
        int a = $2->get_type();
        if (a != STRING)
        {
            $$ = new Expression(MINUS, UNARY_OP, $2);
        }
        else 
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, 
                          operator_to_string(MINUS), "", "");
            $$ = new Expression(0);
        }
    }
    | T_NOT  expression %prec UNARY_OPS
    {
        Expression *init_expr = $2;
        int a = $2->get_type();
        if ($2 && a != 4)
        {
            $$ = new Expression(NOT, UNARY_OP, $2);
        } 
        else 
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, 
                         operator_to_string(NOT), "", "");
            $$ = new Expression(0);
        }
    }
    | math_operator T_LPAREN expression T_RPAREN
    {
        Expression *init_expr = $3;

        if (init_expr->get_type() == STRING)
        {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, 
                         operator_to_string($1), "", "");
            $$ = new Expression(0);
        }
        else
            $$ = new Expression($1, MATH_OP, $3);
    }
    | variable geometric_operator variable
    {

    }
    ;

//---------------------------------------------------------------------
primary_expression:
    T_LPAREN  expression T_RPAREN
    {
        $$ = $2;
    }
    | variable
    {
        $$ = new Expression($1, VARIABLE);
    }
    | T_INT_CONSTANT
    {    
        $$ = new Expression($1, INT_CONST);
    }
    | T_TRUE
    {
        $$ = new Expression(1, TRUE);
    }
    | T_FALSE
    {
        $$ = new Expression(0, FALSE);
    }
    | T_DOUBLE_CONSTANT
    {
        $$ = new Expression($1, DOUBLE_CONST);
    }
    | T_STRING_CONSTANT
    {
        $$ = new Expression(*$1, STRING_CONST);
    }
    ;

//---------------------------------------------------------------------
geometric_operator:
    T_TOUCHES
    | T_NEAR
    ;

//---------------------------------------------------------------------
math_operator:
    T_SIN
    {
        $$ = SIN;
    }
    | T_COS
    {
        $$ = COS;
    }
    | T_TAN
    {
        $$ = TAN;
    }
    | T_ASIN
    {
        $$ = ASIN;
    }
    | T_ACOS
    {
        $$ = ACOS;
    }
    | T_ATAN
    {
        $$ = ATAN;
    }
    | T_SQRT
    {
        $$ = SQRT;
    }
    | T_ABS
    {
        $$ = ABS;
    }
    | T_FLOOR
    {
        $$ = FLOOR;
    }
    | T_RANDOM
    {
        $$ = RANDOM;
    }
    ;

//---------------------------------------------------------------------
empty:
    // empty goes to nothing so that you can use empty in productions
    // when you want a production to go to nothing
    ;
