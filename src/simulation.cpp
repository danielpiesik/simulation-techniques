#include <stdio.h>
#include "simulation.hpp"
#include "settings.hpp"


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

Table&
Simulation::table() const
{
  return *p_table;
}

double
Simulation::getSimulationTime() const
{
  return m_simulationTime;
}

void
Simulation::setLogger(const Logger &inLogger)
{
  p_logger = std::make_shared<Logger> (inLogger);
}

void
Simulation::createResources()
{
  logger().info("create resources\n");

  // table
  p_table = std::shared_ptr<Table> (new Table());

  // testers
  table().testers().reserve(TaskSettings.m_numberOfTesters);
  for(unsigned int i = 0; i < TaskSettings.m_numberOfTesters; ++i)
  {
    table().addTester(new Tester());
  }
}

Simulation::Simulation()
  : p_logger(nullptr)
  , p_table(nullptr)
  , m_simulationTime(0.0)
{}

Simulation::~Simulation()
{}
