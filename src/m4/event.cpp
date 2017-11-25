#include "m4/event.hpp"
#include "m4/process.hpp"
#include "simulation.hpp"


Event::Event(Process *inProcess)
  : m_executeTime(-1.0)
  , p_process(inProcess)
{}

Event::~Event()
{}

double
Event::executeTime() const
{
  return m_executeTime;
}

Process*
Event::process() const
{
  return p_process;
}

void
Event::setExecuteTime(double time)
{
  m_executeTime = time;
}
