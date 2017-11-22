#ifndef TESTER_HPP
#define TESTER_HPP

#include "resources/circuit.hpp"


class Tester
{

public:

  Tester();
  ~Tester();

private:

  bool m_busy;
  Circuit* p_circuit;

};


#endif // TESTER_HPP
