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
bool Symbol_table::get_type(string var_name, Gpl_type type)
{
    /*if (sym_table.find(var_name) == sym_table.end())
    {
        string str = sym->getId();
	sym_table[str] = sym;
	return true;
    }
    else*/
      return false;
}
void Symbol_table::get(string name, int size)
{
    if (sym_table.find(name) == sym_table.end())
    {
    }
}
void Symbol_table::get(string name, string window_title)
{
    if (sym_table.find(name) == sym_table.end())
    {
    }
}
void Symbol_table::set(string name, int size)
{
    if (sym_table.find(name) == sym_table.end())
    {
    }
}
