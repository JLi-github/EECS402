#include <iostream>
using namespace std;

#include "EventsClass.h"

//constructor for setting up the Events with the time
//and the type
EventsClass::EventsClass(int theTime, EventType theType)
{
  time = theTime;
  type = theType;
}

//default constructor for EventsClass
EventsClass::EventsClass()
{
 ;
}

//return the event's type
EventType EventsClass::getType() const 
{
  return type;
}

//return the event's time
int EventsClass::getTime() const
{
  return time;
}

//overloading the '<' operator for the EventsClass
bool operator < (const EventsClass &e1, const EventsClass &e2) 
{
  return (e1.getTime() < e2.getTime());
}

//overloading the '>' operator for the EventsClass
bool operator > (const EventsClass &e1, const EventsClass &e2)
{
  return (e1.getTime() > e2.getTime());
}

//overloading the '==' operator for the EventsClass
bool operator == (const EventsClass &e1, const EventsClass &e2)
{
  return (e1.getTime() == e2.getTime());
}

//overloading the '<<' operator for the EventsClass
ostream& operator << (ostream &os, const EventsClass &e)
{
  if(e.getType() == trainArrival)
  {
    os << "Event: time | type: " << e.getTime() << " | " << "trainArrival" << endl;
  }

  if(e.getType() == riderArrival)
  {
    os << "Event: time | type: " << e.getTime() << " | " << "riderArrival" << endl;
  }
  
  return (os);
}

