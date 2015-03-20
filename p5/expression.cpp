#include "expression.h"
#include "variable.h"

Expression::Expression(int dummie)
{
    m_dummie = dummie;
}
/*********************************************************************************/
Expression::Expression(int val, Kind kind)
{
    m_int_val = val;
    m_kind = kind;
    m_type = INT;
}
/*********************************************************************************/
Expression::Expression(double val, Kind kind)
{
    m_double_val = val;
    m_kind = kind;
    m_type = DOUBLE;
}
/*********************************************************************************/
Expression::Expression(string val, Kind kind)
{
    m_string_val = val;
    m_kind = kind;
    m_type = STRING;
}
/*********************************************************************************/
Expression::Expression(Variable *var, Kind kind)
{
    m_var = var;
    m_kind = kind;

    if (var)
    {
        int var_type = var->get_var_type();

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
        }
    }

}
/*********************************************************************************/
Expression::Expression(Operator_type op, Kind kind, Expression *left, Expression *right)
{
    m_op = op;
    m_kind = kind;
    m_left = left;
    m_right = right; 

    if (kind == LOGICAL_OP)
    {
        if (op == AND || op == OR || op == EQUAL || 
            op == NOT_EQUAL || op == GREATER_THAN || op == LESS_THAN || 
            op == LESS_THAN_EQUAL || op == GREATER_THAN_EQUAL)
        {
            m_type = INT;
        }
    }
    else if (kind == BINARY_OP)
    {
        int left_type = 0, right_type = 0, both;
        if (op == MOD)
        {
            m_type = INT;
        }
        if (op == PLUS)
        {
            /*if (left->m_var || right->m_var)
            {
                if (left->m_var)
                {
                    left_type = left->m_var->get_var_type();
                    
                    if(right->m_var)
                    {
                        //both left and right are variables
                        right_type = right->m_var->get_var_type();
                        both = (left_type|right_type);
                        
                        if (both == INT)
                        {
                            m_type = INT;
                        }
                        else if (both == DOUBLE || both == (INT|DOUBLE))
                        {
                            m_type = DOUBLE;
                        }
                        else
                        {
                            m_type = STRING;
                        }
                    }
                    else
                    {
                        //left is a variable, right is a constant
                        right_type = right->get_type();
                        both = (left_type|right_type);
                        if (both == INT)
                        {
                            m_type = INT;
                        }
                        else if (both == DOUBLE || both == (INT|DOUBLE))
                        {
                            m_type = DOUBLE;
                        }
                        else
                        {
                            m_type = STRING;
                        }
                    }
                }
                else
                {
                    //left is a constant, right is a variable
                    left_type = left->get_type();
                    right_type = right->m_var->get_var_type();
                    both = (left_type|right_type);

                    if (both == INT)
                    {
                        m_type = INT;
                    }
                    else if (both == DOUBLE || both == (INT|DOUBLE))
                    {
                        m_type = DOUBLE;
                    }
                    else 
                    {
                        m_type = STRING;
                    }
                }
            }
            else*/ if (left->get_type() == STRING || right->get_type() == STRING)
            {
                m_type = STRING;
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
            if (left->get_type() == INT && right->get_type() == INT)
            {
                m_type = INT;
            }
            else
            {
                m_type = DOUBLE;
            }
        }
    }
}
/*********************************************************************************/
Expression::Expression(Operator_type op, Kind kind, Expression *left)
{
    m_op = op;
    m_kind = kind;
    m_left = left;

        int left_type = left->get_type();
        if (kind == MATH_OP)
        {
            if (op == RANDOM || op == FLOOR)
            {
                m_type = INT;
            }
            else if (op == ABS)
            {
                if (left_type == INT)
                {
                    m_type = INT;
                }
                else
                    m_type = DOUBLE;
            }
            else
                m_type = DOUBLE;
        }
        else if (kind == UNARY_OP)
        {
            if (op == NOT)
            {
                m_type = INT;
            }
            if (op == MINUS)
            {
                if (left_type == INT)
                {
                    m_type = INT;
                }
                else 
                {
                    m_type = DOUBLE;
                }
            }
        }
}
/*********************************************************************************/
int Expression::eval_int()
{
    if (m_kind == BINARY_OP)
    {
        if (m_op == PLUS)
        {
            if (m_type == INT)
            {
                return m_left->eval_int() + m_right->eval_int();
            }
            else
                return eval_double();
        }
        if (m_op == MINUS)
        {
            if (m_type == INT)
            {
                return m_left->eval_int() - m_right->eval_int();
            }
            else
                return eval_double();
        }
        if (m_op == MULTIPLY)
        {
            if (m_type == INT)
            {
                return m_left->eval_int() * m_right->eval_int();
            }
            else 
                return eval_double();
        }
        if (m_op == DIVIDE)
        {
            if (m_type == INT)
            {
                return m_left->eval_int() / m_right->eval_int();
            }
            else 
                return eval_double();
        }
        if (m_op == MOD)
        {
            if (m_type == INT)
            {
                return m_left->eval_int() % m_right->eval_int();
            }
            else 
                return eval_double();
        }
    }
    else if (m_kind == LOGICAL_OP)
    {
        int a, b, c;
        a = m_left->get_type();
        b = m_right->get_type();
        c = (a|b);

        if (m_op == LESS_THAN)
        {
            if (c == INT)
            {
                return m_left->eval_int() < m_right->eval_int();
            }
            else if (c == DOUBLE || c == (INT|DOUBLE))
            {
                return m_left->eval_double() < m_right->eval_double();
            }
            else 
            {
                string left_str, right_str;

                left_str = m_left->eval_string();
                right_str = m_right->eval_string();

                return left_str < right_str;
            }
        }
        if (m_op == GREATER_THAN)
        {
            if (c == INT)
            {
                return m_left->eval_int() > m_right->eval_int();
            }
            else if (c == DOUBLE || c == (INT|DOUBLE))
            {
                return m_left->eval_double() > m_right->eval_double();
            }
            else
            {
                string left_str, right_str;

                left_str = m_left->eval_string();
                right_str = m_right->eval_string();

                return left_str > right_str;
            }
        }
        if (m_op == LESS_THAN_EQUAL)
        {
            if (c == INT)
            {
                return m_left->eval_int() <= m_right->eval_int();
            }
            else if (c == DOUBLE || c == (INT|DOUBLE))
            {
                return m_left->eval_double() <= m_right->eval_double();
            }
            else
            {
                string left_str, right_str;

                left_str = m_left->eval_string();
                right_str = m_right->eval_string();

                return left_str <= right_str;
            }
        }
        if (m_op == GREATER_THAN_EQUAL)
        {
            if (c == INT)
            {
                return m_left->eval_int() >= m_right->eval_int();
            }
            else if (c == DOUBLE || c == (INT|DOUBLE))
            {
                return m_left->eval_double() >= m_right->eval_double();
            }
            else
            {
                string left_str, right_str;

                left_str = m_left->eval_string();
                right_str = m_right->eval_string();

                return left_str >= right_str;
            }
        }
        if (m_op == EQUAL)
        {
            if (c == INT)
            {
                return m_left->eval_int() == m_right->eval_int();
            }
            else if (c == DOUBLE || c == (INT|DOUBLE))
            {
                return m_left->eval_double() == m_right->eval_double();
            }
            else
            {
                string left_str, right_str;

                left_str = m_left->eval_string();
                right_str = m_right->eval_string();

                return left_str == right_str;
            }
        }
        if (m_op == NOT_EQUAL)
        {
            if (c == INT)
            {
                return m_left->eval_int() != m_right->eval_int();
            }
            else if (c == DOUBLE || c == (INT|DOUBLE))
            {
                return m_left->eval_double() != m_right->eval_double();
            }
            else
            {
                string left_str, right_str;

                left_str = m_left->eval_string();
                right_str = m_right->eval_string();

                return left_str != right_str;
            }
        }
        if (m_op == AND)
        {
            if (c == INT)
            {
                return m_left->eval_double() && m_right->eval_double();
            }
            else 
            {
                return m_left->eval_double() && m_right->eval_double();
            }
        }
        if (m_op == OR)
        {
            if (c == INT)
            {
                return m_left->eval_int() || m_right->eval_int();
            }
            else 
            {
                return m_left->eval_double() || m_right->eval_double();
            }
        }
    }
    else if (m_kind == UNARY_OP)
    {
        if (m_op == MINUS)
        {
            if (m_type == INT)
            {
                int val = m_left->eval_int();
                return -val;
            }
            else
            {
                double val = m_left->eval_double();
                return -val;
            }
        }
        if (m_op == NOT)
        {
            return !(m_left->eval_double());
        }
    }
    else if (m_kind == TRUE)
    {
        return 1;
    }
    else if (m_kind == FALSE)
    {
        return 0;
    }
    else if (m_kind == MATH_OP)
    {
        if (m_op == RANDOM)
        {
            return rand() % m_left->eval_int();
        }
        else if (m_op == ABS)
        {
            return abs(m_left->eval_double());
        }
        else if (m_op == FLOOR)
        {
            return floor(m_left->eval_double());
        }
        else
            return m_left->eval_double();
    }
    else if (m_kind == VARIABLE) 
    {
        return m_var->get_int_value(); 
    }
    else if (m_kind == INT_CONST)
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
    else if (m_kind == BINARY_OP)
    {
        if (m_op == PLUS)
        {
            if (m_type == INT)
            {
                return m_left->eval_int() + m_right->eval_int();
            }
            else if (m_type == DOUBLE)
            {
                return m_left->eval_double() + m_right->eval_double();
            }
        }
        if (m_op == MINUS)
        {
            if (m_type == INT)
            {
                return m_left->eval_int() - m_right->eval_int();
            }
            else if (m_type == DOUBLE)
            {
                return m_left->eval_double() - m_right->eval_double();
            }
        }
        if (m_op == MULTIPLY)
        {
            if (m_type == INT)
            {
                return m_left->eval_int() * m_right->eval_int();
            }
            else if (m_type == DOUBLE)
            {
                return m_left->eval_double() * m_right->eval_double();
            }   
        }
        if (m_op == DIVIDE)
        {
            if (m_type == INT)
            {
                return m_left->eval_int() / m_right->eval_int();
            }
            else if (m_type == DOUBLE)
            {
                return m_left->eval_double() / m_right->eval_double();
            }   
        }
    }
    else if (m_kind == LOGICAL_OP)
    {
        return eval_int();
    }
    else if (m_kind == UNARY_OP)
    {
        if (m_op == NOT)
        {
            return !(m_left->eval_double());
        }
        if (m_op == MINUS)
        {
            double val = m_left->eval_double();
            return -val;
        }
    }
    else if (m_kind == MATH_OP)
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
        if (m_op == RANDOM)
        {
            int value = floor(m_left->eval_double());
            return rand() % value;
        }
    }
    else if (m_kind == TRUE)
    {
        return eval_int();
    }
    else if (m_kind == FALSE)
    {
        return eval_int();
    }
    else if (m_kind == VARIABLE)
    {
        return m_var->get_double_value();
    }
    else if (m_kind == DOUBLE_CONST)
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
        int value = eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
    }
    else if (m_type == DOUBLE)
    {
        double value = eval_double();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
    }
    else if (m_kind == UNARY_OP)
    {
        int value;
        value = eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
    }
    else if (m_kind == BINARY_OP)
    {
        if (m_op == PLUS)
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
                value = m_left->eval_double() + m_right->eval_double();
                convert << value;
                str = convert.str();
                tmp = str;
                convert.clear();
                convert.str(string());
                return tmp;
            }
            else  
            {
                // string str1, str2;
                // str1 = m_left->eval_string();
                // str2 = m_right->eval_string();
                // convert << str1 << str2;
                // str = convert.str();
                // tmp = str;
                // return tmp;
                return m_left->eval_string() + m_right->eval_string();
            }
        }
    }
    else if (m_kind == MATH_OP)
    {
        if (m_type == INT)
        {
            int value = eval_int();
            convert << value;
        }
        else
        {
            double value = eval_double();
            convert << value;
        }
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
    }
    else if (m_kind == LOGICAL_OP)
    {
        int value = eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;  
    }
    else if (m_kind == STRING_CONST)
    {
        return m_string_val;
    }
    else if (m_kind == VARIABLE)
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
Kind Expression::get_kind()
{
    return m_kind;
}