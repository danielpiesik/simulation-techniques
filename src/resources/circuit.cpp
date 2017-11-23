#include <stdexcept>
#include "resources/circuit.hpp"
#include "metadata/generators.hpp"
#include "simulation.hpp"


Circuit::Circuit()
{
  Simulation::instance().logger().debug("constructor of Circuit");
}

Circuit::~Circuit()
{
  Simulation::instance().logger().debug("destructor of Circuit");
}

void
Circuit::execute()
{
  bool active = true;
  while (active)
  {
    switch (static_cast<Phase>(m_phase))
    {
      case Phase::injection:
      {
        injection();
        active = true;
        break;
      }
      case Phase::waiting_in_queue:
      {
        active = false;
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
}

void
Circuit::injection()
{
  Simulation::instance().logger().debug("circuit %p: injection phase", this);
  (new Circuit)->activate(RNG::instance().m_curcuitGenerator.value());
  Simulation::instance().table().enqueue(this);
  m_phase = static_cast<unsigned int>(Phase::waiting_in_queue);
}
