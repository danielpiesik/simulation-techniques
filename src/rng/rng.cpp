#include <cmath>
#include <chrono>
#include <cstdlib>
#include <stdexcept>
#include "rng/rng.hpp"


UniformRNG::UniformRNG(double a, double b)
  : m_generator(std::chrono::system_clock::now().time_since_epoch().count())
  , m_distribution(std::uniform_real_distribution<double>(a, b))
{}

UniformRNG::~UniformRNG()
{}

double
UniformRNG::value()
{
  return m_distribution(m_generator);
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
UniformRNG::reset()
{
  m_distribution.reset();
}


ExponentialRNG::ExponentialRNG(double lambda)
  : m_generator(std::chrono::system_clock::now().time_since_epoch().count())
  , m_distribution(std::exponential_distribution<double>(lambda))
{}

ExponentialRNG::~ExponentialRNG()
{}

double
ExponentialRNG::value()
{
  return m_distribution(m_generator);
}

void
ExponentialRNG::reset()
{
  m_distribution.reset();
}


NormalRNG::NormalRNG(double mean, double stddev)
  : m_generator(std::chrono::system_clock::now().time_since_epoch().count())
  , m_distribution(std::normal_distribution<double>(mean, stddev))
{}

NormalRNG::~NormalRNG()
{}

double
NormalRNG::value()
{
  return m_distribution(m_generator);
}

void
NormalRNG::reset()
{
  m_distribution.reset();
}
