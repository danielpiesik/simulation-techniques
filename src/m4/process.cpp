#include "m4/process.hpp"
#include "simulation.hpp"


Process::Process()
  : m_phase(0)
  , m_terminated(false)
  , p_event(new Event(this))
{}

Process::~Process()
{
  delete p_event;
}

void
Process::activate(double time)
{
  p_event->setExecuteTime(Simulation::instance().simulationTime() + time);
  Simulation::instance().agenda().addEvent(p_event);
}

bool
Process::isTerminated() const
{
  return m_terminated;
}
