#ifndef TABLE_HPP
#define TABLE_HPP

#include <vector>
#include <memory>
#include "resources/tester.hpp"


class Table
{

public:

  Table();
  ~Table();

  void addTester(Tester *inTester);

  std::vector<std::shared_ptr<Tester>>& testers();

private:

  std::vector<std::shared_ptr<Tester>> m_testers;

};


#endif // TABLE_HPP
