#include <stdio.h>
#include "simulation.hpp"
#include "settings.hpp"
#include "resources/circuit.hpp"


Simulation&
Simulation::instance()
{
  static Simulation instance;
  return instance;
}

void
Simulation::start()
{
  logger().info("start simulation");
}

Agenda&
Simulation::agenda() const
{
  return *p_agenda;
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
Simulation::simulationTime() const
{
  return m_simulationTime;
}

void
Simulation::setLogger(Logger &inLogger)
{
  p_logger = &inLogger;
}

void
Simulation::createResources()
{
  logger().info("create resources");

  // agenda
  p_agenda = new Agenda();

  // table
  p_table = new Table();

  // testers
  table().testers().reserve(TaskSettings.m_numberOfTesters);
  for(unsigned int i = 0; i < TaskSettings.m_numberOfTesters; ++i)
  {
    table().addTester(new Tester());
  }
}

Simulation::Simulation()
  : p_logger(nullptr)
  , p_agenda(nullptr)
  , p_table(nullptr)
  , m_simulationTime(0.0)
{}

Simulation::~Simulation()
{}
