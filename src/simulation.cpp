#include "m4/process.hpp"
#include "rng/rng.hpp"
#include "simulation.hpp"
#include "metadata/settings.hpp"
#include "resources/circuit.hpp"
#include "stats/statistics.hpp"


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


  for(int iter = 0; iter < SimulationSettings.m_iteration_number; ++iter)
  {
    reset();
    logger().info("start %d iteration", iter + 1);

    (new Circuit)->activate();

    while (Statistics.m_success_utilization.value() <
      SimulationSettings.m_maxSuccessUtilization)
    {
      Event *current_event = agenda().first();
      Process *current_process = current_event->process();
      m_simulationTime = current_event->executeTime();
      agenda().removeFirst();
      current_process->execute();
      if (current_process->isTerminated())
      {
        delete current_process;
      }
    }

    Statistics.m_queue_size.add(
      Simulation::instance().table().circuits().size());

    Statistics.aggregate();
  }

  Statistics.print();

  logger().setLevel(Verbose::none);
  reset();

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
  ExponentialRNG* g1;
  UniformRNG* g2;
  g1 = new ExponentialRNG(1.0 / TaskSettings.m_breakDownIntervalMean);
  g2 = new UniformRNG(TaskSettings.m_minBreakDownTime,
                      TaskSettings.m_maxBreakDownTime);
  p_table = new Table(g1, g2);

  // testers
  table().testers().reserve(TaskSettings.m_numberOfTesters);
  for(unsigned int i = 0; i < TaskSettings.m_numberOfTesters; ++i)
  {
    ExponentialRNG* g1;
    UniformRNG* g2;
    NormalRNG* g3;
    g1 = new ExponentialRNG(1.0 / TaskSettings.m_breakDownIntervalMean);
    g2 = new UniformRNG(TaskSettings.m_minBreakDownTime,
                        TaskSettings.m_maxBreakDownTime);
    g3 = new NormalRNG(TaskSettings.m_meanAndStdDevForTestingTime[i][0],
                       TaskSettings.m_meanAndStdDevForTestingTime[i][1]);
    table().addTester(new Tester(i, g1, g2, g3));
  }
}

Simulation::Simulation()
  : p_logger(nullptr)
  , p_agenda(nullptr)
  , p_table(nullptr)
  , m_simulationTime(0.0)
{}

void
Simulation::reset()
{
  m_simulationTime = 0.0;
  agenda().clear();
  for(auto &tester : table().testers())
    tester->reset();
  table().reset();
  Circuit::reset();
  Statistics.reset();
}

Simulation::~Simulation()
{
  logger().info("remove resources");
  if (p_agenda)
    delete p_agenda;
  if (p_table)
    delete p_table;
}
