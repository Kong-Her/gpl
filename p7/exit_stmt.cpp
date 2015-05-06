#include "exit_stmt.h"

Exit_stmt::Exit_stmt(Expression *expr)
{
    m_expr = expr;
}
void Exit_stmt::execute()
{
    int return_val = m_expr->eval_int();
    exit(return_val);
}
