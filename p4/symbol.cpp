#include "symbol.h"

Symbol::Symbol()
{
}
Symbol::Symbol(string var_name, Gpl_type gpl_type, int val)
{
    m_var_name = var_name;
    m_gpl_type = gpl_type;
    m_iVal = val;
}
Symbol::Symbol(string var_name, Gpl_type gpl_type, double val)
{
    m_var_name = var_name;
    m_gpl_type = gpl_type;
    m_dVal = val;
}
Symbol::Symbol(string var_name, Gpl_type gpl_type, string val)
{
    m_var_name = var_name;
    m_gpl_type = gpl_type;
    m_strVal = val;
}
int Symbol::getInt()
{
    return m_iVal; 
}
double Symbol::getDouble()
{
    return m_dVal;
}
string Symbol::getId()
{
    return m_var_name;
}
string Symbol::getString()
{
    return m_strVal;
}
