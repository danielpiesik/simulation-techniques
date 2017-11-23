#ifndef RNG_HPP
#define RNG_HPP


class UniformRNG
{

public:

  UniformRNG(int seed);
  ~UniformRNG();

  double value();
  double value(double min, double max);
  void reset(int seed);

// private:

  int m_seed;

};


class ExponentialRNG
{

public:

  ExponentialRNG(double mean, int seed);   // mean = 1 / lambda
  ~ExponentialRNG();

  double value();
  void reset(int seed);

// private:

  double m_mean;
  UniformRNG m_uniform;

};


#endif // RNG_HPP
