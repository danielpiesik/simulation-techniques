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
  const unsigned int m_numberOfTesters = 3;   // N
  const double m_timeOfRotation = 1 * Time.MINUTE; // T

  const double m_minBreakDownTime = 1 * Time.MINUTE; // LB
  const double m_maxBreakDownTime = 10 * Time.MINUTE; // MB

} TaskSettings;


static struct SimulationSettings
{
  const int a = 0; // TODO: remove it. It is only for silencing warning

} SimulationSettings;


static struct GeneratorsSettings
{
  const double circuit_generator_mean = 1; // A

} GeneratorsSettings;


#endif // SETTINGS_HPP
