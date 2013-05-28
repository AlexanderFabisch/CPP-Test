#ifndef TestSuite_H
#define TestSuite_H

#include "TestCase.h"
#include <list>
#include <string>

class TestSuite : public TestCase
{
  std::string name;
  std::list<TestCase*> testCases;
public:
  TestSuite(const char* name) : name(name) {}
  virtual ~TestSuite();
  virtual void run();
  virtual void reset();
  void addTestCase(TestCase* testCase);
};

#endif
