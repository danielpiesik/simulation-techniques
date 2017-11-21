#include "resources/tester.hpp"
#include "simulation.hpp"


Tester::Tester()
{
  Simulation::instance().logger().debug("constructor of Tester\n");
}

Tester::~Tester()
{
  Simulation::instance().logger().debug("destructor of Tester\n");
}
