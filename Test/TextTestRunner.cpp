#include "TextTestRunner.h"

#include "Stopwatch.h"
#include <iostream>

TextTestRunner::TextTestRunner(bool verbose)
    : verbose(verbose)
{}

void TextTestRunner::run(TestCase& testCase)
{
  testCase.testResult.attach(this);
  Stopwatch sw;
  testCase.run();
  std::cout << sw.stop() << " mus" << std::endl;
  testCase.testResult.detach(this);
}

void TextTestRunner::update(Observable* observable)
{
  TestResult& testResult = (TestResult&) *observable;
  std::cout << testReportLast(testResult, verbose, 0) << std::endl;
}

std::string TextTestRunner::testReportLast(TestResult& testResult, bool verbose, int nested)
{
  std::stringstream tabStream;
  for(int i = 0; i < nested; i++)
    tabStream << "\t";
  std::string tabs = tabStream.str();

  std::stringstream report;

  std::list<TestResult>::iterator r = testResult.testResults.begin();
  std::list<std::string>::iterator n = testResult.testResultNames.begin();
  for(int i = 0; i < testResult.lastInserted; i++, r++, n++)
    report << tabs << *n << std::endl << testReportLast(*r, verbose, nested+1);

  std::list<AssertResult>::iterator a = testResult.assertResults.begin();
  for(int i = 0; a != testResult.assertResults.end(); i++, a++)
    if(verbose || !a->success)
    {
      report << tabs << i << ". " << a->file << "(" << a->line << ")" << ": "
          << (a->success ? "SUCCESS" : "FAILURE") << " " << a->assertion << std::endl;
    }

  report << tabs << "Successful " << testResult.successful << "/"
      << testResult.total << std::endl;

  return report.str();
}
