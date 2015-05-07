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
    int expr_type, var_type;
    Symbol *cur_sym = m_var->get_symbol();
    
    expr_type = m_expr->get_type();    
    var_type = cur_sym->get_type();

    if (var_type == STRING)
    {
        cur_sym->set_new_value(m_expr->eval_string());
        symbol_table->update_symbol(cur_sym);
    }
    else if (var_type == DOUBLE && expr_type != STRING)
    {
        cur_sym->set_new_value(m_expr->eval_double());
        symbol_table->update_symbol(cur_sym);
    }
    else if (var_type == INT && expr_type == INT)
    {
        cur_sym->set_new_value(m_expr->eval_int());
        symbol_table->update_symbol(cur_sym);
    }
        
}
