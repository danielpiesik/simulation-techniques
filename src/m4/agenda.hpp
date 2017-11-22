#ifndef AGENDA_HPP
#define AGENDA_HPP

#include <vector>
#include "m4/event.hpp"


class Agenda
{

public:

  Agenda();
  ~Agenda();

  void addEvent(const Event *inEvent);
  const Event* first() const;
  void removeFirst();
  bool isEmpty() const;


private:

  std::vector<const Event*> m_eventsList;

};

#endif // AGENDA_HPP