#include "symbol_table.h"

/* static */ Symbol_table *Symbol-table::m_instance = 0;

/* static */ Symbol_table * Symbol_table::instance()
{
    if (m_instance == 0)
	m_instance = new Symbol_table();
    return m_instance;
}
