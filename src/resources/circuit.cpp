#include <stdexcept>
#include <vector>
#include "resources/table.hpp"
#include "resources/tester.hpp"
#include "resources/circuit.hpp"
#include "metadata/generators.hpp"
#include "stats/statistics.hpp"
#include "simulation.hpp"


int Circuit::m_globalId = 0;


Circuit::Circuit()
  : m_id(m_globalId++)
  , p_tester(nullptr)
  , m_success_finish_test(false)
  , m_startTest(0.0)
{
  // Simulation::instance().logger().debug("constructor of Circuit");
}

Circuit::~Circuit()
{
  // Simulation::instance().logger().debug("destructor of Circuit");
}

void
Circuit::execute()
{
  switch (static_cast<CircuitPhase>(m_phase))
  {
    case CircuitPhase::injection:
    {
      injection();
    }
    case CircuitPhase::waiting_in_queue:
    {
      tryStartTesting();
      break;
    }
    case CircuitPhase::being_tested:
    {
      utilize();
      break;
    }
    default:
    {
      Simulation::instance().logger().critical(
        "Invalid phase (%d) in circuit process", m_phase);
      throw std::runtime_error("Invalid phase in circuit process");
    }
  }
}

void
Circuit::testedBy(Tester *inTester)
{
  p_tester = inTester;
}

void
Circuit::startTest()
{
  m_startTest = Simulation::instance().simulationTime();
}

void
Circuit::finishTest(bool success)
{
  m_success_finish_test = success;
}

int
Circuit::id()
{
  return m_id;
}

void
Circuit::injection()
{
  Simulation::instance().table().enqueue(this);
  m_phase = static_cast<int>(CircuitPhase::waiting_in_queue);

  Circuit *new_circuit = new Circuit();
  double time = RNG::instance().m_curcuitGenerator.value();
  new_circuit->activate(time);
  Simulation::instance().logger().debug(
    "inject next circuit (%d) on %f",
    new_circuit->id(), Simulation::instance().simulationTime() + time);
}

void
Circuit::tryStartTesting()
{
  Table &table = Simulation::instance().table();
  std::vector<Circuit*> &circuits = table.circuits();
  std::vector<Tester*> &testers = table.testers();

  if (circuits.empty())
  {
    Simulation::instance().logger().critical(
      "Circuits queue is empty during trying start testing of circuit");
    throw std::runtime_error("Circuits queue is empty");
  }

  Tester &first_tester = *testers.front();
  if (table.isMotionless() && first_tester.isIdle())
  {
    table.dequeue(this);
    first_tester.prepareTest(this);
    first_tester.activate();
    m_phase = static_cast<int>(CircuitPhase::being_tested);
  }
}

void
Circuit::utilize()
{
  if (m_success_finish_test)
  {
    double now = Simulation::instance().simulationTime();
    Statistcs.m_testing_time.add(now - m_startTest);
  }
  Simulation::instance().logger().debug("circuit %d is utilized", id());
  m_terminated = true;
}
