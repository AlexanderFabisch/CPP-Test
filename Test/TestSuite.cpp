#include "TestSuite.h"

TestSuite::~TestSuite()
{
  for(std::list<TestCase*>::iterator tc = testCases.begin(); tc != testCases.end(); tc++)
    delete *tc;
  testCases.clear();
}

void TestSuite::run()
{
  reset();
  for(std::list<TestCase*>::iterator tc = testCases.begin(); tc != testCases.end(); tc++)
  {
    (*tc)->setUp();
    (*tc)->run();
    (*tc)->tearDown();
    testResult.append((*tc)->testResult);
  }
}

void TestSuite::reset()
{
  TestCase::reset();
  for(std::list<TestCase*>::iterator tc = testCases.begin(); tc != testCases.end(); tc++)
    (*tc)->reset();
}

void TestSuite::addTestCase(TestCase* testCase)
{
  testCases.push_back(testCase);
}
