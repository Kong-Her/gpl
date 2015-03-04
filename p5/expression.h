#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <sstream>
#include <string>
#include "parser.h"
#include "variable.h"
#include "gpl_type.h"
using namespace std;

class Expression
{
    public:
        //class Variable;
        Expression(int, Expression *, Expression *);
        Expression(double, Expression *, Expression *);
        Expression(string, Expression *, Expression *);
        Expression(Variable *);
        Expression(Operator_type, Expression *, Expression *);
        Expression(Operator_type, Expression *);
        int eval_int();
        double eval_double();
        string eval_string();
        int get_type();
        Operator_type get_op_type();

    private:
        Operator_type m_op;
        Gpl_type m_gpl_type;
        Variable *m_var;
        Expression *m_left;
        Expression *m_right;
        int m_int_val;
        double m_double_val;
        string m_string_val;


};

#endif
