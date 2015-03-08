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

    /*int var_type = var->get_var_type();
    
    if (var_type == INT)
    {
        m_type = INT;
    }
    else if (var_type == DOUBLE)
    {
        m_type = DOUBLE;
    }
    else 
    {
        m_type = STRING;
    }*/

}
Expression::Expression(Operator_type op, Kind kind, Expression *left, Expression *right)
{
    //find the type (m_type)
    //check both left and right and determine the type
    m_op = op;
    m_kind = kind;
    m_left = left;
    m_right = right; 

    /*int left_var_type = 0, right_var_type = 0;

    if (left && right)
    {
        if (op == AND || op == OR || op == EQUAL || 
            op == NOT_EQUAL || op == NOT_EQUAL || op == LESS_THAN || 
            op == LESS_THAN_EQUAL || op == GREATER_THAN_EQUAL || op == MOD)
        {
            m_type = INT;
        }
        else if (op == PLUS)
        {
            if (left->m_var || right->m_var)
            {
                if (left->m_var)
                {
                    left_var_type = left->m_var->get_var_type();
                    if (left_var_type == STRING)
                    {
                        m_type = STRING;
                    }
                    else if (left_var_type == DOUBLE)
                    {
                        m_type = DOUBLE;
                    }
                    else 
                    {
                        m_type = INT;
                    }
                }
                if (right->m_var)
                {
                    right_var_type = left->m_var->get_var_type();
                    if (right_var_type == STRING)
                    {
                        m_type = STRING;
                    }
                    else if (right_var_type == DOUBLE)
                    {
                        m_type = DOUBLE;
                    }
                    else 
                    {
                        m_type = INT;
                    }
                }
            }
            else if (left->get_type() == DOUBLE || right->get_type() == DOUBLE)
            {
                m_type =  DOUBLE;
            }
            else 
            {
                m_type = INT;
            }
        }
        else if (op == MINUS || op == MULTIPLY || op == DIVIDE)
        {
            if (left->get_type() == DOUBLE || right->get_type() == DOUBLE)
            {
                m_type = DOUBLE;
            }
            else 
            {
                m_type = INT;
            }
        }
    }*/
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
            {
                if (m_right->eval_int() == 0)
                {
                    return 0;
                }
                return m_left->eval_int() / m_right->eval_int();
            }
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
    if (m_kind == TRUE)
    {
        return 1;
    }
    if (m_kind == FALSE)
    {
        return 0;
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
        return eval_int();
    }
    if (m_kind == UNARY_OP)
    {
        if (m_op == NOT)
        {
            return !m_left->eval_double();
        }
        if (m_op == UNARY_MINUS)
        {
            double value = m_left->eval_double();
            return -value;
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
            //value = value * M_PI / 180;
            return asin(m_left->eval_double()) * 180 / M_PI;
        }
        if (m_op == ACOS)
        {
            return acos(m_left->eval_double()) * 180 / M_PI;
        }
        if (m_op == ATAN)
        {
            return atan(m_left->eval_double()) * 180 / M_PI;
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
            //if (m_left->)
            double value = m_left->eval_double();
            return abs(value);
        }
        if (m_op == RANDOM)
        {
            srand(rand() ^ time(NULL));
            if (m_type == DOUBLE)
            {
                int value = floor(m_left->eval_double());
                return rand() % value;
            }
            else
                return rand() % m_left->eval_int();
        }
    }
    if (m_kind == TRUE)
    {
        return eval_int();
    }
    if (m_kind == FALSE)
    {
        return eval_int();
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
    if (m_kind == UNARY_OP)
    {
        int value = m_left->eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
    }
    if (m_kind == BINARY_OP)
    {
        if (m_op == PLUS)
        {
            int a, b, c;
            if (m_left->m_var || m_right->m_var)
            {
                int left_var, right_var;
                if (m_left->m_var)
                {
                    left_var = m_left->m_var->get_var_type();
                    if (left_var == INT)
                    {
                        convert << m_left->m_var->get_int_value();
                    }
                    else if (left_var == DOUBLE)
                    {
                        convert << m_left->m_var->get_double_value();
                    }
                    else
                    {
                        convert << m_left->m_var->get_string_value();
                    }
                    if (m_right->m_var)
                    {
                        right_var = m_right->m_var->get_var_type();
                        if (right_var == INT)
                        {
                            convert << m_right->m_var->get_int_value();
                        }
                        else if (right_var == DOUBLE)
                        {
                            convert << m_right->m_var->get_double_value();
                        }
                        else
                        {
                            convert << m_right->m_var->get_string_value();
                        }
                    }
                    else
                    {
                        if (m_right->get_type() == INT)
                        {
                            convert << m_right->eval_int();
                        }
                        else if (m_right->get_type() == DOUBLE)
                        {
                            convert << m_right->eval_double();
                        }
                        else
                            convert << m_right->eval_string();
                    }
                }
                else
                {
                    left_var = m_left->get_type();
                    right_var = m_right->m_var->get_var_type();
                    if (left_var == INT)
                    {
                        int value = m_left->eval_int();
                        convert << value;
                    }
                    else if (m_left->get_type() == DOUBLE)
                    {
                        double value = m_left->eval_double();
                        convert << value;
                    }
                    else
                    {
                        string value = m_left->eval_string();
                        convert << value;
                    }
                    if (right_var == INT)
                    {
                        int value2 = m_right->m_var->get_int_value();
                        convert << value2;
                    }
                    else if (right_var == DOUBLE)
                    {
                        double value2 = m_right->m_var->get_double_value();
                        convert << value2;
                    }
                    else
                    {
                        string value2 = m_right->m_var->get_string_value();
                        convert << value2;
                    }
                }
            }
            else
            {
                a = m_left->get_type();
                b = m_right->get_type(); 
                c = a|b;
            
                if (c == INT) 
                {
                    int value = m_left->eval_int() + m_right->eval_int();
                    convert << value;
                }
                else if (c == DOUBLE)
                {
                    double value = m_left->eval_double() + m_right->eval_double();
                    convert << value;
                }
                else if (c == STRING)
                {
                    return m_left->eval_string() + m_right->eval_string();
                }
                else if (c == (INT|DOUBLE))
                {
                    double value;
                    if (m_left->get_type() == INT)
                    {
                        value = m_left->eval_int() + m_right->eval_double();
                    }
                    else
                    {
                        value = m_left->eval_double() + m_right->eval_int();
                    }
                    convert << value;
                }
                else if (c == (INT|STRING))
                {
                    int value;
                    string s;
                    if (m_left->get_type() == INT)
                    {
                        value = m_left->eval_int();
                        s = m_right->eval_string();
                    }
                    else
                    {
                        value = m_right->eval_int();
                        s = m_left->eval_string();
                    }
                    convert << s << value;
                }
                else if (c == (DOUBLE|STRING))
                {
                    double value;
                    string s;
                    if (m_left->get_type() == DOUBLE)
                    {
                        value = m_left->eval_double();
                        s = m_right->eval_string();
                    }
                    else
                    {
                        value = m_right->eval_double();
                        s = m_left->eval_string();
                    }  
                    convert << s << value; 
                }
            }
            str = convert.str();
            tmp = str;
            convert.clear();
            convert.str(string());
            return tmp; 
        }
    }
    /*if (m_op == PLUS)
    {
        if (m_type == INT)
        {   
            int value;
            value = m_left->eval_int() + m_right->eval_int();
            convert << value;
            str = convert.str();
            tmp = str;
            convert.clear();
            convert.str(string());
            return tmp; 
        }
        else if (m_type == DOUBLE)
        {
            double value;
            if (m_left->m_var || m_right->m_var)
            {
                if (m_left->m_var)
                {
                    if (m_right->m_var)
                    {
                        value = m_left->m_var->get_double_value() +
                                 m_right->m_var->get_double_value();
                    }
                }
                else 
                {
                    value = m_left->eval_double() + 
                            m_right->m_var->get_double_value();
                }
            }
            else if (m_left->get_type() == INT)
            {
                value = m_left->eval_int() + m_right->eval_double();
            }
            else if (m_right->get_type() == INT)
            {
                value = m_left->eval_double() + m_right->eval_int();
            }
            else
            {
                value = m_left->eval_double() + m_right->eval_double();
            }
            convert << value;
            str = convert.str();
            tmp = str;
            convert.clear();
            convert.str(string());
            return tmp; 
        }
        else 
        {
            if (m_left->m_var || m_right->m_var)
            {
                if (m_left->m_var)
                {
                    if (m_right->m_var)
                    {
                        return m_left->m_var->get_string_value() +
                               m_right->m_var->get_string_value();
                    }
                    else
                    {
                        return m_left->eval_string() +
                               m_right->eval_string(); 
                    }
                }
                else
                {
                    return m_left->eval_string() +
                           m_right->m_var->get_string_value();
                }
            }
            return m_left->eval_string() + m_right->eval_string();
        }
    }
    }*/
    if (m_kind == MATH_OP)
    {
        double value = m_left->eval_double();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
    }
    if (m_kind == LOGICAL_OP)
    {
        int value;
        if (m_op == NOT_EQUAL)
        {
            value = m_left->eval_string() != m_right->eval_string();
        }
        if (m_op == EQUAL)
        {
            value = m_left->eval_string() == m_right->eval_string();
        }
        if (m_op == GREATER_THAN)
        {
            value = m_left->eval_string() > m_right->eval_string();
        }
        if (m_op == GREATER_THAN_EQUAL)
        {
            value = m_left->eval_string() >= m_right->eval_string();
        }
        if (m_op == LESS_THAN)
        {
            value = m_left->eval_string() < m_right->eval_string();
        }
        if (m_op == LESS_THAN_EQUAL)
        {
            value = m_left->eval_int() <= m_right->eval_int();
        }
        if (m_op == AND)
        {
            value = m_left->eval_int() && m_right->eval_int();
        }
        if (m_op == OR)
        {
            value = m_left->eval_int() || m_right->eval_int();
        }
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;  
    }
    if (m_kind == TRUE)
    {
        int value = eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
    }
    if (m_kind == FALSE)
    {
        int value = eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
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
