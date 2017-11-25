#include <ctime>
#include <cstdlib>
#include "metadata/settings.hpp"
#include "metadata/generators.hpp"


RNG::RNG()
  : m_seedGenerator(rand() + 4536547)
  , m_curcuitGenerator(GeneratorsSettings.circuit_generator_mean, 0)
  , m_testingTimeByTester(std::vector<NormalRNG>())
{
  srand((unsigned int)time(NULL));

  m_testingTimeByTester.reserve(TaskSettings.m_numberOfTesters);
  for(unsigned int i = 0; i < TaskSettings.m_numberOfTesters; ++i)
  {
    m_testingTimeByTester.push_back(
      NormalRNG(TaskSettings.m_meanAndStdDevForTestingTime[i][0],
                TaskSettings.m_meanAndStdDevForTestingTime[i][1])
    );
  }
}

RNG&
RNG::instance()
{
  static RNG instance;
  return instance;
}
