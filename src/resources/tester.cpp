#include "resources/tester.hpp"
#include "simulation.hpp"


Tester::Tester()
  : m_idle(true)
  , p_circuit(nullptr)
{
  Simulation::instance().logger().debug("constructor of Tester");
}

Tester::~Tester()
{
  Simulation::instance().logger().debug("destructor of Tester");
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
  return m_idle;
}
