#include <string>
#include <stdarg.h>
#include "logger/logger.hpp"
#include "simulation.hpp"


Logger::Logger(const Verbose &inLevel)
  : m_level(inLevel)
{}

Logger::~Logger()
{}

void
Logger::setLevel(const Verbose &inLevel)
{
  m_level = inLevel;
}

void
Logger::debug(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  print(Verbose::debug, format, args);
  va_end(args);
}

void
Logger::info(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  print(Verbose::info, format, args);
  va_end(args);
}

void
Logger::warning(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  print(Verbose::warning, format, args);
  va_end(args);
}

void
Logger::error(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  print(Verbose::error, format, args);
  va_end(args);
}

void
Logger::critical(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  print(Verbose::critical, format, args);
  va_end(args);
}

void
Logger::print(const Verbose &inLevel, const char *format, va_list args)
{
  if (m_level > inLevel || m_level == Verbose::none)
  {
    return;
  }

  printf("%10.2f [%8.8s]:  ",
        Simulation::instance().simulationTime(),
        levelMessage(inLevel).c_str());
  vfprintf(stdout, format, args);
  printf("\n");
}

std::string
Logger::levelMessage(const Verbose &inLevel)
{
  switch(inLevel)
  {
    case Verbose::debug: return "DEBUG";
    case Verbose::info: return "INFO";
    case Verbose::warning: return "WARNING";
    case Verbose::error: return "ERROR";
    case Verbose::critical: return "CRITICAL";
    default:
    {
      warning("No message for log level: %d", inLevel);
      return "";
    }
  }
}
