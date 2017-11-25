#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include "m4/process.hpp"

class Tester;


enum class CircuitPhase: int
{
  injection = 0,
  waiting_in_queue,
  being_tested,
};


class Circuit: public Process
{

public:

  Circuit();
  ~Circuit();

  virtual void execute();

  void testedBy(Tester *inTester);

  int id();

private:

  void injection();
  void tryStartTesting();
  void utilize();

  static int m_globalId;
  int m_id;
  Tester *p_tester;

};


#endif // CIRCUIT_HPP
