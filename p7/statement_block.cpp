#include "statement_block.h"
#include "gpl_assert.h"
using namespace std;


Statement_block::Statement_block()
{

}
void Statement_block::insert(Statement *stmt)
{
    m_vector_statement.push_back(stmt);
}

// Return true if this statement_block has no statements, false otherwise
// Implement this function for p7 (but you won't need it until p8)
bool Statement_block::empty()
{
  // This function MUST be defined for p8
  // If you forget to define it, none of your animations will work
  // So define it when you implement p7

  // place holder to keep the compiler from issuing a warning
  return true;
}

// this function is called for all non-animation_block statement_blocks
// Implement it for p7
void Statement_block::execute()
{
    vector<Statement *>::iterator it;

    for (it = m_vector_statement.begin(); 
         it != m_vector_statement.end(); it++)
    {
        (*it)->execute();
    }
}
