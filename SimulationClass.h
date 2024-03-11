#ifndef _SIMULATIONCLASS_TEMPLATE_H_
#define _SIMULATIONCLASS_TEMPLATE_H_

#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "EventsClass.h"
#include "random.h"
#include "RiderClass.h"
#include "TrainClass.h"

//Const number for the train's seat number
const int TRAIN_SEAT = 20;  

//The simulation class for setting up the simulation and run 
//the simulation and printing out the simulaiton results
template < class T >
class SimulationClass
{
  private:
    string attractionName;  //The name of attraction in the simulation

    //Park closing time: No additional rider arrivals will be 
    //allowed after this time
    double closingTime; 

    //Rider arrival rate normal distribution mean: Riders have
    //been determined to arrive at the attraction in a normally distributed 
    //way. This value is the mean of that normal distribution.    
    double riderArrivalMean;  

    //Rider arrival rate normal distribution standard deviation
    double riderArrivalStddev;
    
    //Car arrival rate uniform distribution minimum value
    double carArrivalMin;

    //Car arrival rate uniform distribution maximum value
    double carArrivalMax;

    //What percentage of the riders have purchased super fast pass access
    double percentageSFP;

    //What percentage of the riders have purchased fast pass access
    double percentageFP;

    //The ideal number of riders from the super fast pass access line 
    //that are admitted for a run of the ride
    int numSFPAdmitted;

    //The ideal number of riders from the fast pass access line 
    //that are admitted for a run of the ride
    int numFPAdmitted;

    //The total number of riders in the simulation
    double numTotalRider;

    //The total number of trains in the simulation
    double numTotalTrain; 

    //The total waitime of superFastPass riders, this is for 
    //generating of the average waiting time of superFastPass riders
    double totalWaitTimeSFP;  

    //The total waitime of fastPass riders, this is for 
    //generating of the average waiting time of fastPass riders
    double totalWaitTimeFP;  

    //The total waitime of standardP riders, this is for 
    //generating of the average waiting time of standardP riders
    double totalWaitTimeStandP;

    //The maxmium of waiting time for a rider
    double maxWaitTimeRider;

    //The total waitime of any riders, this is for 
    //generating of the average waiting time of all riders
    double totalWaitTimeRider;

    //Number of superFastPass riders in the simulation
    int numSuperFP; 

    //Number of fastPass riders in the simulation
    int numFastP;    

    //Number of standardP riders in the simulation
    int numStandardP;

    //The totally addimitted riders by the train
    int numTrainAdmitted;

    //The maximum waiting time for the superFastPass rider
    int maxWaitTimeSFP;

    //The maximum waiting time for the fastPass rider
    int maxWaitTimeStandP;

    //The maximum waiting time for the standardP rider
    int maxWaitTimeFP;

    //The maximum length of the superFastPass rider
    int maxSFPLgth;

    //The maximum length of the fastPass rider
    int maxFPLgth;

    //The maximum length of the standardP rider
    int maxStandPLgth;


    //Set up the SortedListClass data structor for generating 
    //storing, handling the events for the simulation
    SortedListClass< EventsClass > eventList;

    //Set up the FIFOQueue class for storing the rider events 
    //of the superFastPass rider
    FIFOQueueClass< EventsClass > superFP;

    //Set up the FIFOQueue class for storing the rider events 
    //of the fastPass rider
    FIFOQueueClass< EventsClass > fastP;

    //Set up the FIFOQueue class for storing the rider events 
    //of the standardP rider
    FIFOQueueClass< EventsClass > standardP;

    //Set up the FIFOQueue class for storing the train events 
    FIFOQueueClass< TrainClass > train;

    EventsClass currentEvent;   //Set up the currentEvent
    EventsClass lastEvent;      //Set up the lastEvent
    EventsClass nextEvent;      //Set up the nextEvent
    RiderClass theRider;        //Set up the rider
    TrainClass theTrain;        //Set up the train 
    TrainClass lastTrain;       //Set up the train for calling 
                                //the dequeued train

  public:
    //Initialization the parameters and make the seeding of the
    //simulation
    void initialization();

    //Load the file to get the parameters for the simulation
    void loadSimulationFile(const char *fileName);

    //The ride takes some amount of time to arrive the attraction, additional 
    //riders may arrive and get in the appropriate line. When a train
    // of cars arrives at the station, the next set of riders is
    // admitted and the process continues until the park closes.
    void runSimulation();

    //A function in handling the Events that pseudo-randomly 
    //determined using a given distribution, generates the “next” rider 
    //arrival event each time a rider arrives at the attraction and 
    //that particular event is handled. At the time you handle a 
    //rider’s arrival event, determine how far in the future the
    // next rider arrival event occurs using the distribution and 
    //parameters specified.
    void handleEvent(const EventsClass &e);

    //The park currently has three levels of priority: “Standard”, 
    //“Fast Pass”, and “Super Fast Pass” Attractions at our park have 
    //a separate line that riders must stand in for each priority.
    //If the ideal number of each priority level rider is not able to 
    //fill up the car, we take as many SFP riders as available to fill 
    //up the car. If there aren’t enough SFP riders to fill it, we take
    //as many FP riders are needed. Finally, if there are not enough SFP
    //or FP riders, the car is filled up with STD riders.
    void getOnTrain(const EventsClass &e);

    //Print out the statistics of the simulation, including the 
    //Total Riders arrival number, Rider Rrrive's Rate,Total Train's 
    //Arrival number, Train Arrive's Rate, Average Wait Time of Riders,
    //Maximum Wait Time of Riders, Average Number of Riders
    //on Each Train, Percentage Riders Filled on Each Train, and also
    //related parameter for superFastPass, fastPass, standardP riders.
    void printStatistics();
};

#include "SimulationClass.inl"
#endif //_SIMULATIONCLASS_TEMPLATE_H_