#ifndef TestCase_H
#define TestCase_H

#include "Assertions.h"
#include "TestResult.h"

#define RUN(TestCaseClass, function) \
        { \
          TestCaseClass tc; \
          tc.setUp(); \
          tc.function(); \
          tc.tearDown(); \
          testResult.append(#TestCaseClass ":" #function, tc.testResult); \
        }

class TestCase
{
public:
  TestResult testResult;

  virtual ~TestCase() {}
  virtual void setUp() {}
  virtual void tearDown() {}
  virtual void run() = 0;
  virtual void reset() { testResult.reset(); }
};

#endif
