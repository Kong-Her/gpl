#include "exit_stmt.h"
extern int line_count;

Exit_stmt::Exit_stmt(Expression *expr)
{
    m_expr = expr;
    m_line_number = line_count;
}
void Exit_stmt::execute()
{
    cout << "gpl[" << m_line_number << "]: ";
    int return_val = m_expr->eval_int();
    cout << "exit(" << return_val << ")" << endl;
    exit(return_val);
}
