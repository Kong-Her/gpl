#include "assignment_stmt.h"

Assignment_stmt::Assignment_stmt(Variable *var, Expression *expr, string op_type)
{
    m_var = var;
    m_expr = expr;
    m_op_type = op_type;
}
void Assignment_stmt::execute()
{
    Symbol_table *symbol_table = Symbol_table::instance();
    int expr_type, type;
    Symbol *cur_sym = m_var->get_symbol();
    
    expr_type = m_expr->get_type();    
    type = cur_sym->get_type();

    if (type == STRING)
    {
        string str;

        if (m_op_type == "=")
        {
            cur_sym->set_new_value(m_expr->eval_string());
            symbol_table->update_symbol(cur_sym);
        }
        else if (m_op_type == "+=")
        {
            str = cur_sym->getString() + m_expr->eval_string();
            cur_sym->set_new_value(str);
            symbol_table->update_symbol(cur_sym);
        }
    }
    else if (type == DOUBLE && expr_type != STRING)
    {
        if (m_op_type == "=")
        {
            cur_sym->set_new_value(m_expr->eval_double());
            symbol_table->update_symbol(cur_sym);
        }
        else if (m_op_type == "+=")
        {
            double total = cur_sym->getDouble() + m_expr->eval_double();
            cur_sym->set_new_value(total);
            symbol_table->update_symbol(cur_sym);
        }
        else if (m_op_type == "-=")
        {
            double total = cur_sym->getDouble() - m_expr->eval_double();
            cur_sym->set_new_value(total);
            symbol_table->update_symbol(cur_sym);
        }
    }
    else if (type == INT && expr_type == INT)
    {
        if (m_op_type == "=")
        {
            cur_sym->set_new_value(m_expr->eval_int());
            symbol_table->update_symbol(cur_sym);
        }
        else if (m_op_type == "+=")
        {
            int total = cur_sym->getInt() + m_expr->eval_int();
            cur_sym->set_new_value(total);
            symbol_table->update_symbol(cur_sym);
        }
        else if (m_op_type == "-=")
        {
            int total = cur_sym->getInt() - m_expr->eval_int();
            cur_sym->set_new_value(total);
            symbol_table->update_symbol(cur_sym);
        }

    }
    else if (type == GAME_OBJECT)
    {
        //Status status;
        string name = cur_sym->getId();
        if (expr_type == INT)
        {
            if (m_op_type == "=")
            {
                int value = m_expr->eval_int();
                cur_sym->get_game_object_value()->set_member_variable(name, value);
            }
            else if (m_op_type == "+=")
            {
                int total, value; 
                cur_sym->get_game_object_value()->get_member_variable(name, value);
                total = m_expr->eval_int() + value;
                cur_sym->get_game_object_value()->set_member_variable(name, total);
            }
            else if (m_op_type == "-=")
            {
                int total, value; 
                cur_sym->get_game_object_value()->get_member_variable(name, value);
                total = m_expr->eval_int() - value;
                cur_sym->get_game_object_value()->set_member_variable(name, total);
            }

            //if (status == OK)
            //{
                //cur_sym->set_new_value(value);
                //symbol_table->update_symbol(cur_sym);
            //}
        }
        else if (expr_type == DOUBLE)
        {
            double value = m_expr->eval_double();
            /*status =*/ cur_sym->get_game_object_value()->set_member_variable(name, value);
            //if (status == OK)
            //{   
                //cur_sym->set_new_value(value);
                //symbol_table->update_symbol(cur_sym);
            //}
        }
        else if (expr_type == STRING)
        {
            string value = m_expr->eval_string();
            /*status =*/ cur_sym->get_game_object_value()->set_member_variable(name, value);
            //if (status == OK)
            //{
                //cur_sym->set_new_value(value);
                //symbol_table->update_symbol(cur_sym);
            //}
        }

   } 
   else if (type == ANIMATION_BLOCK)
   {
   }
}
