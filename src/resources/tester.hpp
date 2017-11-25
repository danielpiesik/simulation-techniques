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

  void startTesting(Circuit *inCircuit);

  bool isIdle();

private:

  int m_id;
  Circuit* p_circuit;

};


#endif // TESTER_HPP
