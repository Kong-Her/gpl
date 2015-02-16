#ifndef SYMBOL_H
#define SYMBOL_H

#include "gpl_type.h"
#include <string>
using namespace std;

class Symbol
{
    public:
      Symbol();
      Symbol(string var_name, Gpl_type gpl_type, int val);
      Symbol(string var_name, Gpl_type gpl_type, double val);
      Symbol(string var_name, Gpl_type gpl_type, string val);
      int getInt();
      double getDouble();
      string getId();
      string getString();

    private:
      string m_var_name;
      Gpl_type m_gpl_type;
      int m_iVal;
      double m_dVal;
      string m_strVal;


};
#endif
