#include "symbol.h"

Symbol::Symbol(string s, int i)
{
    m_string_val = s;
    m_gpl_type = INT;
}
Symbol::Symbol(string var_name)
{
    m_var_name = var_name;
}
Symbol::Symbol(Gpl_type gpl_type, string var_name, int val)
{
    m_var_name = var_name;
    m_gpl_type = gpl_type;
    m_int_val = val;
}
Symbol::Symbol(Gpl_type gpl_type, string var_name, double val)
{
    m_var_name = var_name;
    m_gpl_type = gpl_type;
    m_double_val = val;
}
Symbol::Symbol(Gpl_type gpl_type, string var_name, string val)
{
    m_var_name = var_name;
    m_gpl_type = gpl_type;
    m_string_val = val;
}
Symbol::Symbol(Gpl_type gpl_type, string var_name, Game_object *game_obj)
{
    m_var_name = var_name;
    m_gpl_type = GAME_OBJECT;
    m_game_obj = game_obj;
}
Game_object *Symbol::get_game_object_value()
{
    return m_game_obj;
}
int Symbol::getInt()
{
    return m_int_val; 
}
double Symbol::getDouble()
{
    return m_double_val;
}
string Symbol::getId()
{
    return m_var_name;
}
string Symbol::getString()
{
    return m_string_val;
}
Gpl_type Symbol::get_type()
{
    return m_gpl_type;
}
