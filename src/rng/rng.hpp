#ifndef RNG_HPP
#define RNG_HPP

#include <random>


class UniformRNG
{

public:

  UniformRNG(double a = 0.0, double b = 1.0);
  ~UniformRNG();

  double value();
  double value(double min, double max);
  void reset();

private:

  std::default_random_engine m_generator;
  std::uniform_real_distribution<double> m_distribution;

};


class ExponentialRNG
{

public:

  ExponentialRNG(double lambda = 1.0);   // lambda = 1 / mean
  ~ExponentialRNG();

  double value();
  void reset();

private:

  std::default_random_engine m_generator;
  std::exponential_distribution<double> m_distribution;

};


class NormalRNG
{

public:

  NormalRNG(double mean = 0.0, double stddev = 1.0);
  ~NormalRNG();

  double value();
  void reset();

private:

  std::default_random_engine m_generator;
  std::normal_distribution<double> m_distribution;

};

#endif // RNG_HPP
