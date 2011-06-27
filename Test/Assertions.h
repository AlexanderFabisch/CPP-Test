#ifndef Assertions_H
#define Assertions_H

#include "Comparisons.h"

#define ASSERT(x) \
        { \
          AssertResult result(__FILE__, __LINE__); \
          result << (#x); \
          if((x)) result.successful(); \
          testResult.add(result); \
        }

#define ASSERT_EQUALS(x, y) \
        { \
          AssertResult result(__FILE__, __LINE__); \
          result << (#x) << " == " << (#y) << "\n" << (x) << "\n == \n" << (y); \
          if((x) == (y)) result.successful(); \
          testResult.add(result); \
        }

#define ASSERT_NOT_EQUALS(x, y) \
        { \
          AssertResult result(__FILE__, __LINE__); \
          result << (#x) << " != " << (#y) << "\n" << (x) << "\n != \n" << (y); \
          if((x) != (y)) result.successful(); \
          testResult.add(result); \
        }

#define ASSERT_EQUALS_DELTA(x, y, delta) \
        { \
          AssertResult result(__FILE__, __LINE__); \
          result << (#x) << " == " << (#y) << "\n" << (x) << "\n == \n" << (y) << "\n+- " << (delta); \
          if(equals((x), (y), (delta))) result.successful(); \
          testResult.add(result); \
        }

#define ASSERT_WITHIN(x, lower, upper) \
        { \
          AssertResult result(__FILE__, __LINE__); \
          result << (#x) << " : " << x << " in [" << (#lower) << "," << (#upper) << "]"; \
          if((x) >= (lower) && (x) <= (upper)) result.successful(); \
          testResult.add(result); \
        }

#endif
