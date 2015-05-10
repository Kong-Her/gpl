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
    Gpl_type type;
    Symbol *cur_sym = m_var->get_symbol();
    
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
    else if (type == DOUBLE)
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
    else if (type == INT)
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
        Symbol *sym = m_var->get_symbol();
        Game_object *game_obj = sym->get_game_object_value();
        
        if (m_op_type == "=")
        {
            if (m_expr->get_type() == INT)
            {
                int val = m_expr->eval_int();
                game_obj->set_member_variable(m_var->get_var_name(), val);
                cur_sym->set_new_value(game_obj);
                symbol_table->update_symbol(cur_sym);
            }
            else if (m_expr->get_type() == DOUBLE)
            {
                double val = m_expr->eval_double();
                game_obj->set_member_variable(m_var->get_var_name(), val);
                cur_sym->set_new_value(game_obj);
                symbol_table->update_symbol(cur_sym);
            }
            else if (m_expr->get_type() == STRING)
            {
                string val = m_expr->eval_string();
                game_obj->set_member_variable(m_var->get_var_name(), val);
                cur_sym->set_new_value(game_obj);
                symbol_table->update_symbol(cur_sym);
            }
        }
        else if (m_op_type == "+=")
        {
            if (m_expr->get_type() == INT)
            {
                int val, member_val; 
                game_obj->get_member_variable(m_var->get_var_name(), member_val);
                val = member_val - m_expr->eval_int();
                game_obj->set_member_variable(m_var->get_var_name(), val);
                cur_sym->set_new_value(game_obj);
                symbol_table->update_symbol(cur_sym);
            }
            else if (m_expr->get_type() == DOUBLE)
            {
                double val, member_val;
                game_obj->get_member_variable(m_var->get_var_name(), member_val);
                val = member_val - m_expr->eval_double();
                game_obj->set_member_variable(m_var->get_var_name(), val);
                cur_sym->set_new_value(game_obj);
                symbol_table->update_symbol(cur_sym);
            }
        }
        else if (m_op_type == "-=")
        {
            if (m_expr->get_type() == INT)
            {
                int val, member_val; 
                game_obj->get_member_variable(m_var->get_var_name(), member_val);
                val = member_val - m_expr->eval_int();
                game_obj->set_member_variable(m_var->get_var_name(), val);
                cur_sym->set_new_value(game_obj);
                symbol_table->update_symbol(cur_sym);
            }
            else if (m_expr->get_type() == DOUBLE)
            {
                double val, member_val;
                game_obj->get_member_variable(m_var->get_var_name(), member_val);
                val = member_val - m_expr->eval_double();
                game_obj->set_member_variable(m_var->get_var_name(), val);
                cur_sym->set_new_value(game_obj);
                symbol_table->update_symbol(cur_sym);
            }
        }

    } 
    else if (type == ANIMATION_BLOCK)
    {
        if (m_op_type == "=")
        {
        }
        else if (m_op_type == "+=")
        {
        }
        else if (m_op_type == "-=")
        {
        }
    }
}
