#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include "m4/process.hpp"


enum class Phase : unsigned int
{
  injection = 0,
  waiting_in_queue,
};


class Circuit: public Process
{

public:

  Circuit();
  ~Circuit();

  virtual void execute();

private:

  void injection();

};


#endif // CIRCUIT_HPP
