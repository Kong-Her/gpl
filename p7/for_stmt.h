#ifndef FOR_STMT_H
#define FOR_STMT_H

#include "statement.h"
#include "statement_block.h"
#include "expression.h"

class For_stmt: public Statement
{
    public:
        For_stmt(Statement_block *, Statement_block *, 
                 Statement_block *, Expression *);

    protected:
        void execute();


    private:
        Statement_block *m_initializer;
        Statement_block *m_incrementor;
        Statement_block *m_body;
        Expression *m_expr;

};

#endif
