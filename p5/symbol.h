#ifndef SYMBOL_H
#define SYMBOL_H

#include "gpl_type.h"
#include <string>
using namespace std;

class Symbol
{
    public:
      Symbol();
      Symbol(Gpl_type gpl_type, string var_name, int val);
      Symbol(Gpl_type gpl_type, string var_name, double val);
      Symbol(Gpl_type gpl_type, string var_name, string val);
      int getInt();
      double getDouble();
      string getId();
      string getString();
      Gpl_type getType();

    private:
      string m_var_name;
      Gpl_type m_gpl_type;
      int m_iVal;
      double m_dVal;
      string m_strVal;


};
#endif
