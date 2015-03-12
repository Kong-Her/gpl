#include "variable.h"

Variable::Variable(Symbol *s)
{
}
Variable::Variable(string var_name, Gpl_type gpl_type, Symbol *sym)
{
    m_var_name = var_name;
    m_gpl_type = gpl_type;
    m_sym = sym;
}
Variable::Variable(string var_name, Gpl_type gpl_type, Symbol *sym,  Expression *index_expr)
{
    m_var_name = var_name;
    m_gpl_type = gpl_type;
    m_sym = sym;
    m_index_expr = index_expr;
}
int Variable::get_int_value()
{
    return m_sym->getInt();
}
double Variable::get_double_value()
{
    return m_sym->getDouble();
}
string Variable::get_string_value()
{
    return m_sym->getString();
}
Gpl_type Variable::get_var_type()
{
    return m_sym->getType();
}
