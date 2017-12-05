#ifndef AGENDA_HPP
#define AGENDA_HPP

#include <vector>
#include "m4/event.hpp"
#include "m4/process.hpp"


class Agenda
{

public:

  Agenda();
  ~Agenda();

  void addEvent(Event *inEvent);
  Event* first() const;
  void removeFirst();
  bool isEmpty() const;

  void removeProcess(Process *inProcess);

private:

  std::vector<Event*> m_eventsList;

};

#endif // AGENDA_HPP