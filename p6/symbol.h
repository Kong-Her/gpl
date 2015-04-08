#ifndef SYMBOL_H
#define SYMBOL_H

#include "gpl_type.h"
#include "game_object.h"
#include <string>
using namespace std;

class Symbol
{
    public:
      Symbol();
      Symbol(string, int);
      Symbol(string var_name);
      Symbol(Gpl_type gpl_type, string var_name, int val);
      Symbol(Gpl_type gpl_type, string var_name, double val);
      Symbol(Gpl_type gpl_type, string var_name, string val);
      Symbol(Gpl_type gpl_type, string var_name, Game_object *);
      int getInt();
      double getDouble();
      string getId();
      string getString();
      Gpl_type get_type();
      Game_object *get_game_object_value();

    private:
      Game_object *m_game_obj;
      string m_var_name;
      Gpl_type m_gpl_type;
      int m_int_val;
      double m_double_val;
      string m_string_val;


};
#endif
