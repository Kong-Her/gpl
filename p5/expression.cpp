#include "expression.h"
#include "variable.h"

Expression::Expression(int dummie)
{
    m_dummie = dummie;
}
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

    if(var)
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

    if (left && right)
    {
        int left_type = 0, right_type = 0, both;
        
        if (op == AND || op == OR || op == EQUAL || 
            op == NOT_EQUAL || op == GREATER_THAN || op == LESS_THAN || 
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
                    left_type = left->m_var->get_var_type();
                    
                    if(right->m_var)
                    {
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
            else if (left->get_type() == STRING || right->get_type() == STRING)
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
            /*left_type = left->get_type();
            right_type = right->get_type();
            both = (left_type|right_type);*/

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

    if (left)
    {
        if (kind == MATH_OP)
        {
            if (op == RANDOM || op == FLOOR)
            {
                m_type = INT;
            }
            else 
                m_type = DOUBLE;
        }
        else if (op == NOT)
        {
            m_type = INT;
        }
        else if (op == UNARY_MINUS)
        {
            int left_type = left->get_type();
            if (left_type == INT)
            {
                m_type = INT;
            }
            else if (left_type == DOUBLE)
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
    if (m_kind == LOGICAL_OP)
    {
        if (m_op == LESS_THAN)
        {
            if (m_type == INT)
            {
                return m_left->eval_int() < m_right->eval_int();
            }
            else if (m_type == DOUBLE)
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
            if (m_type == INT)
            {
                return m_left->eval_int() > m_right->eval_int();
            }
            else if (m_type == DOUBLE)
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
            if (m_type == INT)
            {
                return m_left->eval_int() <= m_right->eval_int();
            }
            else if (m_type == DOUBLE)
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
            if (m_type == INT)
            {
                return m_left->eval_int() >= m_right->eval_int();
            }
            else if (m_type == DOUBLE)
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
            if (m_type == INT)
            {
                return m_left->eval_int() == m_right->eval_int();
            }
            else if (m_type == DOUBLE)
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
            if (m_type == INT)
            {
                return m_left->eval_int() != m_right->eval_int();
            }
            else if (m_type == DOUBLE)
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
            //if (m_type == INT)
            //{
                return m_left->eval_double() && m_right->eval_double();
            //}
            /*else if (m_type == DOUBLE)
            {
                return m_left->eval_double() && m_right->eval_double();
            }*/
        }
        if (m_op == OR)
        {
            if (m_type == INT)
            {
                return m_left->eval_int() || m_right->eval_int();
            }
            else if (m_type == DOUBLE)
            {
                return m_left->eval_double() || m_right->eval_double();
            }
        }
    }
    if (m_kind == UNARY_OP)
    {
        if (m_op == MINUS)
        {
            /*if (m_type == INT)
            {*/
                int val = m_left->eval_int();
                return -val;
            //}
            /*else
            {
                double val = m_left->eval_double();
                return -val;
            }*/
        }
        if (m_op == NOT)
        {
            return !(m_left->eval_double());
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
        if (m_op == RANDOM)
        {
            return rand() % m_left->eval_int();
        }
        else if (m_op == ABS)
        {
            return abs(m_left->eval_double());
        }
        else
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
    if (m_kind == LOGICAL_OP)
    {
        return eval_int();
    }
    if (m_kind == UNARY_OP)
    {
        //maybe I just need to call eval_int, it handle it?
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
        //int value = m_left->eval_int();
        int value = eval_int();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
    }
    if (m_type == DOUBLE)
    {
        //double value = m_left->eval_double();
        double value = eval_double();
        convert << value;
        str = convert.str();
        tmp = str;
        convert.clear();
        convert.str(string());
        return tmp;
    }
    if (m_kind == UNARY_OP)
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
    if (m_kind == BINARY_OP)
    {
        //if (m_op == PLUS)
        //{
            /*if (m_type == INT)
            {
                int value;
                value = m_left->eval_int() + m_right->eval_int();
                convert << value;
            }
            else if (m_type == DOUBLE)
            {
                double value;
                value = m_left->eval_double() + m_right->eval_double();
                convert << value;
            }
            else  
            {*/
                return m_left->eval_string() + m_right->eval_string();
            //}
        //}
    }
    if (m_kind == MATH_OP)
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
    if (m_kind == LOGICAL_OP)
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
