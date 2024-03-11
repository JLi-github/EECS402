#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "random.h"
#include "EventsClass.h"
#include "SimulationClass.h"
#include "RiderClass.h"
#include "TrainClass.h"

//Programmer: Jinju Li
//Programming date: 4/11/2018
//Purpose: Generating the Simulation programming with the 
//double linked data structor to mimic the riders and trains 
//in a park. using the pseudo-random numbers for multiple 
//distribution types.

//The main function for the simulation
int main(int argc, char *argv[])
{ 
  ifstream inFile; //The ifstream for the reading of file

  //Set up the simulation class object to do the simulation
  SimulationClass< EventsClass > theSimulation;
  
  //Check if there are errors in the input command line
  if(argc != 2)
  {
    cout << "Usage: " << argv[0] << " <inputFilename>" << endl;  
    return 0; 
  }
  
  //Assigning the file to read in
  string fileName = argv[1];
  
  //Do the initialization of the simulation
  theSimulation.initialization();

  //Loading the simulation file
  theSimulation.loadSimulationFile(fileName.c_str()); 

  //Run the simulation
  theSimulation.runSimulation();

  //Print out the statistics of the simulation
  theSimulation.printStatistics();
  
  return 0;
}
