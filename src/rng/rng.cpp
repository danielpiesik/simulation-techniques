#include <cmath>
#include <stdexcept>
#include "rng/rng.hpp"


UniformRNG::UniformRNG(int seed)
  : m_seed(seed)
{}

UniformRNG::~UniformRNG()
{}

double
UniformRNG::value()
{
  static const int q = 127773;
  static const int r = 2836;
  static const int range = 2147483647; //2^31-1

  int h = int(m_seed / q);
  m_seed = 16807 * (m_seed - q * h) - r * h;
  if (m_seed < 0)
  {
    m_seed += range;
  }
  return (double)(m_seed) / (double)(range);
}

double
UniformRNG::value(double min, double max)
{
  if (max < min)
  {
    throw std::runtime_error("UniformRNG: max value is less then min value");
  }
  return ((value() * (max - min)) + min);
}

void
UniformRNG::reset(int seed)
{
  m_seed = seed;
}


ExponentialRNG::ExponentialRNG(double mean, int seed)
  : m_mean(mean)
  , m_uniform(seed)
{}

ExponentialRNG::~ExponentialRNG()
{}

double
ExponentialRNG::value()
{
  return -log(m_uniform.value()) * m_mean;
}

void
ExponentialRNG::reset(int seed)
{
  m_uniform.reset(seed);
}
