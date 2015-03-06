#include "expression.h"
#include "variable.h"

Expression::Expression(int val, Kind kind)
{
    m_int_val = val;
    m_kind = kind;
    m_type = INT;
}
Expression::Expression(double val, Kind kind)
{
    m_double_val = val;
    m_kind = kind;
    m_type = DOUBLE;
}
Expression::Expression(string val, Kind kind)
{
    m_string_val = val;
    m_kind = kind;
    m_type = STRING;
}
Expression::Expression(Variable *var, Kind kind)
{
    m_var = var;
    m_kind = kind;
}
Expression::Expression(Operator_type op, Kind kind, Expression *left, Expression *right)
{
    //find the type (m_type)
    //check both left and right and determine the type
    m_op = op;
    m_kind = kind;
    m_left = left;
    m_right = right;
}
Expression::Expression(Operator_type op, Kind kind, Expression *left)
{
    //find the type (m_type)
    //check both left and right and determine the type
    m_op = op;
    m_kind = kind;
    m_left = left;
}
/*********************************************************************************/
int Expression::eval_int()
{
    if (m_type == DOUBLE)
    {
        return eval_double();
    }
    if (m_kind == BINARY_OP)
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
        if (m_op == MULTIPLY)
        {
            if (!m_left || !m_right)
            {
                return 0;
            }
            else
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
        if (m_op == NOT_EQUAL)
        {
            return m_left->eval_int() != m_right->eval_int();
        }
        if (m_op == EQUAL)
        {
            int a, b, c;
            a = m_left->get_type();
            b = m_right->get_type();
            c = a|b;

            if (c == 1)
            {
                return m_left->eval_int() == m_right->eval_int();
            }
            if (c == 2)
            {
                return m_left->eval_double() == m_right->eval_double();
            }
            else if (a == 1 && b == 2)
            {
                return m_left->eval_int() == m_right->eval_double();
            }
            else if (a == 2 && b == 1) 
            {
                return m_left->eval_double() == m_right->eval_int();
            }
            else 
            {
                return m_left->eval_string() == m_right->eval_string();
            }
        }
        if (m_op == LESS_THAN)
        {
            int a, b, c;
            a = m_left->get_type();
            b = m_right->get_type();
            c = a|b;

            if (c == 1)
            {
                return m_left->eval_int() < m_right->eval_int();
            }
            if (c == 2)
            {
                return m_left->eval_double() < m_right->eval_double();
            }
            else if (a == 1 && b == 2)
            {
                return m_left->eval_int() < m_right->eval_double();
            }
            else if (a == 2 && b == 1) 
            {
                return m_left->eval_double() < m_right->eval_int();
            }
            else 
            {
                return m_left->eval_string() < m_right->eval_string();
            }
        }
        if (m_op == GREATER_THAN)
        {
            int a, b, c;
            a = m_left->get_type();
            b = m_right->get_type();
            c = a|b;

            if (c == 1)
            {
                return m_left->eval_int() > m_right->eval_int();
            }
            else if (c == 2)
            {
                return m_left->eval_double() > m_right->eval_double();
            }
            else if (a == 1 && b == 2)
            {
                return m_left->eval_int() > m_right->eval_double();
            }
            else if (a == 2 && b == 1)
            {
                return m_left->eval_double() > m_right->eval_int();
            }
            else
            {
                return m_left->eval_string() > m_right->eval_string();
            }
        } 
        if (m_op == LESS_THAN_EQUAL)
        {
            int a, b, c;
            a = m_left->get_type();
            b = m_right->get_type();
            c = a|b;
            if (c == 1)
            {
                return m_left->eval_int() <= m_right->eval_int();
            }
            else if (c == 2)
            {
                return m_left->eval_double() <= m_right->eval_double();
            }
            else if (a == 1 && b == 2)
            {
                return m_left->eval_int() <= m_right->eval_double();
            }
            else if (a == 2 && b == 1)
            {
                return m_left->eval_double() <= m_right->eval_int();
            }
            else
            {
                return m_left->eval_string() <= m_right->eval_string();
            }
        } 
        if (m_op == GREATER_THAN_EQUAL)
        {
            int a, b, c;
            a = m_left->get_type();
            b = m_right->get_type();
            c = a|b;
            if (c == 1)
            {
                return m_left->eval_int() >= m_right->eval_int();
            }
            else if (c == 2)
            {
                return m_left->eval_double() >= m_right->eval_double();
            }
            else if (a == 1 && b == 2)
            {
                return m_left->eval_int() >= m_right->eval_double();
            }
            else if (a == 2 && b == 1)
            {
                return m_left->eval_double() >= m_right->eval_int();
            }
            else
            {
                return m_left->eval_string() >= m_right->eval_string();
            }
            return m_left->eval_int() >= m_right->eval_int();
        } 
        if (m_op == AND)
        {
            if (m_left->get_type() == 2 && m_right->get_type() == 2)
            {
                return m_left->eval_double() && m_right->eval_double();
            }
            return m_left->eval_int() && m_right->eval_int();
        }
        if (m_op == OR)
        {
            return m_left->eval_int() || m_right->eval_int();
        }
    }
    if (m_kind == UNARY_OP)
    {
        if (m_op == UNARY_MINUS)
        {
            return -m_left->eval_int();
        }
        if (m_op == NOT)
        {
            return !m_left->eval_int();
        }
    }
    if (m_kind == MATH_OP)
    {
        return m_left->eval_double();
    }
    if (m_kind == VARIABLE) 
    {
        return m_var->get_int_value(); 
    }
    if (m_kind == INT_CONST)
    {
        return m_int_val;
    }
    return 0;
}
/*********************************************************************************/
double Expression::eval_double()
{
    if (m_type == INT)
    {
        return eval_int();
    }
    if (m_kind == BINARY_OP)
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
            //else if (m_left->get_type() == 1 && m_right->get_type() == 1)
              //  return m_left->eval_int() / m_right->eval_int();
                return m_left->eval_double() / m_right->eval_double();
        }
    }
    if (m_kind == LOGICAL_OP)
    {
        return m_left->eval_int();
    }
        /*if (m_op == NOT_EQUAL)
        {
            return m_left->eval_int() != m_right->eval_int();
        }
        if (m_op == EQUAL)
        {
            int a, b, c;
            a = m_left->get_type();
            b = m_right->get_type();
            c = a|b;
            if (c == 1)
            {
                return m_left->eval_int() == m_right->eval_int();
            }
            else if (c == 2)
            {
                return m_left->eval_double() == m_right->eval_double();
            }
            else if (a == 1 && b == 2)
            {
                return m_left->eval_int() == m_right->eval_double();
            }
            else if (a == 2 && b == 1)
            {
                return m_left->eval_double() == m_right->eval_int();
            }
            else
            {
                return m_left->eval_string() == m_right->eval_string();
            }
            return m_left->eval_int() == m_right->eval_int();
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
        }*/
    
    if (m_kind == UNARY_OP)
    {
        if (m_op == NOT)
        {
            return !m_left->eval_double();
        }
        if (m_op == UNARY_MINUS)
        {
            return -m_left->eval_double();
        }
    }
    if (m_kind == MATH_OP)
    {
        if (m_op == SIN)
        {
            return sin((m_left->eval_double() * M_PI) / 180);
        }
        if (m_op == COS)
        {
            return cos((m_left->eval_double() * M_PI) / 180);
        }
        if (m_op == TAN)
        {
            return tan((m_left->eval_double() * M_PI) / 180);
        }
        if (m_op == ASIN)
        {
            double value = m_left->eval_double();
            value = value * M_PI / 180;
            return asin(value);
        }
        if (m_op == ACOS)
        {
            return acos((m_left->eval_double() * M_PI) / 180);
        }
        if (m_op == ATAN)
        {
            return atan((m_left->eval_double() * M_PI) / 180);
        }
        if (m_op == SQRT)
        {
            /*if (m_left->m_var)
            {
                return sqrt(m_left->m_var->get_double_value());
            }*/
            return sqrt(m_left->eval_double());
        }
        if (m_op == FLOOR)
        {
            return floor(m_left->eval_double());
        }
        if (m_op == ABS)
        {
            return abs(m_left->eval_double());
        }
    }
    if (m_kind == VARIABLE)
    {
        return m_var->get_double_value();
    }
    if (m_kind == DOUBLE_CONST)
    {
        return m_double_val;
    }
    return 0;
}
/*********************************************************************************/
string Expression::eval_string()
{
    string str = "";
    string tmp;
    ostringstream convert;
    /*int a, b, c;

    a = m_left->get_type();
    b = m_right->get_type();
    c = a|b;*/

    if (m_type == INT)
    {
        int value = m_left->eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
    }
    if (m_type == DOUBLE)
    {
        double value = m_left->eval_double();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
    }
    if (m_var)
    {
        return m_var->get_string_value();
    }
    if (m_op == PLUS)
    {
        if (m_left && m_right)
        return m_left->eval_string() + m_right->eval_string();
    }
    if (m_op == MINUS)
    {
        double value;
        if (m_left->get_type() == 1 && m_right->get_type() == 2)
        {
            value = m_left->eval_int() - m_right->eval_double();
        }
        else if (m_left->get_type() == 1 && m_right->get_type() == 1)
             value = m_left->eval_int() - m_right->eval_int();
        else if (m_left->get_type() == 2 && m_right->get_type() == 2)
             value = m_left->eval_double() - m_right->eval_double();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
        //return m_left->eval_double() - m_right->eval_double();
    }
    if (m_op == NOT)
    {
        int value = m_left->eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
        //return !m_left->eval_string();
    }
    if (m_op == NOT_EQUAL)
    {
        int value = m_left->eval_int() != m_right->eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
        //return m_left->eval_int() != m_right->eval_int();
    }
    if (m_op == EQUAL)
    {
        int a, b, c;
        double value;
        a = m_left->get_type();
        b = m_right->get_type();
        c = a|b;
        if (c == 1)
        {
            value = m_left->eval_int() == m_right->eval_int();
        }
        else if (c == 2)
        {
            value =  m_left->eval_double() == m_right->eval_double();
        }
        else if (a == 1 && b == 2)
        {
            value = m_left->eval_int() == m_right->eval_double();
        }
        else if (a == 2 && b == 1)
        {
            value = m_left->eval_double() == m_right->eval_int();
        }
        else
        {
            value = m_left->eval_string() == m_right->eval_string();
        }
        value = m_left->eval_int() == m_right->eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
        //return m_left->eval_int() == m_right->eval_int();
    }
    if (m_op == LESS_THAN)
    {
        int value;
        if (m_left->get_type() == 1 && m_right->get_type() == 2)
            value = m_left->eval_int() < m_right->eval_double();
        else if (m_left->get_type() == 2 && m_right->get_type() == 1)
            value = m_left->eval_int() < m_right->eval_double();
        else if (m_left->get_type() == 1 && m_right->get_type() == 1)
             value = m_left->eval_int() < m_right->eval_int();
        else 
             value = m_left->eval_int() < m_right->eval_int();
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
        int value;
        if (m_left->get_type() == 1 && m_right->get_type() == 2)
            value = m_left->eval_int() > m_right->eval_double();
        else if (m_left->get_type() == 2 && m_right->get_type() == 1)
            value = m_left->eval_int() > m_right->eval_double();
        else if (m_left->get_type() == 1 && m_right->get_type() == 1)
             value = m_left->eval_int() > m_right->eval_int();
        else 
             value = m_left->eval_int() > m_right->eval_int();
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
        int value;
        if (m_left->get_type() == 1 && m_right->get_type() == 2)
            value = m_left->eval_int() <= m_right->eval_double();
        else if (m_left->get_type() == 2 && m_right->get_type() == 1)
            value = m_left->eval_int() <= m_right->eval_double();
        else if (m_left->get_type() == 1 && m_right->get_type() == 1)
             value = m_left->eval_int() <= m_right->eval_int();
        else 
             value = m_left->eval_int() <= m_right->eval_int();
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
        int value;
        if (m_left->get_type() == 1 && m_right->get_type() == 2)
            value = m_left->eval_int() >= m_right->eval_double();
        else if (m_left->get_type() == 2 && m_right->get_type() == 1)
            value = m_left->eval_double() >= m_right->eval_int();
        else if (m_left->get_type() == 1 && m_right->get_type() == 1)
             value = m_left->eval_int() >= m_right->eval_int();
        else 
             value = m_left->eval_double() >= m_right->eval_double();
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
        int value = m_left->eval_int() || m_right->eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
        //return m_left->eval_int() || m_right->eval_int();
    }
    if (m_kind == STRING_CONST)
    {
        return m_string_val;
    }
    if (m_kind == VARIABLE)
    {
        return m_var->get_string_value();
    }
    return "";
}
/*********************************************************************************/
int Expression::get_type()
{
   return m_type; 
}
Operator_type Expression::get_op_type()
{
    return m_op;
}
