#ifndef MEASUREMENTS_HPP
#define MEASUREMENTS_HPP

#include <vector>
#include "stats/measure_container.hpp"


//=============================================================================
// QueueSize
//=============================================================================

struct QueueSize: public MeasureContainer<double>
{

public:

  QueueSize();

  void add(unsigned int value);
  double value();
  void reset();

private:

  double m_value;
  double m_last_update_time;
  double m_sum;

};


//=============================================================================
// TestingTime
//=============================================================================

struct TestingTime: public MeasureContainer<double>
{

public:

  TestingTime();

  void add(double value);
  double value();
  void reset();

private:

  double m_value;
  int m_iter;

};


//=============================================================================
// CircuitUtilization
//=============================================================================

struct CircuitUtilization
{

  struct _Utilizations : public MeasureContainer<int>
  {
    void add();
    int value();
    void reset();

    int m_value;
  };

public:

  CircuitUtilization();

  _Utilizations& get(int tester_id);

  void aggregate();
  void reset();

private:

  static std::vector<_Utilizations> m_utilization_counters;

};

#endif // MEASUREMENTS_HPP