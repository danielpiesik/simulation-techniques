#ifndef MEASURE_CONTAINER_HPP
#define MEASURE_CONTAINER_HPP


template <typename T>
struct MeasureContainer
{

public:

  MeasureContainer();

  void aggregate();
  void reset();

  virtual T value() = 0;
  double mean();
  double std_dev();

private:

  T m_aggregate_value;
  T m_aggregate_value_pow;
  int m_iter;

  static double m_alpha;
};


#endif // MEASURE_CONTAINER_HPP
