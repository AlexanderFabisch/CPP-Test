#ifndef Comparisons_H
#define Comparisons_H

#include <cmath>

template<class T>
bool equals(T a, T b, T delta)
{
  return fabs(a-b) <= delta;
}

template<class T>
bool isNaN(T value)
{
  return isnan(value);
}

template<class T>
bool isInf(T value)
{
  return isinf(value);
}

#endif
