proj5.exe: proj5.o LinkedNodeClass.h SortedListClass.h FIFOQueueClass.h random.o SimulationClass.h EventsClass.o RiderClass.o TrainClass.o
	g++ proj5.o EventsClass.o random.o RiderClass.o TrainClass.o -o proj5.exe

EventsClass.o: EventsClass.h EventsClass.cpp 
	g++ -c EventsClass.cpp -o EventsClass.o

RiderClass.o: RiderClass.h RiderClass.cpp 
	g++ -c RiderClass.cpp -o RiderClass.o

TrainClass.o: TrainClass.h TrainClass.cpp 
	g++ -c TrainClass.cpp -o TrainClass.o
	
random.o: random.h random.cpp
	g++ -c random.cpp -o random.o

proj5.o: proj5.cpp LinkedNodeClass.h SortedListClass.h FIFOQueueClass.h random.h SimulationClass.h EventsClass.h RiderClass.h TrainClass.h
	g++ -c proj5.cpp -o proj5.o

clean:
	rm -f proj5.exe proj5.o random.o EventsClass.o RiderClass.o TrainClass.o