#ifndef SETTINGS_HPP
#define SETTINGS_HPP


static struct Time
{
  const int     MINUTE = 1;
  const double  SECOND = MINUTE / 60.0;
  const double  HOUR   = 60 * MINUTE;
} Time;


static struct TaskSettings
{
  const unsigned int m_numberOfTesters = 4;   // N

  const double m_meanAndStdDevForTestingTime[4][2] = {
    {0.3 * Time.MINUTE, 0.01 * Time.MINUTE},
    {0.8 * Time.MINUTE, 0.03 * Time.MINUTE},
    {0.5 * Time.MINUTE, 0.02 * Time.MINUTE},
    {0.6 * Time.MINUTE, 0.01 * Time.MINUTE},
  };

  const double m_circuitInjectionIntervalMean = 2 * Time.MINUTE; // A

  const double m_timeOfRotation = 0.1 * Time.MINUTE; // T

  const double m_minBreakDownTime = 5 * Time.MINUTE; // LB
  const double m_maxBreakDownTime = 10 * Time.MINUTE; // MB

  const double m_breakDownIntervalMean = 30 * Time.MINUTE; // TT

} TaskSettings;


static struct SimulationSettings
{
  const int m_maxSuccessUtilization = 2500;

  const int m_iteration_number = 10;

  const int m_transient_phase_circuits = 500;

} SimulationSettings;


#endif // SETTINGS_HPP
