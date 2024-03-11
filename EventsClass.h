#ifndef _EVENTSCLASS_TEMPLATE_H_
#define _EVENTSCLASS_TEMPLATE_H_

//The EventsClass for handling diffent Events for the 
//Simulation, including the riderArrival and trainArrival

//the EventType of the EventsClass includes riderArrival
//and trainArrival
enum EventType {riderArrival, trainArrival}; 
class EventsClass
{
  private:
    int time;       //event's time
    EventType type; //event's type
   
  public:
    //constructor for setting up the Events with the time
    //and the type
    EventsClass(int time, EventType type);

    //default constructor for EventsClass
    EventsClass();

    //return the event's type
    EventType getType() const;

    //return the event's time
    int getTime() const;   
};

//overloading the '<' operator for the EventsClass
bool operator < (const EventsClass &e1, const EventsClass &e2);

//overloading the '>' operator for the EventsClass
bool operator > (const EventsClass &e1, const EventsClass &e2);

//overloading the '==' operator for the EventsClass
bool operator == (const EventsClass &e1, const EventsClass &e2);

//overloading the '<<' operator for the EventsClass
ostream& operator << (ostream &os, const EventsClass &e);


#endif //__EVENTSCLASS_TEMPLATE_H_
