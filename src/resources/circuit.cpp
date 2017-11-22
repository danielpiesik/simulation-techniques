#include "resources/circuit.hpp"
#include "simulation.hpp"


Circuit::Circuit()
{
  Simulation::instance().logger().debug("constructor of Circuit");
}

Circuit::~Circuit()
{
  Simulation::instance().logger().debug("destructor of Circuit");
}
