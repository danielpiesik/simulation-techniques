#ifndef EVENT_HPP
#define EVENT_HPP

class Process;


class Event
{
public:

  Event(Process *inProcess);
  ~Event();

  double executeTime() const;
  Process* process() const;

  void setExecuteTime(double time);

private:

  double m_executeTime;
  Process* p_process;

};

#endif // EVENT_HPP