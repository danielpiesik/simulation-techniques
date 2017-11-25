#ifndef RNG_HPP
#define RNG_HPP

#include <random>


class UniformRNG
{

public:

  UniformRNG(int seed);
  ~UniformRNG();

  double value();
  double value(double min, double max);
  void reset();

private:

  int m_seed;

};


class ExponentialRNG
{

public:

  ExponentialRNG(double mean, int seed);   // mean = 1 / lambda
  ~ExponentialRNG();

  double value();
  void reset();

private:

  double m_mean;
  UniformRNG m_uniform;

};


class NormalRNG
{

public:

  NormalRNG(double mean, double variance);
  ~NormalRNG();

  double value();
  void reset();

private:

  std::default_random_engine m_generator;
  std::normal_distribution<double> m_distribution;

};

#endif // RNG_HPP
