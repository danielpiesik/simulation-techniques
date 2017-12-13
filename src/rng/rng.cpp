#include <cmath>
#include <chrono>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "rng/rng.hpp"

template struct RNG<std::uniform_real_distribution<double>>;
template struct RNG<std::exponential_distribution<double>>;
template struct RNG<std::normal_distribution<double>>;


template<class T>
RNG<T>::RNG()
 : m_distribution(T())
 , m_generator(std::chrono::system_clock::now().time_since_epoch().count())
 , m_values(std::vector<double>())
{}

template<class T>
RNG<T>::~RNG()
{}

template<class T>
double
RNG<T>::value()
{
  double val = m_distribution(m_generator);
  m_values.push_back(val);
  return val;
}

template<class T>
void
RNG<T>::reset()
{
  m_distribution.reset();
  m_values.clear();
}

template<class T>
void
RNG<T>::save2file(const std::string &inFileName)
{
  std::string dir_str = "output/distributions";

  std::ofstream file;
  file.open(dir_str + "/" + inFileName,
            std::ios_base::out | std::ios_base::trunc);
  for(auto &value : m_values)
    file << value << std::endl;
  file.close();
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
