#ifndef Observer_H
#define Observer_H

class Observable;

class Observer
{
public:
  virtual void update(Observable* observable) = 0;
};

#endif
