#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "stats/measurements.hpp"


static struct Statistcs
{

  static TestingTime m_testing_time;
  static QueueSize m_queue_size;
  static CircuitUtilization m_curcuit_utilization;

  void aggregate();
  void print();
  void reset();

} Statistcs;


#endif // STATISTICS_HPP
