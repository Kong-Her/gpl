#ifndef VARIABLE_H
#define VARIABLE_H

#include "gpl_type.h"
#include "expression.h"
#include "symbol.h"
#include "symbol_table.h"
#include "animation_block.h"
#include <string>
class Expression;
using namespace std;

class Variable
{
    public:
        Variable(Symbol *);
        Variable(string var_name, Gpl_type gpl_type, Symbol*);
        Variable(string var_name, Gpl_type gpl_type, Symbol*, 
                 Expression *index_expr);
        int get_int_value();
        double get_double_value();
        string get_string_value();
        string get_var_name();
        Animation_block *get_animation_block();
        Gpl_type get_var_type();
        Symbol *get_symbol();

    private:
        string m_var_name;
        Expression *m_index_expr;
        Symbol *m_sym;
        Gpl_type m_gpl_type;

};

#endif
