#ifndef VARIABLE_H
#define VARIABLE_H

#include "gpl_type.h"
#include "expression.h"
#include "symbol.h"
#include "symbol_table.h"
#include <string>
class Expression;
using namespace std;

class Variable
{
    public:
        Variable(string var_name, Gpl_type gpl_type, Symbol*);
        Variable(string var_name, Gpl_type gpl_type, Symbol*, 
                 Expression *index_expr);
        void set_value();
        int get_int_value();
        double get_double_value();
        string get_string_value();
        Gpl_type get_var_type();

    private:
        string m_var_name;
        Expression *m_index_expr;
        Symbol *m_sym;
        Gpl_type m_gpl_type;

};

#endif
