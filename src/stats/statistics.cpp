#include <string>
#include "stats/statistics.hpp"


TestingTime Statistcs::m_testing_time = TestingTime();
QueueSize Statistcs::m_queue_size = QueueSize();

void
Statistcs::aggregate()
{
  m_queue_size.aggregate();
  m_testing_time.aggregate();
}

void
Statistcs::print()
{
  std::string separate = "****************************************************";

  printf("\n%s\n", separate.c_str());

  printf("Average queue size: %.2f +/- %.2f circuits\n",
         m_queue_size.mean(), m_queue_size.std_dev());
  printf("Average testing time: %.2f +/- %.2f minutes\n",
         m_testing_time.mean(), m_testing_time.std_dev());
  printf("\n");
}

void
Statistcs::reset()
{
  m_queue_size.reset();
  m_testing_time.reset();
}
