#ifndef TESTER_HPP
#define TESTER_HPP

#include "m4/process.hpp"
#include "rng/rng.hpp"
#include "resources/circuit.hpp"


enum class TesterPhase: int
{
  idle = 0,
  testing,
  waiting,
  break_down,
};


class Tester: public Process
{

public:

  Tester(int id, ExponentialRNG* inBreakDownGenerator,
         UniformRNG* inBreakDownDurationGenerator);
  ~Tester();

  virtual void execute();

  void prepareTest(Circuit *inCircuit);
  void moveCircuitTo(Tester *inTester);
  void utilizeCircuit();

  bool isIdle();
  bool isWaiting();
  bool isBroken();
  bool hasCircuit();

  bool isFirstTester();
  bool isLastTester();

private:

  void startTesting();
  void finishTesting();

  bool isItBreakDownTime();
  bool isItFinishBreakDownTime();
  void planBreakDown();
  void breakDown();
  void finishBraekDown();

  int m_id;
  Circuit* p_circuit;

  double m_nextBreakDownTime;
  double m_finishBreakDownTime;

  ExponentialRNG* p_breakDownGenerator;
  UniformRNG* p_breakDownDurationGenerator;
};


#endif // TESTER_HPP
