#include <stdexcept>
#include "resources/tester.hpp"
#include "metadata/generators.hpp"
#include "simulation.hpp"


Tester::Tester(int id)
  : m_id(id)
  , p_circuit(nullptr)
{
  Simulation::instance().logger().debug("constructor of Tester");
}

Tester::~Tester()
{
  Simulation::instance().logger().debug("destructor of Tester");
}

void
Tester::execute()
{
  switch (static_cast<TesterPhase>(m_phase))
  {
    case TesterPhase::idle:
    {
      startTesting();
      break;
    }
    case TesterPhase::testing:
    {
      finishTesting();
      break;
    }
    case TesterPhase::waiting:
    {
      break;
    }
    case TesterPhase::break_down:
    {
      break;
    }
    default:
    {
      Simulation::instance().logger().critical(
        "Invalid phase (%d) in tester process", m_phase);
      throw std::runtime_error("Invalid phase in tester process");
    }
  }
}

void
Tester::prepareTest(Circuit *inCircuit)
{
  if (!isIdle())
  {
    Simulation::instance().logger().critical(
      "Tester %d prepares test of circuit %d but he is not idle",
      m_id, inCircuit->id());
    throw std::runtime_error("Tester prepares test without circuit");
  }

  p_circuit = inCircuit;
  p_circuit->testedBy(this);
}

void
Tester::startTesting()
{
  if (!hasCircuit())
  {
    Simulation::instance().logger().critical(
      "Tester %d starts test without circuit", m_id);
    throw std::runtime_error("Tester starts test without circuit");
  }

  m_phase = static_cast<int>(TesterPhase::testing);
  double testing_time = RNG::instance().m_testingTimeByTester[m_id].value();
  this->activate(testing_time);
  Simulation::instance().logger().debug(
    "tester %d starts test the circuit %d and will finish on %f",
    m_id, p_circuit->id(),
    Simulation::instance().simulationTime() + testing_time);
}

void
Tester::moveCircuitTo(Tester *inTester)
{
  inTester->prepareTest(p_circuit);
  inTester->activate();
  p_circuit=nullptr;
  m_phase = static_cast<int>(TesterPhase::idle);
}

void
Tester::utilizeCircuit()
{
  p_circuit->activate();
  p_circuit=nullptr;
  m_phase = static_cast<int>(TesterPhase::idle);
}

bool
Tester::isIdle()
{
  return static_cast<TesterPhase>(m_phase) == TesterPhase::idle;
}

bool
Tester::isWaiting()
{
  return static_cast<TesterPhase>(m_phase) == TesterPhase::waiting;
}

bool
Tester::hasCircuit()
{
  return p_circuit != nullptr;
}

void
Tester::finishTesting()
{
  if (isIdle())
  {
    Simulation::instance().logger().critical(
      "Tester %d finishes test but is idle", m_id);
    throw std::runtime_error("Tester finishes test but is idle");
  }

  if (!Simulation::instance().table().isMotionless())
  {
    Simulation::instance().logger().critical(
      "Tester %d finishes test but table is rotating", m_id);
    throw std::runtime_error("Tester finishes test but table is rotating");
  }

  p_circuit->testedBy(nullptr);
  m_phase = static_cast<int>(TesterPhase::waiting);
  Simulation::instance().table().activate();
  Simulation::instance().logger().debug(
    "tester %d finished testing the circuit %d", m_id, p_circuit->id());
}
