#include <iostream>
using namespace std;

#include "RiderClass.h"
#include "random.h"

//The RiderClass constructor handle the riders with their time and 
//different of types
RiderClass::RiderClass(int theTime, RiderType theType)
{
  time = theTime;
  type = theType;
}

//default RiderClass constructor
RiderClass::RiderClass()
{
  ;
}

//return the type of the RiderClass object
RiderType RiderClass::getType() const 
{
  return type;
}

//return the time of the RiderClass object
int RiderClass::getTime() const
{
  return time;
}

//set up the types of RiderClass object
void RiderClass::setType(double &num1, double &num2)
{
  int riderType = getUniform(0, 100);
 
  if((100 - num1) < riderType && (riderType < 100 || riderType == 100))
  {
    type = superFastPass;
  }

  else if(((100 - num1 - num2) < riderType
                  && riderType < (100 - num1)) || 
                  riderType == (100 - num1))
  {
    type = fastPass;
  }
    
  else if(riderType < (100 - num1 - num2) || 
          riderType == (100 - num1 - num2))
  {
    type = standardPass;
  }
}

//overload the "<<" for output of the RiderClass object
ostream& operator << (ostream &os, const RiderClass &r)
{
  if(r.getType() == superFastPass)
  {
    os << "Event: time | type: " << r.getTime() << " | " << "superFastPass" << endl;
  }

  else if(r.getType() == fastPass)
  {
    os << "Event: time | type: " << r.getTime() << " | " << "fastPass" << endl;
  }

   else if(r.getType() == standardPass)
  {
    os << "Event: time | type: " << r.getTime() << " | " << "standardPass" << endl;
  }
  
  return (os);
}
