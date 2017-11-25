#ifndef TESTER_HPP
#define TESTER_HPP

#include "m4/process.hpp"
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

  Tester(int id);
  ~Tester();

  virtual void execute();

  void prepareTest(Circuit *inCircuit);
  void moveCircuitTo(Tester *inTester);
  void utilizeCircuit();

  bool isIdle();
  bool isWaiting();
  bool hasCircuit();

private:

  void startTesting();
  void finishTesting();

  int m_id;
  Circuit* p_circuit;

};


#endif // TESTER_HPP
