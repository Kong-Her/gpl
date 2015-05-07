#include "print_stmt.h"
extern int line_count;

Print_stmt::Print_stmt(Expression *expr)
{
    m_line_number = line_count;
    m_expr = expr;
}
void Print_stmt::execute()
{
    cout << "gpl[" << m_line_number << "]: ";
    std::string str = m_expr->eval_string();
    cout << str << endl;
}

