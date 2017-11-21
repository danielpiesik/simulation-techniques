#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <memory>
#include "logger/logger.hpp"


class Simulation
{
public:

  static Simulation &instance();
  Simulation(const Simulation &inSimulation) = delete;
  void operator=(const Simulation &inSimulation) = delete;

  ~Simulation();

  void start();

  double getSimulationTime();
  Logger& logger() const;

  void setLogger(const Logger &inLogger);

private:

  Simulation();

  std::shared_ptr<Logger> p_logger;

  double m_simulationTime;

};


#endif // SIMULATION_HPP
