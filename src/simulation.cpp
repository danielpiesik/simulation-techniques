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
  logger().info("start simulation\n");
}

Logger&
Simulation::logger() const
{
  return *p_logger;
}
}

double
Simulation::getSimulationTime()
{
  return m_simulationTime;
}

void
Simulation::setLogger(const Logger &inLogger)
{
  p_logger = std::make_shared<Logger> (inLogger);
}

Simulation::Simulation()
  : p_logger(nullptr)
  , m_simulationTime(0.0)
{}

Simulation::~Simulation()
{}
