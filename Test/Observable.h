#ifndef Observable_H
#define Observable_H

#include "Observer.h"
#include <list>

class Observable
{
  std::list<Observer*> observers;
public:
  void attach(Observer* observer);
  void detach(Observer* observer);
  void detachAll();
  void notify();
};

#endif
