#ifndef TextTestRunner_H
#define TextTestRunner_H

#include "TestRunner.h"

class TextTestRunner : public TestRunner
{
  bool verbose;
public:
  TextTestRunner(bool verbose);
  void run(TestCase& testCase);
  void update(Observable* observable);
private:
  /** Generates the report of the last added results. */
  std::string testReportLast(TestResult& testResult, bool verbose, int nested);
};

#endif
