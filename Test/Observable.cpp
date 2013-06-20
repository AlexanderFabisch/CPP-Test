#include "Observable.h"

void Observable::attach(Observer* observer)
{
  observers.push_back(observer);
}

void Observable::detach(Observer* observer)
{
  observers.remove(observer);
}

void Observable::notify()
{
  for(std::list<Observer*>::iterator observer = observers.begin(); observer != observers.end(); ++observer)
    (*observer)->update(this);
}
