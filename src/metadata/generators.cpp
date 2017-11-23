#include <ctime>
#include <cstdlib>
#include "metadata/settings.hpp"
#include "metadata/generators.hpp"


RNG::RNG()
  : m_seedGenerator(rand() + 4536547)
  , m_curcuitGenerator(GeneratorsSettings.circuit_generator_mean, 0)
{
  srand((unsigned int)time(NULL));
}

RNG&
RNG::instance()
{
  static RNG instance;
  return instance;
}
