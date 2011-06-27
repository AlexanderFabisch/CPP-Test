#ifndef TestRunner_H
#define TestRunner_H

#include "TestCase.h"
#include "Observer.h"

class TestRunner : public Observer
{
public:
  virtual void run(TestCase& testCase) = 0;
};

#endif
