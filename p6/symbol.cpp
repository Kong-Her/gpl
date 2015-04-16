#include "symbol.h"
#include "animation_block.h"

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
Symbol::Symbol(Gpl_type gpl_type, string var_name, Animation_block *animation)
{
    m_var_name = var_name;
    m_gpl_type = ANIMATION_BLOCK;
    m_animation_block = animation;
}
Animation_block *Symbol::get_animation_block_value()
{
    return m_animation_block;
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
Object_type Symbol::get_object_type()
{
    return m_object_type;
}
bool Symbol::is_int()
{
    if (m_gpl_type == INT)
    {
        return true;
    }
    else
        return false;
}
bool Symbol::is_double()
{
    if (m_gpl_type == DOUBLE)
    {
        return true;
    }
    else
        return false;
}
bool Symbol::is_string()
{
    if (m_gpl_type == STRING)
    {
        return true;
    }
    else
        return false;
}
