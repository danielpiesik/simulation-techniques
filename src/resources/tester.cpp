#include <stdexcept>
#include "resources/tester.hpp"
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
      break;
    }
    case TesterPhase::testing:
    {
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
Tester::startTesting(Circuit *inCircuit)
{
  if (!isIdle())
    return;
}

bool
Tester::isIdle()
{
  return static_cast<TesterPhase>(m_phase) == TesterPhase::idle;
}
