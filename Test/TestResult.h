#ifndef TestResult_H
#define TestResult_H

#include "Observable.h"
#include <list>
#include <sstream>
#include <string>

class AssertResult
{
public:
  std::string file;
  int line;
  std::string assertion;
  bool success;

  AssertResult(const char* file, int line);
  void successful() { success = true; }

  template<class T>
  AssertResult& operator<<(const T& msg)
  {
    std::stringstream oss;
    oss << msg;
    assertion += oss.str();
    return *this;
  }
};

/** A summary of test Results. */
class TestResult : public Observable
{
public:
  /** Results of assertions. (Only used in leaves.) */
  std::list<AssertResult> assertResults;
  /** The names of nestes tests. */
  std::list<std::string> testResultNames;
  /** Nested test results. */
  std::list<TestResult> testResults;
  /** The number of assertions. */
  int total;
  /** The number of successful assertions. */
  int successful;
  /** The number of the last results that have been added without nesting. */
  int lastInserted;

  TestResult()
      : total(0), successful(0), lastInserted(0)
  {}

  /** Appends the results without nesting. */
  void append(TestResult& testResult);
  /** Appends the result with nesting. */
  void append(const char* name, const TestResult& testResult);
  /** Adds the result of an assertion. */
  void add(const AssertResult& assertResult);
  /** Clears all results. */
  void reset();
};

#endif
