#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "logger/logger.hpp"
#include "resources/table.hpp"
#include "resources/tester.hpp"


class Simulation
{
public:

  static Simulation &instance();
  Simulation(const Simulation &inSimulation) = delete;
  void operator=(const Simulation &inSimulation) = delete;

  ~Simulation();

  void start();

  Logger& logger() const;
  Table& table() const;
  double simulationTime() const;

  void setLogger(Logger &inLogger);
  void createResources();

private:

  Simulation();

  Logger *p_logger;
  Table *p_table;

  double m_simulationTime;

};


#endif // SIMULATION_HPP
