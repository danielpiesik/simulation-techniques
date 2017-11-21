#include "resources/table.hpp"
#include "simulation.hpp"


Table::Table()
  : m_testers(std::vector<std::shared_ptr<Tester>>())
{
  Simulation::instance().logger().debug("constructor of Table\n");
}

Table::~Table()
{
  Simulation::instance().logger().debug("destructor of Table\n");
}

void
Table::addTester(Tester *inTester)
{
  testers().push_back(std::shared_ptr<Tester>(inTester));
}

std::vector<std::shared_ptr<Tester>>&
Table::testers()
{
  return m_testers;
}
