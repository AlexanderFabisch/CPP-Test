#include "TestResult.h"

AssertResult::AssertResult(const char* file, int line)
  : file(file), line(line), assertion(), success(false)
{
  size_t s = this->file.rfind("/");
  if(s != std::string::npos && s + 1 != this->file.size())
    this->file = this->file.substr(s + 1);
}

void TestResult::append(TestResult& testResult)
{
  if(testResult.testResultNames.size() > 0)
  {
    lastInserted = 1;
    std::string name = testResult.testResultNames.front();
    size_t s = name.find(":");
    if(s != std::string::npos)
    {
      name = name.substr(0, s);
      for(std::list<std::string>::iterator n = testResult.testResultNames.begin(); n != testResult.testResultNames.end(); n++)
        if(n->size() > s)
          *n = n->substr(s+1);
    }
    testResultNames.push_front(name);
    testResults.push_front(testResult);
    total += testResult.total;
    successful += testResult.successful;
    notify();
  }
}

void TestResult::append(const char* name, const TestResult& testResult)
{
  testResultNames.push_back(std::string(name));
  testResults.push_back(testResult);
  total += testResult.total;
  successful += testResult.successful;
  lastInserted++;
  notify();
}

void TestResult::add(const AssertResult& assertResult)
{
  total++;
  if(assertResult.success)
    successful++;
  assertResults.push_back(assertResult);
  notify();
}

void TestResult::reset()
{
  testResultNames.clear();
  testResults.clear();
  assertResults.clear();
  successful = 0;
  total = 0;
}
