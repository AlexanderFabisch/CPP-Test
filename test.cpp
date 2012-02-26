#include "Test/TestSuite.h"
#include "Test/TestCase.h"
#include "Test/TextTestRunner.h"
#ifdef CPPTEST_USE_QT
#include "Test/QtTestRunner.h"
#endif

class ExampleTestCase : public TestCase
{
  void setUp() { /* do some stuff here before each test function */ }
  void tearDown() { /* do some stuff here after each test function */ }

  void run()
  {
    RUN(ExampleTestCase, testFunction1);
    RUN(ExampleTestCase, testFunction2);
  }

  void testFunction1()
  {
    ASSERT(false);
    double a = 0.0, b = 0.5;
    ASSERT_EQUALS(a, b);
    ASSERT_NOT_EQUALS(a, b);
    ASSERT_EQUALS_DELTA(a, b, 1.0);
    ASSERT_WITHIN(a, -1.0, 1.0);
  }

  void testFunction2()
  {
    double c = 0.0;
    ASSERT(isNaN(c/c));
    ASSERT(isInf(c));
  }
};

int main(int argc, char** argv)
{
  TestSuite ts("FrameworkTests");
  ts.addTestCase(new ExampleTestCase);

  TextTestRunner ttr(false);
  ttr.run(ts);

#ifdef CPPTEST_USE_QT
  QtTestRunner qtr(argc, argv);
  qtr.run(ts);
#endif

  return 0;
}
