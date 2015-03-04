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
int Variable::get_int_value()
{
    Symbol_table *symbol_table = Symbol_table::instance();
    Symbol *sym = symbol_table->lookup(m_var_name);
    //error if not found
    /*if (sym == NULL)
    {
        return 0;
    }*/
    return sym->getInt();
}
double Variable::get_double_value()
{
    Symbol_table *symbol_table = Symbol_table::instance();
    Symbol *sym = symbol_table->lookup(m_var_name);
    //error if not found
    if (sym == NULL)
    {
        return 0;
    }
    return sym->getDouble();
}
string Variable::get_string_value()
{
    Symbol_table *symbol_table = Symbol_table::instance();
    Symbol *sym = symbol_table->lookup(m_var_name);
    //error if not found
    if (sym == NULL)
    {
        return "";
    }
    return sym->getString();
}
