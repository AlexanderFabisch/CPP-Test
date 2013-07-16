#ifndef Comparisons_H
#define Comparisons_H

#include <cmath>

template<class T>
bool equals(T a, T b, T delta)
{
  return std::fabs(a-b) <= delta;
}

template<class T>
bool isNaN(T value)
{
  return std::isnan(value);
}

template<class T>
bool isInf(T value)
{
  return std::isinf(value);
}

#endif
