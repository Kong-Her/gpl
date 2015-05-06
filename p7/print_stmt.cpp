#include "print_stmt.h"

Print_stmt::Print_stmt(Expression *expr)
{
    m_expr = expr;
}
void Print_stmt::execute()
{
    std::string str = m_expr->eval_string();
    cout << str;
}

