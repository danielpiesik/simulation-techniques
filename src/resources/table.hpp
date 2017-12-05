#ifndef TABLE_HPP
#define TABLE_HPP

#include <vector>
#include "m4/process.hpp"
#include "resources/tester.hpp"
#include "resources/circuit.hpp"


enum class TablePhase: int
{
  motionless = 0,
  rotating,
  break_down,
};


class Table: public Process
{

public:

  Table();
  ~Table();

  virtual void execute();

  void addTester(Tester *inTester);
  void enqueue(Circuit *inCircuit);

  bool isMotionless();

  std::vector<Tester*>& testers();
  std::vector<Circuit*>& circuits();

private:

  std::vector<Tester*> m_testers;
  std::vector<Circuit*> m_circuits;

  void tryRotate();
  void finishRotate();

  bool anyTesterHasCircuit();

};


#endif // TABLE_HPP
