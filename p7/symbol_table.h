#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "symbol.h"
#include "parser.h"
#include "indent.h"
#include <map>

class Symbol_table
{
    public:
	static Symbol_table *instance();
        bool insert(Symbol*, string actual_name);
	void print(ostream &os);
        Symbol *lookup(string name);
        bool get(string, int &);
        bool get(string, double &);
        bool get(string, string &);
        bool get_type(string, Gpl_type &);
        bool set(string, int);
        void set_new_value();

    private:
        static Symbol_table *m_instance;
	Symbol_table() {};
	// disable default copy constructor and default assignment
	// done as a precaution, they should never be called
	Symbol_table(const Symbol_table &);
	const Symbol_table &operator=(const Symbol_table &);
	map<string, Symbol*> sym_table;

};

#endif
