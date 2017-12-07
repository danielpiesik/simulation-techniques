#include <cmath>
#include <stdexcept>
#include "stats/measure_container.hpp"
#include "stats/students_t_distribution.hpp"
#include "simulation.hpp"


template struct MeasureContainer<int>;
template struct MeasureContainer<double>;
template struct MeasureContainer<float>;


// alpha = 0 -> 0.200
// alpha = 1 -> 0.100
// alpha = 2 -> 0.050
// alpha = 3 -> 0.020
// alpha = 4 -> 0.010
template <typename T>
double MeasureContainer<T>::m_alpha = 2;

template <typename T>
MeasureContainer<T>::MeasureContainer()
{
  reset();
}

template <typename T>
double
MeasureContainer<T>::mean()
{
  double mean = m_aggregate_value / double(m_iter);
  return mean;
}

template <typename T>
double
MeasureContainer<T>::std_dev()
{
  double tmp = sqrt(
      (1.0 / (m_iter - 1))
    * (m_aggregate_value_pow - (m_iter * std::pow(mean(), 2)))
  );
  double std_dev = st_distribution(m_iter - 1, m_alpha) * (tmp / sqrt(m_iter));
  return std_dev;
}

template <typename T>
void
MeasureContainer<T>::aggregate()
{
  T current_value = value();
  m_aggregate_value += current_value;
  m_aggregate_value_pow += std::pow(current_value, 2);
  ++m_iter;
}

template <typename T>
void
MeasureContainer<T>::reset()
{
  m_aggregate_value = static_cast<T>(0.0);
  m_aggregate_value_pow = static_cast<T>(0.0);
  m_iter = 0;
}
