#include "m4/process.hpp"
#include "simulation.hpp"
#include "metadata/settings.hpp"
#include "metadata/generators.hpp"
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

  RNG::instance().m_curcuitGenerator.reset(
    RNG::instance().m_seedGenerator.value(7596, 9056468)
  );

  (new Circuit)->activate();

  while (simulationTime() < 500)
  {
    Process *current_process = agenda().first()->process();
    agenda().removeFirst();
    m_simulationTime = current_process->time();
    current_process->execute();
    if (current_process->isTerminated())
    {
      delete current_process;
    }
  }
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
    table().addTester(new Tester(i));
  }
}

Simulation::Simulation()
  : p_logger(nullptr)
  , p_agenda(nullptr)
  , p_table(nullptr)
  , m_simulationTime(0.0)
{}

Simulation::~Simulation()
{
  logger().info("remove resources");
  if (p_agenda)
    delete p_agenda;
  if (p_table)
    delete p_table;
}
