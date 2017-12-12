#include "simulation.hpp"
#include "logger/logger.hpp"


int main(int argc, char *argv[])
{

  // TODO: ask a user about logger - step by step mode and verbose level
  Logger logger = Logger(Verbose::info);

  Simulation::instance().setLogger(logger);
  Simulation::instance().createResources();
  Simulation::instance().start();
  return 0;
}
