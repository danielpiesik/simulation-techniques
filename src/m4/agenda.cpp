#include <stdexcept>
#include "m4/agenda.hpp"
#include "simulation.hpp"


Agenda::Agenda()
 : m_eventsList(std::vector<const Event*>())
{
  Simulation::instance().logger().debug("constructor of Agenda");
}

Agenda::~Agenda()
{
  Simulation::instance().logger().debug("destructor of Agenda");
}

void
Agenda::addEvent(const Event *inEvent)
{
  std::vector<const Event*>::reverse_iterator event_iter;
  event_iter = m_eventsList.rbegin();
  while (event_iter != m_eventsList.rend()
        && (*event_iter)->executeTime() > inEvent->executeTime())
  {
    ++event_iter;
  }
  m_eventsList.insert(event_iter.base(), inEvent);
}

const Event*
Agenda::first() const
{
  if (isEmpty())
  {
    Simulation::instance().logger().critical("The events list is empty");
    throw std::runtime_error("The events list is empty");
  }
  return *m_eventsList.begin();
}

void
Agenda::removeFirst()
{
  m_eventsList.erase(m_eventsList.begin());
}

bool
Agenda::isEmpty() const
{
  return m_eventsList.size() == 0;
}