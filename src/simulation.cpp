#include <stdio.h>

#include "simulation.hpp"


Simulation&
Simulation::instance()
{
  static Simulation instance;
  return instance;
}

void
Simulation::start()
{
  printf("start simulation\n");
}

double
Simulation::getSimulationTime()
{
  return m_simulationTime;
}


Simulation::Simulation()
  : m_simulationTime(0.0)
{}
