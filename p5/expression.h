#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "parser.h"
//#include "gpl_type.h"
class Variable;
using namespace std;

enum Kind { INT_CONST, DOUBLE_CONST, STRING_CONST, VARIABLE,
            MATH_OP, LOGICAL_OP, BINARY_OP, UNARY_OP, TRUE, FALSE };

class Expression
{
    public:
        Expression(int, Kind);
        Expression(double, Kind);
        Expression(string, Kind);
        Expression(Variable *, Kind);
        Expression(Operator_type, Kind, Expression *, Expression *);
        Expression(Operator_type, Kind, Expression *);
        int eval_int();
        double eval_double();
        string eval_string();
        int get_type();
        Operator_type get_op_type();

    private:
        Operator_type m_op;
        Gpl_type m_type;
        Variable *m_var;
        Expression *m_left;
        Expression *m_right;
        int m_int_val;
        double m_double_val;
        string m_string_val;
        Kind m_kind;

};

#endif
