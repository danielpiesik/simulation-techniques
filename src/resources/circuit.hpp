#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include "rng/rng.hpp"
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

  void startTest();
  void finishTest(bool success);

  int id();

  static void reset();
  static void saveGeneratorsValues();

private:

  void injection();
  void tryStartTesting();
  void utilize();

  static int m_globalId;
  int m_id;
  Tester *p_tester;

  bool m_success_finish_test;
  double m_startTest;

  double m_injectTime;

  static ExponentialRNG m_curcuitGenerator;

};


#endif // CIRCUIT_HPP
