#include "if_stmt.h"

If_stmt::If_stmt(Expression *expr, Statement_block *stmt_block, 
                 Statement_block *stmt_block2)
{
    m_expr = expr;
    m_statement_block = stmt_block;
    m_statement_block2 = stmt_block2;
}
void If_stmt::execute()
{
    if (m_expr->eval_int())
    {
        m_statement_block->execute();
    }
    else
    {
        if (m_statement_block2)
        {
            m_statement_block2->execute();
        }
    }
}
