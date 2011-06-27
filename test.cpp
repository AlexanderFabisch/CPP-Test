#include "Test/TestSuite.h"
#include "Test/TestCase.h"
#include "Test/QtTestRunner.h"
#include "Test/TextTestRunner.h"

class ExampleTestCase : public TestCase
{
  void run()
  {
    RUN(ExampleTestCase, testFunction);
  }

  void testFunction()
  {
    ASSERT(false);
  }
};

int main(int argc, char** argv)
{
  TestSuite ts("FrameworkTests");
  ts.addTestCase(new ExampleTestCase);

  QtTestRunner qtr(argc, argv);
  qtr.run(ts);

  TextTestRunner ttr(false);
  ttr.run(ts);

  return 0;
}
