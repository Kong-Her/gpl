#include "symbol_table.h"

/* static */ Symbol_table *Symbol_table::m_instance = NULL;

/* static */ Symbol_table * Symbol_table::instance()
{
    if (m_instance == NULL)
	m_instance = new Symbol_table();
    return m_instance;
}
bool Symbol_table::insert(Symbol *sym)
{
    if (myMap.find(sym->getId()) == myMap.end())
    {
	myMap[sym->getId()] = sym;
	return true;
    }
    else
    {
	return false;
    }
}
void Symbol_table::print(ostream &os)
{
    //vector<map<>
    //for (map<string, 
    //os << 
}
