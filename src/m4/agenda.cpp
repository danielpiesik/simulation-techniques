#include <stdexcept>
#include "m4/agenda.hpp"
#include "simulation.hpp"


Agenda::Agenda()
 : m_eventsList(std::vector<Event*>())
{
  Simulation::instance().logger().debug("constructor of Agenda");
}

Agenda::~Agenda()
{
  Simulation::instance().logger().debug("destructor of Agenda");
}

void
Agenda::addEvent(Event *inEvent)
{
  std::vector<Event*>::reverse_iterator event_iter;
  event_iter = m_eventsList.rbegin();
  while (event_iter != m_eventsList.rend()
        && (*event_iter)->executeTime() > inEvent->executeTime())
  {
    ++event_iter;
  }
  m_eventsList.insert(event_iter.base(), new Event(*inEvent));
}

Event*
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
  delete *m_eventsList.begin();
  m_eventsList.erase(m_eventsList.begin());
}

bool
Agenda::isEmpty() const
{
  return m_eventsList.size() == 0;
}

void
Agenda::clear()
{
  while (!isEmpty())
    removeFirst();
}

void
Agenda::removeProcess(Process *inProcess)
{
  std::vector<Event*>::iterator event_iter;
  event_iter = m_eventsList.begin();
  while (event_iter != m_eventsList.end())
  {
    if ((*event_iter)->process() == inProcess)
      event_iter = m_eventsList.erase(event_iter);
    else
      ++event_iter;
  }
}
