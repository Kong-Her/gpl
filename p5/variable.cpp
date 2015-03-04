#include "variable.h"

Variable::Variable(string var_name, Gpl_type gpl_type)
{
    m_var_name = var_name;
    m_gpl_type = gpl_type;
}
Variable::Variable(string var_name, Gpl_type gpl_type,  Expression *index_expr)
{
    m_var_name = var_name;
    m_gpl_type = gpl_type;
    m_index_expr = index_expr;
}
void Variable::set_value()
{
}
int Variable::get_value()
{
    Symbol_table *symbol_table = Symbol_table::instance();
    Symbol *sym = symbol_table->lookup(m_var_name);
    return sym->getInt();
}
