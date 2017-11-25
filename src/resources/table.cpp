#include <stdexcept>
#include "resources/table.hpp"
#include "simulation.hpp"


Table::Table()
  : m_testers(std::vector<Tester*>())
  , m_circuits(std::vector<Circuit*>())
{
  Simulation::instance().logger().debug("constructor of Table");
}

Table::~Table()
{
  Simulation::instance().logger().debug("destructor of Table");
  for (Tester *tester : m_testers)
  {
    delete tester;
  }
  m_testers.clear();
}

void
Table::execute()
{
  switch (static_cast<TablePhase>(m_phase))
  {
    case TablePhase::motionless:
    {
      break;
    }
    case TablePhase::rotating:
    {
      break;
    }
    case TablePhase::break_down:
    {
      break;
    }
    default:
    {
      Simulation::instance().logger().critical(
        "Invalid phase (%d) in table process", m_phase);
      throw std::runtime_error("Invalid phase in table process");
    }
  }
}

void
Table::addTester(Tester *inTester)
{
  testers().push_back(inTester);
}

void
Table::enqueue(Circuit *inCircuit)
{
  circuits().push_back(inCircuit);
}

std::vector<Tester*>&
Table::testers()
{
  return m_testers;
}

std::vector<Circuit*>&
Table::circuits()
{
  return m_circuits;
}
