#include "symbol.h"

Symbol::Symbol()
{
}
Symbol::Symbol(string s, int i)
{
    m_strVal = s;
    m_iVal = i;
}
Symbol::Symbol(string var_name)
{
    m_var_name = var_name;
}
Symbol::Symbol(Gpl_type gpl_type, string var_name, int val)
{
    m_var_name = var_name;
    m_gpl_type = gpl_type;
    m_iVal = val;
}
Symbol::Symbol(Gpl_type gpl_type, string var_name, double val)
{
    m_var_name = var_name;
    m_gpl_type = gpl_type;
    m_dVal = val;
}
Symbol::Symbol(Gpl_type gpl_type, string var_name, string val)
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
Gpl_type Symbol::getType()
{
    return m_gpl_type;
}
