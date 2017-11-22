#include "resources/tester.hpp"
#include "simulation.hpp"


Tester::Tester()
  : m_busy(false)
  , p_circuit(nullptr)
{
  Simulation::instance().logger().debug("constructor of Tester");
}

Tester::~Tester()
{
  Simulation::instance().logger().debug("destructor of Tester");
}
