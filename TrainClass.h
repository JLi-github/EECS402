#ifndef _TRAINCLASS_TEMPLATE_H_
#define _TRAINCLASS_TEMPLATE_H_

#include "random.h"

//TrainClass for handling the train coming in differnt time
class TrainClass
{
  private:
    int time;  //train arrives time
   
  public:
    //train constructor for assignment of train
    TrainClass(int time); 
    TrainClass(); //default train constructor

    int getTime() const; //return train time
};

#endif //_TRAINCLASS_TEMPLATE_H_
