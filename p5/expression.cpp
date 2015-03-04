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
/*********************************************************************************/
int Expression::eval_int()
{
    if (m_op == PLUS)
    {
        if (m_left && m_right)
        return m_left->eval_int() + m_right->eval_int();
    }
    if (m_op == MINUS)
    {
        return m_left->eval_int() - m_right->eval_int();
    }
    if (m_op == UNARY_MINUS)
    {
        return -m_left->eval_int();
    }
    if (m_op == MULTIPLY)
    {
        return m_left->eval_int() * m_right->eval_int();
    }
    if (m_op == DIVIDE)
    {
        if (!m_left || !m_right)
        {
            return 0;
        }
        else
            return m_left->eval_int() / m_right->eval_int();
    }
    if (m_op == NOT)
    {
        return !m_left->eval_int();
    }
    if (m_op == LESS_THAN)
    {
        return m_left->eval_int() < m_right->eval_int();
    }
    if (m_op == GREATER_THAN)
    {
        return m_left->eval_int() > m_right->eval_int();
    } 
    if (m_op == LESS_THAN_EQUAL)
    {
        return m_left->eval_int() <= m_right->eval_int();
    } 
    if (m_op == GREATER_THAN_EQUAL)
    {
        return m_left->eval_int() >= m_right->eval_int();
    } 
    if (m_op == AND)
    {
        return m_left->eval_int() && m_right->eval_int();
    }
    if (m_op == OR)
    {
        return m_left->eval_int() || m_right->eval_int();
    }
    if (m_op == SIN)
    {
        return sin((m_left->eval_int() * M_PI) / 180);
    }
    if (m_op == COS)
    {
        return cos((m_left->eval_int() * M_PI) / 180);
    }
    if (m_op == TAN)
    {
        return tan((m_left->eval_int() * M_PI) / 180);
    }
    if (m_op == ASIN)
    {
        return asin((m_left->eval_int() * M_PI) / 180);
    }
    if (m_op == ACOS)
    {
        return acos((m_left->eval_int() * M_PI) / 180);
    }
    if (m_op == ATAN)
    {
        return atan((m_left->eval_int() * M_PI) / 180);
    }
    if (m_op == SQRT)
    {
        return sqrt(m_left->eval_int());
    }
    if (m_op == FLOOR)
    {
        return floor(m_left->eval_double());
    }
    if (m_op == ABS)
    {
        return abs(m_left->eval_int());
    }
    if (m_op == RANDOM)
    {
        return rand() % m_left->eval_int();
    }
    /*if (m_var) 
    {
        return m_var->get_int_value();
    }*/
    return m_int_val;
}
/*********************************************************************************/
double Expression::eval_double()
{
    if (m_op == PLUS)
    {
        if (m_left && m_right)
        return m_left->eval_double() + m_right->eval_double();
    }
    if (m_op == MINUS)
    {
        return m_left->eval_double() - m_right->eval_double();
    }
    if (m_op == UNARY_MINUS)
    {
        return (-1) * m_left->eval_double();
    }
    if (m_op == MULTIPLY)
    {
        if (!m_left || !m_right)
        {
            return 0;
        }
        else
            return m_left->eval_double() * m_right->eval_double();
    }
    if (m_op == DIVIDE)
    {
        if (!m_left || !m_right)
        {
            return 0;
        }
        else
            return m_left->eval_double() / m_right->eval_double();
    }
    if (m_op == NOT)
    {
        return !m_left->eval_double();
    }
    if (m_op == AND)
    {
        return m_left->eval_int() && m_right->eval_int();
    }
    if (m_op == LESS_THAN)
    {
        return m_left->eval_int() < m_right->eval_int();
    }
    if (m_op == GREATER_THAN)
    {
        return m_left->eval_int() > m_right->eval_int();
    } 
    if (m_op == LESS_THAN_EQUAL)
    {
        return m_left->eval_int() <= m_right->eval_int();
    } 
    if (m_op == GREATER_THAN_EQUAL)
    {
        return m_left->eval_int() >= m_right->eval_int();
    } 
    if (m_op == OR)
    {
        return m_left->eval_int() || m_right->eval_int();
    }
    if (m_op == SIN)
    {
        return sin((m_left->eval_int() * M_PI) / 180);
    }
    if (m_op == COS)
    {
        return cos((m_left->eval_int() * M_PI) / 180);
    }
    if (m_op == TAN)
    {
        return tan((m_left->eval_int() * M_PI) / 180);
    }
    if (m_op == ASIN)
    {
        return asin((m_left->eval_int() * M_PI) / 180);
    }
    if (m_op == ACOS)
    {
        return acos((m_left->eval_int() * M_PI) / 180);
    }
    if (m_op == ATAN)
    {
        return atan((m_left->eval_int() * M_PI) / 180);
    }
    if (m_op == SQRT)
    {
        return sqrt(m_left->eval_double());
    }
    if (m_op == FLOOR)
    {
        return floor(m_left->eval_double());
    }
    if (m_op == ABS)
    {
        return abs(m_left->eval_int());
    }
    return m_double_val;
}
/*********************************************************************************/
string Expression::eval_string()
{
    string str = "";
    ostringstream convert;
    /*int a, b, c;

    a = m_left->get_type();
    b = m_right->get_type();
    c = a|b;*/

    if (m_gpl_type == INT)
    {
        string tmp;
        int value = m_left->eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
    }
    if (m_gpl_type == DOUBLE)
    {
        string tmp;
        double value = m_left->eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
    }
    /*if (m_var)*/
    if (m_op == PLUS)
    {
        if (m_left && m_right)
        return m_left->eval_string() + m_right->eval_string();
    }
    /*if ((m_op == MINUS) && (c == 1 || c == 2 || c == 3))
    {
        string tmp;
        double d = m_left->eval_double() - m_right->eval_double();
        convert << d;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
    }*/
    /*if (m_op == UNARY_MINUS)
    {
        return -m_left->eval_string();
    }
    if (m_op == MULTIPLY)
    {
        return m_left->eval_string() * m_right->eval_string();
    }
    if (m_op == DIVIDE)
    {
        if (!m_left || !m_right)
        {
            return 0;
        }
        else
            return m_left->eval_string() / m_right->eval_string();
    }
    if (m_op == NOT)
    {
        return !m_left->eval_string();
    }*/
    if (m_op == LESS_THAN)
    {
        string tmp;
        int value = m_left->eval_int() < m_right->eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
        //return m_left->eval_int() < m_right->eval_int();
    }
    if (m_op == GREATER_THAN)
    {
        string tmp;
        int value = m_left->eval_int() > m_right->eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
        //return m_left->eval_int() > m_right->eval_int();
    } 
    if (m_op == LESS_THAN_EQUAL)
    {
        string tmp;
        int value = m_left->eval_int() <= m_right->eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
        //return m_left->eval_int() <= m_right->eval_int();
    } 
    if (m_op == GREATER_THAN_EQUAL)
    {
        string tmp;
        int value = m_left->eval_int() >= m_right->eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
        //return m_left->eval_int() >= m_right->eval_int();
    } 
    if (m_op == AND)
    {
        string tmp;
        int value = m_left->eval_int() &&  m_right->eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
        //return m_left->eval_int() && m_right->eval_int();
    }
    if (m_op == OR)
    {
        string tmp;
        int value = m_left->eval_int() || m_right->eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
        //return m_left->eval_int() || m_right->eval_int();
    }
    return m_string_val;
}
/*********************************************************************************/
int Expression::get_type()
{
   return m_gpl_type; 
}
Operator_type Expression::get_op_type()
{
    return m_op;
}
