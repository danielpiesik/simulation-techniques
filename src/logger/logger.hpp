#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <stdio.h>
#include <stdarg.h>


enum class Verbose
{
  debug,
  info,
  warning,
  error,
  critical,
  none
};


class Logger
{
public:

  Logger(const Verbose &inLevel = Verbose::debug);
  ~Logger();

  void setLevel(const Verbose &inlevel);

  void debug(const char *format, ...);
  void info(const char *format, ...);
  void warning(const char *format, ...);
  void error(const char *format, ...);
  void critical(const char *format, ...);

private:

  Verbose m_level;

  void print(const Verbose &inLevel, const char *format, va_list args);
  std::string levelMessage(const Verbose &inLevel);

};


#endif // LOGGER_HPP
