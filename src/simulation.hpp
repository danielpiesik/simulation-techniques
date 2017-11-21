#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <memory>
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
  double getSimulationTime() const;

  void setLogger(const Logger &inLogger);
  void createResources();

private:

  Simulation();

  std::shared_ptr<Logger> p_logger;
  std::shared_ptr<Table> p_table;

  double m_simulationTime;

};


#endif // SIMULATION_HPP
