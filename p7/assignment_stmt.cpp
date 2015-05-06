#include "assignment_stmt.h"

Assignment_stmt::Assignment_stmt(Variable *var, Expression *expr)
{
    m_var = var;
    m_expr = expr;
}
void Assignment_stmt::execute()
{
}
