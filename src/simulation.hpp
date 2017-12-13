#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "m4/agenda.hpp"
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

  Agenda& agenda() const;
  Logger& logger() const;
  Table& table() const;
  double simulationTime() const;

  void setLogger(Logger &inLogger);
  void createResources();

private:

  Simulation();
  void reset();
  void save2fileDistributions();

  Logger *p_logger;
  Agenda *p_agenda;
  Table *p_table;

  double m_simulationTime;

};


#endif // SIMULATION_HPP
