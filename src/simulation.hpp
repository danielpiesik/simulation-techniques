#ifndef SIMULATION_HPP
#define SIMULATION_HPP


class Simulation
{
public:

  static Simulation &instance();
  Simulation(const Simulation &inSimulation) = delete;
  void operator=(const Simulation &inSimulation) = delete;

  void start();

  double getSimulationTime();

private:

  Simulation();

  double m_simulationTime;
};


#endif // SIMULATION_HPP
