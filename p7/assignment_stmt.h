#ifndef ASSIGNMENT_STMT_H
#define ASSIGNMENT_STMT_H

#include "statement.h"
#include "expression.h"
#include "variable.h"

class Assignment_stmt: public Statement
{
    public:
        Assignment_stmt(Variable *, Expression *);

    protected:
        void execute();

    private:
        Variable *m_var;
        Expression *m_expr;

};

#endif
