#include <stdexcept>
#include "resources/tester.hpp"
#include "metadata/generators.hpp"
#include "simulation.hpp"


Tester::Tester(int id, ExponentialRNG* inBreakDownGenerator,
               UniformRNG* inBreakDownDurationGenerator)
  : m_id(id)
  , p_circuit(nullptr)
  , m_nextBreakDownTime(0.0)
  , m_finishBreakDownTime(0.0)
  , p_breakDownGenerator(inBreakDownGenerator)
  , p_breakDownDurationGenerator(inBreakDownDurationGenerator)
{
  Simulation::instance().logger().debug("constructor of Tester");
  planBreakDown();
}

Tester::~Tester()
{
  Simulation::instance().logger().debug("destructor of Tester");

  if (p_circuit)
    delete p_circuit;
  if (p_breakDownGenerator)
    delete p_breakDownGenerator;
  if (p_breakDownDurationGenerator)
    delete p_breakDownDurationGenerator;
}

void
Tester::execute()
{
  switch (static_cast<TesterPhase>(m_phase))
  {
    case TesterPhase::idle:
    {
      if (isItBreakDownTime())
        breakDown();
      else
        startTesting();
      break;
    }
    case TesterPhase::testing:
    {
      if (isItBreakDownTime())
        breakDown();
      else
        finishTesting();
      break;
    }
    case TesterPhase::waiting:
    {
      if (isItBreakDownTime())
        breakDown();
      break;
    }
    case TesterPhase::break_down:
    {
      if (isItFinishBreakDownTime())
        finishBraekDown();
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
Tester::prepareTest(Circuit *inCircuit)
{
  if (!isIdle())
  {
    Simulation::instance().logger().critical(
      "Tester %d prepares test of circuit %d but he is not idle",
      m_id, inCircuit->id());
    throw std::runtime_error("Tester prepares test without circuit");
  }

  p_circuit = inCircuit;
  p_circuit->testedBy(this);
}

void
Tester::startTesting()
{
  if (!hasCircuit())
  {
    Simulation::instance().logger().critical(
      "Tester %d starts test without circuit", m_id);
    throw std::runtime_error("Tester starts test without circuit");
  }

  m_phase = static_cast<int>(TesterPhase::testing);
  double testing_time = RNG::instance().m_testingTimeByTester[m_id].value();
  this->activate(testing_time);
  Simulation::instance().logger().debug(
    "tester %d starts test the circuit %d and will finish on %f",
    m_id, p_circuit->id(),
    Simulation::instance().simulationTime() + testing_time);
}

void
Tester::moveCircuitTo(Tester *inTester)
{
  inTester->prepareTest(p_circuit);
  inTester->activate();
  p_circuit=nullptr;
  m_phase = static_cast<int>(TesterPhase::idle);
}

void
Tester::utilizeCircuit()
{
  p_circuit->activate();
  p_circuit=nullptr;
  m_phase = static_cast<int>(TesterPhase::idle);
}

bool
Tester::isIdle()
{
  return static_cast<TesterPhase>(m_phase) == TesterPhase::idle;
}

bool
Tester::isWaiting()
{
  return static_cast<TesterPhase>(m_phase) == TesterPhase::waiting;
}

bool
Tester::isBroken()
{
  return static_cast<TesterPhase>(m_phase) == TesterPhase::break_down;
}

bool
Tester::hasCircuit()
{
  return p_circuit != nullptr;
}

bool
Tester::isFirstTester()
{
  return *Simulation::instance().table().testers().begin() == this;
}

bool
Tester::isLastTester()
{
  return Simulation::instance().table().testers().back() == this;
}

void
Tester::finishTesting()
{
  if (isIdle())
  {
    Simulation::instance().logger().critical(
      "Tester %d finishes test but is idle", m_id);
    throw std::runtime_error("Tester finishes test but is idle");
  }

  if (!Simulation::instance().table().isMotionless())
  {
    Simulation::instance().logger().critical(
      "Tester %d finishes test but table is rotating", m_id);
    throw std::runtime_error("Tester finishes test but table is rotating");
  }

  p_circuit->testedBy(nullptr);
  m_phase = static_cast<int>(TesterPhase::waiting);
  Simulation::instance().table().activate();
  Simulation::instance().logger().debug(
    "tester %d finished testing the circuit %d", m_id, p_circuit->id());
}

bool
Tester::isItBreakDownTime()
{
  return Simulation::instance().simulationTime() == m_nextBreakDownTime;
}

bool
Tester::isItFinishBreakDownTime()
{
  return Simulation::instance().simulationTime() == m_finishBreakDownTime;
}

void
Tester::planBreakDown()
{
  double time = p_breakDownGenerator->value();
  this->activate(time);
  m_nextBreakDownTime = Simulation::instance().simulationTime() + time;
  Simulation::instance().logger().debug(
    "tester %d will break down next time on %f", m_id, m_nextBreakDownTime);
}

void
Tester::breakDown()
{
  if (hasCircuit())
    utilizeCircuit();
  m_phase = static_cast<int>(TesterPhase::break_down);

  Simulation::instance().agenda().removeProcess(this);

  double time = p_breakDownDurationGenerator->value();
  this->activate(time);
  m_finishBreakDownTime = Simulation::instance().simulationTime() + time;
  Simulation::instance().logger().debug(
    "tester %d is going to break down and it will finish on %f",
    m_id, m_finishBreakDownTime);
}

void
Tester::finishBraekDown()
{
  Simulation::instance().logger().debug("tester %d finished break down", m_id);

  m_phase = static_cast<int>(TesterPhase::idle);
  planBreakDown();

  if (Simulation::instance().table().isMotionless())
    Simulation::instance().table().activate();

  if (isFirstTester() && !Simulation::instance().table().circuits().empty())
    Simulation::instance().table().circuits().front()->activate();
}
