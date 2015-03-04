#include "symbol_table.h"

/* static */ Symbol_table *Symbol_table::m_instance = NULL;

/* static */ Symbol_table * Symbol_table::instance()
{
    if (m_instance == NULL)
	m_instance = new Symbol_table();
    return m_instance;
}
bool Symbol_table::insert(Symbol *sym, string actual_name, bool yes)
{
    //check to see if id is used yet
    if (sym_table.find(actual_name) == sym_table.end() && !yes) 
    {
	sym_table[actual_name] = sym;
	return true;
    }
    if (yes)
    {
	sym_table[sym->getId()] = sym;
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
	if (it->second->getType() == INT)
	{
	    os << "int " << it->second->getId();
	    os << " " << it->second->getInt() << endl; 
	}	
	else if (it->second->getType() == DOUBLE)
	{
	    os << "double " << it->second->getId();
            os << " " << it->second->getDouble() << endl;
	}
	else if (it->second->getType() == STRING)
	{
	    os << "string " << it->second->getId();
      	    os << " \"" << it->second->getString() << "\"" << endl;
	}
    }
}
Symbol *Symbol_table::lookup(string name)
{
    Symbol *tmp = NULL;

    map<string, Symbol*>::iterator it;
    for (it = sym_table.begin(); it != sym_table.end(); it++)
    {
        if (it->first == name)
        {
            tmp = it->second;
        }
    }
    if (!tmp)
    {
        return NULL;
    }
    else 
        return tmp;
}
