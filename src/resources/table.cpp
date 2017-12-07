#include <stdexcept>
#include "resources/table.hpp"
#include "metadata/settings.hpp"
#include "stats/statistics.hpp"
#include "simulation.hpp"


Table::Table(ExponentialRNG* inBreakDownGenerator,
             UniformRNG* inBreakDownDurationGenerator)
  : m_testers(std::vector<Tester*>())
  , m_circuits(std::vector<Circuit*>())
  , m_nextBreakDownTime(0.0)
  , m_finishBreakDownTime(0.0)
  , p_breakDownGenerator(inBreakDownGenerator)
  , p_breakDownDurationGenerator(inBreakDownDurationGenerator)
{
  Simulation::instance().logger().debug("constructor of Table");
  planBreakDown();
}

Table::~Table()
{
  Simulation::instance().logger().debug("destructor of Table");

  for (Tester *tester : m_testers)
    delete tester;
  m_testers.clear();

  for (Circuit *circuit : m_circuits)
    delete circuit;
  m_circuits.clear();

  if (p_breakDownGenerator)
    delete p_breakDownGenerator;
  if (p_breakDownDurationGenerator)
    delete p_breakDownDurationGenerator;
}

void
Table::execute()
{
  switch (static_cast<TablePhase>(m_phase))
  {
    case TablePhase::motionless:
    {
      if (isItBreakDownTime())
        breakDown();
      else
        tryRotate();
      break;
    }
    case TablePhase::rotating:
    {
      if (isItBreakDownTime())
        breakDown();
      else
        finishRotate();
      break;
    }
    case TablePhase::break_down:
    {
      finishBraekDown();
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
  if (!anyTesterHasCircuit())
    return;

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
  Statistcs.m_queue_size.add(circuits().size());
  circuits().push_back(inCircuit);

  Simulation::instance().logger().debug(
    "circuit %d added to queue (queue size = %d)",
    inCircuit->id(), circuits().size());
}

void
Table::dequeue(Circuit *inCircuit)
{
  if (circuits().front() != inCircuit)
  {
    Simulation::instance().logger().critical(
      "Only first circuit from queue can be dequeued. "
      "First circuit is %d but tried to dequeued circuit %d",
      circuits().front()->id(), inCircuit->id());
    throw std::runtime_error("Trying to dequeued not first circuit");
  }

  Statistcs.m_queue_size.add(circuits().size());
  circuits().erase(circuits().begin());

  Simulation::instance().logger().debug(
    "circuit %d removed from queue (queue size = %d)",
    inCircuit->id(), circuits().size());
}

bool
Table::isMotionless()
{
  return static_cast<TablePhase>(m_phase) == TablePhase::motionless;
}

bool
Table::isBroken()
{
  return static_cast<TablePhase>(m_phase) == TablePhase::break_down;
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
    Tester *prev_tester = *std::prev(tester_iter);

    if (!tester->hasCircuit())
      continue;

    if(tester->isLastTester())
    {
      tester->utilizeCircuit(true);
    }
    else
    {
      if (prev_tester->isBroken())
        tester->utilizeCircuit(false);
      else
        tester->moveCircuitTo(prev_tester);
    }
  }

  if(!Simulation::instance().table().circuits().empty())
    Simulation::instance().table().circuits().front()->activate();

  m_phase = static_cast<int>(TablePhase::motionless);
}

bool
Table::anyTesterHasCircuit()
{
  for (auto &tester : testers())
  {
    if (tester->hasCircuit())
      return true;
  }
  return false;
}

void
Table::utilizeAllCircuits()
{
  std::vector<Tester*>::iterator tester_iter;

  for(tester_iter = testers().begin();
      tester_iter != testers().end();
      ++tester_iter
  )
  {
    Tester *tester = (*tester_iter);
    if (tester->isTesting())
        Simulation::instance().agenda().removeProcess(tester);
    if (tester->hasCircuit())
      tester->utilizeCircuit(false);
  }
}

bool
Table::isItBreakDownTime()
{
  return Simulation::instance().simulationTime() == m_nextBreakDownTime;
}

bool
Table::isItFinishBreakDownTime()
{
  return Simulation::instance().simulationTime() == m_finishBreakDownTime;
}

void
Table::planBreakDown()
{
  double time = p_breakDownGenerator->value();
  this->activate(time);
  m_nextBreakDownTime = Simulation::instance().simulationTime() + time;
  Simulation::instance().logger().debug(
    "table will break down next time on %f", m_nextBreakDownTime);
}

void
Table::breakDown()
{
  utilizeAllCircuits();
  m_phase = static_cast<int>(TablePhase::break_down);

  Simulation::instance().agenda().removeProcess(this);

  double time = p_breakDownDurationGenerator->value();
  this->activate(time);
  m_finishBreakDownTime = Simulation::instance().simulationTime() + time;
  Simulation::instance().logger().debug(
    "table is going to break down and it will finish on %f",
    m_finishBreakDownTime);
}

void
Table::finishBraekDown()
{
  if (!isItFinishBreakDownTime())
  {
    Simulation::instance().logger().critical(
      "Table is trying to finish breakdown but is not time for that. "
      "Current time is %f and breakdown should finish of %d",
      Simulation::instance().simulationTime(), m_finishBreakDownTime);
    throw std::runtime_error("Invalid breakdown finish time");
  }

  if (!isBroken())
  {
    Simulation::instance().logger().critical(
      "Table is in phase %d but is trying to finish breakdown", m_phase);
    throw std::runtime_error("Invalid phase during finishing the breakdown");
  }

  Simulation::instance().logger().debug("table finished break down");

  m_phase = static_cast<int>(TablePhase::motionless);
  planBreakDown();

  if (!Simulation::instance().table().circuits().empty())
    Simulation::instance().table().circuits().front()->activate();
}
