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
// FailureUtilization
//=============================================================================

struct FailureUtilization
{

  struct _Utilizations : public MeasureContainer<int>
  {
    void add();
    int value();
    void reset();

    int m_value;
  };

public:

  FailureUtilization();

  _Utilizations& get(int tester_id);

  void aggregate();
  void reset();

private:

  static std::vector<_Utilizations> m_utilization_counters;

};


//=============================================================================
// SuccessUtilization
//=============================================================================

struct SuccessUtilization: public MeasureContainer<int>
{

public:

  SuccessUtilization();

  void add();
  int value();
  void reset();

private:

  int m_value;

};


//=============================================================================
// CircuitLiveTime
//=============================================================================

struct CircuitLiveTime
{

public:

  struct _CircuitLiveTime
  {
    double simulation_time;
    double circuit_live_time;
  };

  CircuitLiveTime();

  void add(double value);
  void reset();

  void save2file();

private:

  int m_counter;
  std::vector<_CircuitLiveTime> m_circuits_live_times;
  int m_iter;

  void calculate();

};

#endif // MEASUREMENTS_HPP
