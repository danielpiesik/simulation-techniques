#include <iostream>
#include <fstream>
#include <string>
#include "stats/measurements.hpp"
#include "metadata/settings.hpp"
#include "simulation.hpp"


//=============================================================================
// QueueSize
//=============================================================================

QueueSize::QueueSize()
{
  reset();
}

void
QueueSize::add(unsigned int value)
{
  double now = Simulation::instance().simulationTime();
  double time =  now - m_last_update_time;
  m_value += (value * time);
  m_sum += time;
  m_last_update_time = now;
}

double
QueueSize::value()
{
  return m_value / m_sum;
}

void
QueueSize::reset()
{
  m_value = 0.0;
  m_last_update_time = 0.0;
  m_sum = 0.0;
}


//=============================================================================
// TestingTime
//=============================================================================

TestingTime::TestingTime()
{
  reset();
}

void
TestingTime::add(double value)
{
  m_value += value;
  ++m_iter;
}

double
TestingTime::value()
{
  return m_value / double(m_iter);
}

void
TestingTime::reset()
{
  m_value = 0.0;
  m_iter = 0;
}


//=============================================================================
// FailureUtilization
//=============================================================================

std::vector<FailureUtilization::_Utilizations>
  FailureUtilization::m_utilization_counters(TaskSettings.m_numberOfTesters);

FailureUtilization::FailureUtilization()
{
  reset();
}

FailureUtilization::_Utilizations&
FailureUtilization::get(int tester_id)
{
  return m_utilization_counters[tester_id];
}

void
FailureUtilization::aggregate()
{
  for (auto &counter : m_utilization_counters)
    counter.aggregate();
}

void
FailureUtilization::reset()
{
  for (auto &counter : m_utilization_counters)
    counter.reset();
}

void
FailureUtilization::_Utilizations::add()
{
  ++m_value;
}

int
FailureUtilization::_Utilizations::value()
{
  return m_value;
}

void
FailureUtilization::_Utilizations::reset()
{
  m_value = 0;
}

//=============================================================================
// SuccessUtilization
//=============================================================================

SuccessUtilization::SuccessUtilization()
{
  reset();
}

void
SuccessUtilization::add()
{
  ++m_value;
}

int
SuccessUtilization::value()
{
  return m_value;
}

void
SuccessUtilization::reset()
{
  m_value = 0;
}

//=============================================================================
// CircuitLiveTime
//=============================================================================

CircuitLiveTime::CircuitLiveTime()
{
  m_circuits_live_times = std::vector<_CircuitLiveTime>(
    SimulationSettings.m_maxSuccessUtilization 
    + SimulationSettings.m_transient_phase_circuits,
    {0.0, 0.0}
  );
  m_iter = 0;
}

void
CircuitLiveTime::add(double value)
{
  double now = Simulation::instance().simulationTime();
  m_circuits_live_times[m_counter].simulation_time += now;
  m_circuits_live_times[m_counter].circuit_live_time += value;
  ++m_counter;
}

void
CircuitLiveTime::reset()
{
  m_counter = 0;
  ++m_iter;
}

void
CircuitLiveTime::save2file()
{
  std::string dir_str = "output/transient_phase/";

  calculate();

  std::ofstream file;
  file.open(dir_str + "transient_phase.txt",
            std::ios_base::out | std::ios_base::trunc);
  for(auto &circuit_live_time : m_circuits_live_times)
  {
    file << circuit_live_time.simulation_time << " "
         << circuit_live_time.circuit_live_time << std::endl;
  }
  file.close();

  file.open(dir_str + "metadata.txt",
            std::ios_base::out | std::ios_base::trunc);
  file << SimulationSettings.m_transient_phase_circuits
       << " # transient phase" << std::endl;
  file << "Counter of successful utilized circuit # OX axis label" << std::endl;
  file << "Circuit live time # OY axis label" << std::endl;
  file.close();
}

void
CircuitLiveTime::calculate()
{
  if (m_iter != SimulationSettings.m_iteration_number)
  {
    Simulation::instance().logger().critical(
      "Number of loop iterations does not match. %d != %d",
      m_iter, SimulationSettings.m_iteration_number);
    throw std::runtime_error("Wrong number of loop iterations");
  }

  for(auto &circuit_live_time : m_circuits_live_times)
  {
    circuit_live_time.simulation_time /= double(m_iter);
    circuit_live_time.circuit_live_time /= double(m_iter);
  }
}
