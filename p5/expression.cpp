#include "expression.h"

Expression::Expression(int val, Expression *left, Expression *right)
{
    m_int_val = val;
    m_left = left;
    m_right = right;
}
Expression::Expression(double val, Expression *left, Expression *right)
{
    m_double_val = val;
    m_left = left;
    m_right = right;
}
Expression::Expression(string val, Expression *left, Expression *right)
{
    m_string_val = val;
    m_left = left;
    m_right = right;
}
Expression::Expression(Variable *var)
{
    m_var = var;
}
Expression::Expression(Operator_type op, Expression *left, Expression *right)
{
    m_op = op;
    m_left = left;
    m_right = right;
}
Expression::Expression(Operator_type op, Expression *left)
{
    m_op = op;
    m_left = left;
}
int Expression::eval_int()
{
    /*if (m_var)
    {
        return m_var->get_value();
    }
    else if (m_op == PLUS)
    {
        return m_left->eval_int() + m_right->eval_int();
    }
    else if (m_op == MINUS)
    {
        return m_left->eval_int() - m_right->eval_int();
    }
    else if (m_op == MULTIPLY)
    {
        return m_left->eval_int() * m_right->eval_int();
    }
    else if (m_op == DIVIDE)
    {
        return m_left->eval_int() / m_right->eval_int();
    }
    else if (m_op == LESS_THAN)
    {
        return m_left->eval_int() < m_right->eval_int();
    }
    else if (m_op == GREATER_THAN)
    {
        return m_left->eval_int() > m_right->eval_int();
    } 
    else if (m_op == LESS_THAN_EQUAL)
    {
        return m_left->eval_int() <= m_right->eval_int();
    } 
    else if (m_op == GREATER_THAN_EQUAL)
    {
        return m_left->eval_int() >= m_right->eval_int();
    } 
    else if (m_op == AND)
    {
        return m_left->eval_int() && m_right->eval_int();
    }
    else if (m_op == OR)
    {
        return m_left->eval_int() || m_right->eval_int();
    }
    else*/ 
        return m_int_val;
}
double Expression::eval_double()
{
    return m_double_val;
}
string Expression::eval_string()
{
    string str = "";
    ostringstream convert;
    if (m_gpl_type == INT)
    {
        int value = eval_int();
        convert << value;
        str = convert.str();
        convert.clear();
        convert.str(string());
        return str;
    }
    else if (m_gpl_type == DOUBLE)
    {
        double value = eval_double();
        convert << value;
        str = convert.str();
        convert.clear();
        convert.str(string());
        return str;
    }
    /*else if (m_op == PLUS)
    {
        return m_left->eval_string() + m_right->eval_string();
    }*/
    return m_string_val;
}
int Expression::get_type()
{
   return m_gpl_type; 
}
Operator_type Expression::get_op_type()
{
    return m_op;
}
