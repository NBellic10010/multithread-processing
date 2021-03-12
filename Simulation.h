#pragma once

#include <fstream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <string.h>
#include <iostream>
#include "Event.h"

using namespace std;

class Simulation {
private:
	// you will need to add fields
        // including: Queues for CPU and IO, and priority queues for Events 	
	Queue* eventQueue;
	Queue* CPU;
	Queue* IODevice;
	Queue* doneProcessQueue;
	int CPU_burst = 4;
	int timeslice = 0;
public:
	Simulation();

	// runSimulation -- start the simulation with the given filename.
	// Called by main.
	void runSimulation(char *fileName); 

	// summary -- print a summary of all the processes, as shown in the
	// assignment.  Called by main.
	void summary();

	// you may need to add more methods
	int getCPUburst();
	Queue* getEventQueue();
	Queue* getCPUQueue();
	Queue* getIOQueue();
	Queue* getdoneQueue();

};// class Simulation
