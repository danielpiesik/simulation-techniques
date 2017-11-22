#ifndef TABLE_HPP
#define TABLE_HPP

#include <vector>
#include "resources/tester.hpp"
#include "resources/circuit.hpp"


class Table
{

public:

  Table();
  ~Table();

  void addTester(Tester *inTester);
  void enqueue(Circuit *inCircuit);

  std::vector<Tester*>& testers();
  std::vector<Circuit*>& circuits();

private:

  std::vector<Tester*> m_testers;
  std::vector<Circuit*> m_circuits;

};


#endif // TABLE_HPP
