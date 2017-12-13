#ifndef RNG_HPP
#define RNG_HPP

#include <random>
#include <vector>
#include <string>


template<class T>
class RNG
{

public:

  RNG();
  virtual ~RNG();

  virtual double value();
  virtual void reset();

  virtual void save2file(const std::string &inPath);

protected:

  T m_distribution;

private:

  std::default_random_engine m_generator;
  std::vector<double> m_values;

};


class UniformRNG : public RNG<std::uniform_real_distribution<double>>
{

public:

  UniformRNG(double a = 0.0, double b = 1.0);
  ~UniformRNG();

};


class ExponentialRNG : public RNG<std::exponential_distribution<double>>
{

public:

  ExponentialRNG(double lambda = 1.0);   // lambda = 1 / mean
  ~ExponentialRNG();

};


class NormalRNG : public RNG<std::normal_distribution<double>>
{

public:

  NormalRNG(double mean = 0.0, double stddev = 1.0);
  ~NormalRNG();

};

#endif // RNG_HPP
