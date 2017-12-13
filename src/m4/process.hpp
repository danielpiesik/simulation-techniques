#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "m4/event.hpp"


class Process
{

public:

  Process();
  virtual ~Process();

  virtual void execute() = 0;
  void activate(double time=0.0, bool onTime=false);
  bool isTerminated() const;

protected:

  int m_phase;
  bool m_terminated;

private:

  Event* p_event;

};


#endif // PROCESS_HPP