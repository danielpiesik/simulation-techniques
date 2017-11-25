#include <stdexcept>
#include "resources/table.hpp"
#include "metadata/settings.hpp"
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
      tryRotate();
      break;
    }
    case TablePhase::rotating:
    {
      finishRotate();
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
Table::tryRotate()
{
  for (Tester *tester : testers())
  {
    if ( !(tester->isIdle() || tester->isWaiting()) )
      return;
  }
  double rotating_time = TaskSettings.m_timeOfRotation;
  this->activate(rotating_time);
  m_phase = static_cast<int>(TablePhase::rotating);
  Simulation::instance().logger().debug(
    "table is rotating and will finish on %f",
    Simulation::instance().simulationTime() + rotating_time);
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
  Simulation::instance().logger().debug(
    "circuit %d added to queue (queue size = %d)",
    inCircuit->id(), circuits().size());
}

bool
Table::isMotionless()
{
  return static_cast<TablePhase>(m_phase) == TablePhase::motionless;
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

void
Table::finishRotate()
{
  Simulation::instance().logger().debug("the table finished the rotation");
  std::vector<Tester*>::reverse_iterator tester_iter;

  for(tester_iter = testers().rbegin();
      tester_iter != testers().rend();
      ++tester_iter
  )
  {
    Tester *tester = (*tester_iter);

    if(tester_iter == testers().rbegin()) // last element
    {
      if (tester->hasCircuit())
        tester->utilizeCircuit();
    }
    else if(std::next(tester_iter) == testers().rend()) // first element
    {
      if (tester->hasCircuit())
        tester->moveCircuitTo(*std::prev(tester_iter));
      if (!Simulation::instance().table().circuits().empty())
        Simulation::instance().table().circuits().front()->activate();
    }
    else
    {
      if (tester->hasCircuit())
        tester->moveCircuitTo(*std::prev(tester_iter));
    }
  }

  m_phase = static_cast<int>(TablePhase::motionless);
}
