#ifndef MEASUREMENTS_HPP
#define MEASUREMENTS_HPP

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

#endif // MEASUREMENTS_HPP
