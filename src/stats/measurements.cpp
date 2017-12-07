#include "stats/measurements.hpp"
#include "simulation.hpp"


//=============================================================================
// QueueSize
//=============================================================================

QueueSize::QueueSize()
{
  reset();
}

void
QueueSize::add(unsigned int value)
{
  double now = Simulation::instance().simulationTime();
  double time =  now - m_last_update_time;
  m_value += (value * time);
  m_sum += time;
  m_last_update_time = now;
}

double
QueueSize::value()
{
  return m_value / m_sum;
}

void
QueueSize::reset()
{
  m_value = 0.0;
  m_last_update_time = 0.0;
  m_sum = 0.0;
}


//=============================================================================
// TestingTime
//=============================================================================

TestingTime::TestingTime()
{
  reset();
}

void
TestingTime::add(double value)
{
  m_value += value;
  ++m_iter;
}

double
TestingTime::value()
{
  return m_value / double(m_iter);
}

void
TestingTime::reset()
{
  m_value = 0.0;
  m_iter = 0;
}
