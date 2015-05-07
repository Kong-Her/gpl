#include "event_manager.h"
#include "gpl_assert.h"
#include "statement_block.h"
using namespace std;

/* static */ Event_manager *Event_manager::m_instance = 0;

/* static */ Event_manager * Event_manager::instance()
{
  if (!m_instance)
    m_instance = new Event_manager();
  return m_instance;
}

Event_manager::Event_manager()
{
}

Event_manager::~Event_manager()
{
}
void Event_manager::register_handler(Window::Keystroke keystroke, 
                                      Statement_block *stmt_block)
{
    m_event_types[keystroke].push_back(stmt_block);
}

void 
Event_manager::execute_handlers(Window::Keystroke keystroke)
{
    vector<Statement_block *>::iterator it;

    for (it = m_event_types[keystroke].begin(); 
         it != m_event_types[keystroke].end(); it++)
    {
        (*it)->execute();
    }
}
