#ifndef _RIDERCLASS_TEMPLATE_H_
#define _RIDERCLASS_TEMPLATE_H_

#include "random.h"

//RiderClass for handling of different rider's type and 
//time
enum RiderType {superFastPass, fastPass, standardPass};
class RiderClass
{
  private:
    int time;       //the RiderClass object time
    RiderType type; //the RiderClass object type
   
  public:
    //The RiderClass constructor handle the riders with their time and 
    //different of types.
    RiderClass(int time, RiderType type);
    RiderClass(); //default RiderClass constructor

    //return the type of the RiderClass object
    RiderType getType() const;

    //set up the types of RiderClass object
    void setType(double &percentageSFP, double &percentageFP);

    //return the time of the RiderClass object
    int getTime() const;
};

//overload the "<<" for output of the RiderClass object.
ostream& operator << (ostream &os, const RiderClass &r);

#endif //__RIDERCLASS_TEMPLATE_H_
