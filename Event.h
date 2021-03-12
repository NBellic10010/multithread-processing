#pragma once
#include "ListItem.h"
#include "Process.h"
#include <string>
#include "Queue.h"

class Process;
class Simulation;

class Event: public ListItem {
private:
	int eventTime;
	Process *process;
protected:
	Simulation *sim;
public:
	// constructor, with pointer to the process that is being handled, and the simulation.
	Event(int theTime, Process *theProcess, Simulation* sim); 

	// pure virtual method - to handle the current event when it is removed from the queue.
	virtual void handleEvent(Queue* CPUQueue, Queue* IOQueue) = 0;

	// compareTo - used to order Events. 
	int compareTo(ListItem *other);
	Process* getProcess();
	int getProcessNum();
	int geteventTime();
	void setProcess(Process* theProcess);
};// class Event


class ArriveEvent: public Event {
public:
	using Event::Event;
	void handleEvent(Queue* CPUQueue, Queue* IOQueue);
};

class StartCPUEvent: public Event {
public:
	using Event::Event;
	void handleEvent(Queue* CPUQueue, Queue* IOQueue);
};

class CompleteCPUEvent: public Event {
public:
	using Event::Event;
	void handleEvent(Queue* CPUQueue, Queue* IOQueue);
};

class TimeoutEvent: public Event {
public:
	using Event::Event;
	void handleEvent(Queue* CPUQueue, Queue* IOQueue);
};

class StartIOEvent: public Event {
public:
	using Event::Event;
	void handleEvent(Queue* CPUQueue, Queue* IOQueue);
};

class CompleteIOEvent: public Event {
public:
	using Event::Event;
	void handleEvent(Queue* CPUQueue, Queue* IOQueue);
};

class ExitEvent: public Event {
public:
	using Event::Event;
	void handleEvent(Queue* CPUQueue, Queue* IOQueue);
	void handleEvent(Queue* queue, int time);
};

