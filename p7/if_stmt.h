#ifndef IF_STMT_H
#define IF_STMT_H

#include "statement.h"
#include "statement_block.h"
#include "expression.h"

class If_stmt: public Statement
{
    public:
        If_stmt(Expression *, Statement_block *);

    protected:
        void execute();

    private:
        Statement_block *m_statement_block;
        Expression *m_expr;

};

#endif

