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

  Table(ExponentialRNG* inBreakDownGenerator,
        UniformRNG* inBreakDownDurationGenerator);
  ~Table();

  virtual void execute();

  void addTester(Tester *inTester);

  void enqueue(Circuit *inCircuit);
  void dequeue(Circuit *inCircuit);

  bool isMotionless();
  bool isBroken();

  std::vector<Tester*>& testers();
  std::vector<Circuit*>& circuits();

  void reset();

private:

  void tryRotate();
  void finishRotate();

  bool anyTesterHasCircuit();
  void utilizeAllCircuits();

  bool isItBreakDownTime();
  bool isItFinishBreakDownTime();
  void planBreakDown();
  void breakDown();
  void finishBraekDown();

  std::vector<Tester*> m_testers;
  std::vector<Circuit*> m_circuits;

  double m_nextBreakDownTime;
  double m_finishBreakDownTime;

  ExponentialRNG* p_breakDownGenerator;
  UniformRNG* p_breakDownDurationGenerator;

};


#endif // TABLE_HPP
