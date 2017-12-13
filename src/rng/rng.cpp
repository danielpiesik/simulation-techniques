#include <cmath>
#include <chrono>
#include <cstdlib>
#include <stdexcept>
#include "rng/rng.hpp"

template struct RNG<std::uniform_real_distribution<double>>;
template struct RNG<std::exponential_distribution<double>>;
template struct RNG<std::normal_distribution<double>>;


template<class T>
RNG<T>::RNG()
 : m_distribution(T())
 , m_generator(std::chrono::system_clock::now().time_since_epoch().count())
{}

template<class T>
RNG<T>::~RNG()
{}

template<class T>
double
RNG<T>::value()
{
  double val = m_distribution(m_generator);
  return val;
}

template<class T>
void
RNG<T>::reset()
{
  m_distribution.reset();
}


UniformRNG::UniformRNG(double a, double b)
{
  m_distribution = std::uniform_real_distribution<double>(a, b);
}

UniformRNG::~UniformRNG()
{}


ExponentialRNG::ExponentialRNG(double lambda)
{
  m_distribution = std::exponential_distribution<double>(lambda);
}

ExponentialRNG::~ExponentialRNG()
{}


NormalRNG::NormalRNG(double mean, double stddev)
{
  m_distribution = std::normal_distribution<double>(mean, stddev);
}

NormalRNG::~NormalRNG()
{}
