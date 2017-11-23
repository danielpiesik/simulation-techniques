#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include "rng/rng.hpp"


class RNG
{

public:

  static RNG &instance();
  RNG(const RNG &inRNG) = delete;
  void operator=(const RNG &inRNG) = delete;

  UniformRNG m_seedGenerator;
  ExponentialRNG m_curcuitGenerator;

private:

  RNG();

};


#endif // GENERATORS_HPP
