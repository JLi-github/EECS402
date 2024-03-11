
template< class T >
void SimulationClass< T >::initialization()
{
  string attractionName = "Space Mountain";
  closingTime = 0;
  riderArrivalMean = 0;
  riderArrivalStddev = 0;
  carArrivalMin = 0;
  carArrivalMax = 0;
  percentageSFP = 0;
  percentageFP = 0;
  numSFPAdmitted = 0;
  numFPAdmitted = 0;
  numTotalRider = 0;
  numTotalTrain = 0;
  numTrainAdmitted = 0;
  maxSFPLgth = 0;
  maxFPLgth = 0;
  maxStandPLgth = 0;
  totalWaitTimeSFP = 0;  
  totalWaitTimeFP = 0;  
  totalWaitTimeStandP = 0;
  totalWaitTimeRider = 0;
  numSuperFP = 0; 
  numFastP = 0;    
  numStandardP = 0;
  maxWaitTimeSFP = 0;
  maxWaitTimeStandP = 0;
  maxWaitTimeFP = 0;
  maxWaitTimeRider = 0;

  int seed;
  cout << "Enter seed: ";
  cin >> seed;
  setSeed(seed);
  cout << endl;
}

template< class T >
void SimulationClass< T >::loadSimulationFile(const char *fileName) 
{   
  ifstream inFile; 
  inFile.open(fileName);

  if(inFile.fail())
  {
    cout << "Invalid file to open, loads again" << endl;
  }

  if(!inFile.fail())
  {
    inFile >> closingTime;
    inFile >> riderArrivalMean;
    inFile >> riderArrivalStddev;
    inFile >> carArrivalMin;
    inFile >> carArrivalMax;
    inFile >> percentageSFP;
    inFile >> percentageFP;
    inFile >> numSFPAdmitted;
    inFile >> numFPAdmitted;
  }
}   

template< class T >  
void SimulationClass< T >::runSimulation()
{ 
  int riderSchedule;
  int trainSchedule;

  cout << "Simulation begins: " << "\n" << endl;

  if(eventList.getNumElems() == 0)
  {
    riderSchedule = getNormal(riderArrivalMean, riderArrivalStddev);
    currentEvent = EventsClass(riderSchedule, riderArrival);
    eventList.insertValue(currentEvent);

    trainSchedule = getUniform(carArrivalMin, carArrivalMax);
    currentEvent = EventsClass(trainSchedule, trainArrival);
    eventList.insertValue(currentEvent);
    theTrain = TrainClass(trainSchedule);
    train.enqueue(theTrain);
  }

  do
  { 
    eventList.removeFront(currentEvent);
    handleEvent(currentEvent);  

  } while(currentEvent.getTime() != 0 && currentEvent.getTime() < closingTime);

  if(superFP.getNumElems() + fastP.getNumElems() + standardP.getNumElems() > 0)
  {
    while((superFP.getNumElems() + fastP.getNumElems() + 
                                   standardP.getNumElems()) > 0)
    { 
      trainSchedule = lastTrain.getTime() + getUniform(carArrivalMin,
                                                          carArrivalMax);
      currentEvent = EventsClass(trainSchedule, trainArrival);
      handleEvent(currentEvent);
    }
  }
}

template< class T >
void SimulationClass< T >::handleEvent(const EventsClass &e)
{
  int riderSchedule;
  int trainSchedule;

  if(currentEvent.getType() == riderArrival)
  {
    riderSchedule = currentEvent.getTime() + getNormal(riderArrivalMean,
                                                      riderArrivalStddev);
    nextEvent = EventsClass(riderSchedule, riderArrival);
    eventList.insertValue(nextEvent);
    numTotalRider++;
    cout << "At Time: " << currentEvent.getTime();

    theRider.setType(percentageSFP, percentageFP);

    if(theRider.getType() == superFastPass)
    {
      superFP.enqueue(currentEvent);
      cout << " SuperFP arrives. ";
      cout << "Current Length of superFP: " << superFP.getNumElems();
      cout << "\n" << endl;
      numSuperFP++;
    }

    if(theRider.getType() == fastPass)
    {
      fastP.enqueue(currentEvent);
      cout << " FastP arrives. ";
      cout << "Current Length of fastP: " << fastP.getNumElems();
      cout << "\n" << endl;
      numFastP++;
    }
      
    if(theRider.getType() == standardPass)
    {
      standardP.enqueue(currentEvent); 
      cout << " StandardP arrives. ";
      cout << "Current Length of standP: " << standardP.getNumElems();
      cout << "\n" << endl;
      numStandardP++;
    }
  }

  else if(currentEvent.getType() == trainArrival)
  {
    trainSchedule = currentEvent.getTime() + getUniform(carArrivalMin, 
                                                        carArrivalMax);
    nextEvent = EventsClass(trainSchedule, trainArrival);
    eventList.insertValue(nextEvent);
    theTrain = TrainClass(trainSchedule);
    train.enqueue(theTrain);
    numTotalTrain++;
    getOnTrain(currentEvent); 
    train.dequeue(lastTrain);
  }
}

template< class T >
void SimulationClass< T >::getOnTrain(const EventsClass &e)
{
  int trainAd = TRAIN_SEAT;
  int minNum;
  int numSuperFPOnTN = 0;
  int numFastPOnTN = 0;
  int numStandardPOnTN = 0;
  double waitTimeSFP;
  double waitTimeFP;
  double waitTimeStandP;

  cout << "At Time: " << currentEvent.getTime() << " Train arrives, ";
  cout<< "Total: superFP (" << superFP.getNumElems() << "); fastP (";
  cout << fastP.getNumElems() << ") standardP (" << standardP.getNumElems();
  cout << ")" << endl;

  minNum = min(superFP.getNumElems(), numSFPAdmitted);
  for(int i = 0; i < minNum; i++) 
  {
    if(maxSFPLgth < superFP.getNumElems())
    {
      maxSFPLgth = superFP.getNumElems();
    }

    superFP.dequeue(lastEvent);
    waitTimeSFP = currentEvent.getTime() - lastEvent.getTime();
    totalWaitTimeSFP += waitTimeSFP;
    totalWaitTimeRider += waitTimeSFP;
    numSuperFPOnTN++;

    if(maxWaitTimeSFP < waitTimeSFP)
    {
      maxWaitTimeSFP = waitTimeSFP;
    }

    if(maxWaitTimeRider < waitTimeSFP)
    {
      maxWaitTimeRider = waitTimeSFP;
    }

    numTrainAdmitted++;
    trainAd--;
  }

  minNum = min(fastP.getNumElems(), numFPAdmitted);
  for(int i = 0; i < minNum; i++) 
  {
    if(maxFPLgth < fastP.getNumElems())
    {
      maxFPLgth = fastP.getNumElems();
    }

    fastP.dequeue(lastEvent);
    waitTimeFP = currentEvent.getTime() - lastEvent.getTime();
    totalWaitTimeFP += waitTimeFP;
    totalWaitTimeRider += waitTimeFP;
    numFastPOnTN++;

    if(maxWaitTimeFP < waitTimeFP)
    {
      maxWaitTimeFP = waitTimeFP;
    }

    if(maxWaitTimeRider < waitTimeFP)
    {
      maxWaitTimeRider = waitTimeFP;
    }

    numTrainAdmitted++;
    trainAd--;
  }

  minNum = min(standardP.getNumElems(), TRAIN_SEAT - numSFPAdmitted 
                                                   - numFPAdmitted);
  for(int i = 0; i < minNum; i++) 
  {
    if(maxStandPLgth < standardP.getNumElems())
    {
      maxStandPLgth = standardP.getNumElems();
    }

    standardP.dequeue(lastEvent);
    waitTimeStandP = currentEvent.getTime() - lastEvent.getTime();
    totalWaitTimeStandP += waitTimeStandP;
    totalWaitTimeRider += waitTimeStandP;
    numStandardPOnTN++;

    if(maxWaitTimeStandP < waitTimeStandP)
    {
      maxWaitTimeStandP = waitTimeStandP;
    }

    if(maxWaitTimeRider < waitTimeStandP)
    {
      maxWaitTimeRider = waitTimeStandP;
    }

    numTrainAdmitted++;
    trainAd--;
  }
  
  minNum = min(superFP.getNumElems(), trainAd);
  for (int i = 0; i < minNum; i++) 
  {
    superFP.dequeue(lastEvent);
    waitTimeSFP = currentEvent.getTime() - lastEvent.getTime();
    totalWaitTimeSFP += waitTimeSFP;
    totalWaitTimeRider += waitTimeSFP;
    numSuperFPOnTN++;
    
    if(maxWaitTimeSFP < waitTimeSFP)
    {
      maxWaitTimeSFP = waitTimeSFP;
    }
    
    if(maxWaitTimeRider < waitTimeSFP)
    {
      maxWaitTimeRider = waitTimeSFP;
    }

    numTrainAdmitted++;
    trainAd--;
  }

  minNum = min(fastP.getNumElems(), trainAd);
  for (int i = 0; i < minNum; i++) 
  {
    fastP.dequeue(lastEvent);
    waitTimeFP = currentEvent.getTime() - lastEvent.getTime();
    totalWaitTimeFP += waitTimeFP;
    totalWaitTimeRider += waitTimeFP;
    numFastPOnTN++;

    if(maxWaitTimeFP < waitTimeFP)
    {
      maxWaitTimeFP = waitTimeFP;
    }

    if(maxWaitTimeRider < waitTimeFP)
    {
      maxWaitTimeRider = waitTimeFP;
    }

    numTrainAdmitted++;
    trainAd--;
  }

  minNum = min(standardP.getNumElems(), trainAd);
  for (int i = 0; i < minNum; i++) 
  {
    standardP.dequeue(lastEvent);
    waitTimeStandP = currentEvent.getTime() - lastEvent.getTime();
    totalWaitTimeStandP += waitTimeStandP;
    totalWaitTimeRider += waitTimeStandP;
    numStandardPOnTN++;

    if(maxWaitTimeStandP < waitTimeStandP)
    {
      maxWaitTimeStandP = waitTimeStandP;
    }

    if(maxWaitTimeRider < waitTimeStandP)
    {
      maxWaitTimeRider = waitTimeStandP;
    }

    numTrainAdmitted++;
    trainAd--;
  }
  
  int totalROTN = numSuperFPOnTN + numFastPOnTN + numStandardPOnTN;

  cout << "Total getting on Train: superFP (" << numSuperFPOnTN;
  cout << ") fastP (" << numFastPOnTN << ") standardP (";
  cout << numStandardPOnTN << ")" << endl;
  cout << "Train leaves. Total left: superFP (" << superFP.getNumElems();
  cout << ") fastP (" << fastP.getNumElems() << ") standardP (";
  cout << standardP.getNumElems() << ")" << endl;
  cout << "Percentage of train is filled: ";
  cout << (double(totalROTN)/double(TRAIN_SEAT)) * 100;
  cout << "\n" << endl;
}

template< class T >
void SimulationClass< T >::printStatistics() 
{
  cout << "Simulation Ends!" << "\n" << endl;
  cout << "Final Statistics:" << endl;
  cout << "Total Riders arrival: " << numTotalRider << endl;
  cout << "Rider Rrrive's Rate: " << numTotalRider/closingTime << endl;
  cout << "Total Trains Arrival: " << numTotalTrain << endl;
  cout << "Train Arrive's Rate: " << numTotalTrain/closingTime << endl;
  cout << "Average time interval between train: ";
  cout << closingTime/numTotalTrain << endl;
  cout << "Average Wait Time of Riders: ";
  cout << totalWaitTimeRider/numTotalRider << endl;
  cout << "Maximum Wait Time of Rider: ";
  cout << maxWaitTimeRider << endl;
  cout << "Average Number of Riders on Each Train: " ;
  cout << double(numTrainAdmitted/numTotalTrain) << endl;
  cout << "Percentage Riders Filled on Each Train: ";
  cout << double(numTrainAdmitted/numTotalTrain)/double(TRAIN_SEAT) * 100;
  cout << "\n" << endl;

  cout << "Total Number of SuperFastPass Rider: " << numSuperFP << endl;
  cout << "Actual Percentage of SuperFastPass Rider: ";
  cout << numSuperFP/numTotalRider * 100 << endl;
  cout << "Average Wait Time of superFastPass rider: ";
  cout << totalWaitTimeSFP/numSuperFP << endl;
  cout << "Maximum Wait Time of SuperFastPass Rider: "<< maxWaitTimeSFP << endl;
  cout << "Maximun Length of SuperFastPass Rider: " << maxSFPLgth << endl;
  cout << "Average Number of SuperFastPass Rider on Each Train: ";
  cout << numSuperFP/numTotalTrain << endl;
  cout << "Percentage of SuperFastPass Rider Filled on Each Train: ";
  cout << (numSuperFP/numTotalTrain) / TRAIN_SEAT * 100 << "\n" << endl;

  cout << "Total Number of FastPass Rider: " << numFastP << endl;
  cout << "Actual Percentage of FastPass Rider: ";
  cout << numFastP/numTotalRider * 100 << endl;
  cout << "Average Wait Time of FastPass Rider: ";
  cout << totalWaitTimeFP/numFastP << endl;
  cout << "Maximum Wait Time of FastPass Rider: " << maxWaitTimeStandP << endl;
  cout << "Maximun Length of FastPass Fider: " << maxFPLgth << endl;
  cout << "Average Number of FastPass Rider on Each Train: ";
  cout << numFastP/numTotalTrain << endl;
  cout << "Percentage of FastPass Rider Filled on Each Train: ";
  cout << (numFastP/numTotalTrain) / TRAIN_SEAT * 100 << "\n" << endl;

  cout << "Total Number of StandardPass Rider: " << numStandardP << endl;
  cout << "Actual Percentage of StandardPass Rider: ";
  cout << numStandardP/numTotalRider * 100 << endl;
  cout << "Average Wait Time of StandardPass Rider: "; 
  cout << totalWaitTimeStandP/numStandardP << endl;
  cout << "Maximum Wait Time of StandardPass Rider: " << maxWaitTimeFP << endl;
  cout << "Maximun Length of StandardPass Rider: " << maxStandPLgth << endl;
  cout << "Average Number of StandardPass Rider on Each Train: ";
  cout << numStandardP/numTotalTrain << endl;
  cout << "Percentage of StandardPass Rider Filled on Each Train: ";
  cout << (numStandardP/numTotalTrain) / TRAIN_SEAT * 100 << "\n" << endl;
}





 

  

 