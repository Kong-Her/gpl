#include "if_stmt.h"

If_stmt::If_stmt(Expression *expr, Statement_block *stmt_block)
{
    m_expr = expr;
    m_statement_block = stmt_block;
}
void If_stmt::execute()
{
    if (m_expr->eval_int())
    {
        m_statement_block->execute();
    }
    else
    {
        m_statement_block->execute();
    }
}
