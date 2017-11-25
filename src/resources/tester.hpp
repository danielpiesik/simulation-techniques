#ifndef TESTER_HPP
#define TESTER_HPP

#include "resources/circuit.hpp"


class Tester
{

public:

  Tester();
  ~Tester();

  void startTesting(Circuit *inCircuit);

  bool isIdle();

private:

  bool m_idle;
  Circuit* p_circuit;

};


#endif // TESTER_HPP
