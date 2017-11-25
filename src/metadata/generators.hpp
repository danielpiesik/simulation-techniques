#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <vector>
#include "rng/rng.hpp"


class RNG
{

public:

  static RNG &instance();
  RNG(const RNG &inRNG) = delete;
  void operator=(const RNG &inRNG) = delete;

  UniformRNG m_seedGenerator;
  ExponentialRNG m_curcuitGenerator;
  std::vector<NormalRNG> m_testingTimeByTester;

private:

  RNG();

};


#endif // GENERATORS_HPP
