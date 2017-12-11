#include <string>
#include "stats/statistics.hpp"
#include "metadata/settings.hpp"


TestingTime Statistcs::m_testing_time = TestingTime();
QueueSize Statistcs::m_queue_size = QueueSize();
FailureUtilization Statistcs::m_failure_utilization = FailureUtilization();
SuccessUtilization Statistcs::m_success_utilization = SuccessUtilization();


void
Statistcs::aggregate()
{
  m_queue_size.aggregate();
  m_testing_time.aggregate();
  m_failure_utilization.aggregate();
  m_success_utilization.aggregate();
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

  printf("Average circuit utilized:\n");
  for(unsigned int i = 0; i < TaskSettings.m_numberOfTesters; ++i)
  {
    printf("\t Tester %02d: %.2f +/- %.2f circuits\n", i + 1,
      m_failure_utilization.get(i).mean(),
      m_failure_utilization.get(i).std_dev());
  }

  printf("\n");
}

void
Statistcs::reset()
{
  m_queue_size.reset();
  m_testing_time.reset();
  m_failure_utilization.reset();
  m_success_utilization.reset();
}
