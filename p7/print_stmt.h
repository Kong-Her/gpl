#ifndef PRINT_STMT_H
#define PRINT_STMT_H

#include "statement.h"
#include "expression.h"
#include <string>

class Print_stmt: public Statement
{
    public:
        Print_stmt(Expression *);
        void execute();
    
    private:
        Expression *m_expr;

};

#endif

