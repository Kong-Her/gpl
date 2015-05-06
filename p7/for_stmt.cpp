#include "for_stmt.h"

For_stmt::For_stmt(Statement_block *init, Statement_block *incrementor, 
                   Statement_block *body, Expression *expr)
{
    m_initializer = init;
    m_incrementor = incrementor;
    m_expr = expr;
}
void For_stmt::execute()
{
}
