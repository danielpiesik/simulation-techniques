#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "stats/measurements.hpp"


static struct Statistics
{

  static TestingTime m_testing_time;
  static QueueSize m_queue_size;
  static FailureUtilization m_failure_utilization;
  static SuccessUtilization m_success_utilization;
  static CircuitLiveTime m_circuit_live_time;

  void aggregate();
  void print();
  void reset();

} Statistics;


#endif // STATISTICS_HPP
