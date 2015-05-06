#ifndef EXIT_STMT_H
#define EXIT_STMT_H

#include "statement.h"
#include "expression.h"

class Exit_stmt: public Statement
{
    public:
        Exit_stmt(Expression *);
        void execute();

    private:
        Expression *m_expr;

};

#endif

