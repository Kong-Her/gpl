#ifndef VARIABLE_H
#define VARIABLE_H

#include "gpl_type.h"
#include "symbol.h"
#include "symbol_table.h"
#include <string>
class Expression;
using namespace std;

class Variable
{
    public:
        Variable(string var_name, Gpl_type gpl_type);
        Variable(string var_name, Gpl_type gpl_type, Expression *index_expr);
        void set_value();
        int get_int_value();
        double get_double_value();
        string get_string_value();

    private:
        string m_var_name;
        Expression *m_index_expr;
        Gpl_type m_gpl_type;

};

#endif
