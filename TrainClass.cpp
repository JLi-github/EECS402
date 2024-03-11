#include <iostream>
using namespace std;

#include "TrainClass.h"
#include "random.h"

//train constructor for assignment of train
TrainClass::TrainClass(int theTime)
{
  time = theTime;
}

//default train constructor
TrainClass::TrainClass()
{
  ;
}

//return train time at the assignment
int TrainClass::getTime() const
{
  return time;
}

