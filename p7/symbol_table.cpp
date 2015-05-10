#include "symbol_table.h"

/* static */ Symbol_table *Symbol_table::m_instance = NULL;

/* static */ Symbol_table * Symbol_table::instance()
{
    if (m_instance == NULL)
	m_instance = new Symbol_table();
    return m_instance;
}
bool Symbol_table::insert(Symbol *sym, string actual_name)
{
    //check to see if id is used yet
    if (sym_table.find(actual_name) == sym_table.end() && sym)
    {
        string str = sym->getId();
	sym_table[str] = sym;
	return true;
    }
    else
      return false;
}
void Symbol_table::print(ostream &os)
{
    for (map<string, Symbol*>::iterator it = sym_table.begin();
         it != sym_table.end(); it++)
    {
	if (it->second->get_type() == INT)
	{
	    os << "int " << it->second->getId();
	    os << " " << it->second->getInt() << endl; 
	}	
	else if (it->second->get_type() == DOUBLE)
	{
	    os << "double " << it->second->getId();
            os << " " << it->second->getDouble() << endl;
	}
	else if (it->second->get_type() == STRING)
	{
	    os << "string " << it->second->getId();
      	    os << " \"" << it->second->getString() << "\"" << endl;
	}
	else if (it->second->get_type() == GAME_OBJECT)
        {
            os << "game_object " << it->second->getId();
            os << endl;
            indent++;
            os << it->second->get_game_object_value();
            os << endl;
            indent--;
        }
        else if (it->second->get_type() == ANIMATION_BLOCK)
        {
            os << "animation_block " << it->second->getId();
            indent++;
            os << endl;
            indent--;
        }

    }

}
Symbol *Symbol_table::lookup(string name)
{
    map<string, Symbol*>::iterator it;
    for (it = sym_table.begin(); it != sym_table.end(); it++)
    {
        if (it->first == name)
        {
            return it->second;
        }
    }
    return NULL;
}
bool Symbol_table::get(string name, int &value)
{
    Symbol *cur = lookup(name);
    if (!cur || !cur->is_int())
        return false;

    value = cur->getInt();
    return true;
}
bool Symbol_table::get(string name, double &value)
{
    Symbol *cur = lookup(name);
    if (!cur || !cur->is_double())
        return false;

    value = cur->getDouble();
    return true;
}
bool Symbol_table::get(string name, string &value)
{
    Symbol *cur = lookup(name);
    if (!cur || !cur->is_string())
        return false;

    value = cur->getString();
    return true;
}
bool Symbol_table::get_type(string name, Gpl_type &type)
{
    Symbol *cur = lookup(name);
    if (!cur) 
        return false;

    type = cur->get_type();
    return true;
}
bool Symbol_table::set(string name, int value) // used for mouse_x, mouse_y
{
    return false;
}
void Symbol_table::update_symbol(Symbol *sym)
{
    string var_name = sym->getId();
    sym_table[var_name] = NULL;
    sym_table[var_name] = sym;
}
