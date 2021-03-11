#pragma once
#include "ListItem.h"
#include "Process.h"
#include <string>
#include "Queue.h"
#include "Simulation.h"

class Process;
class Simulation;

class ArriveEvent: public Event {
public:
	using Event::Event;
	void handleEvent();
};

class StartCPUEvent: public Event {
public:
	using Event::Event;
	void handleEvent();
};

class CompleteCPUEvent: public Event {
public:
	using Event::Event;
	void handleEvent();
};

class TimeoutEvent: public Event {
public:
	using Event::Event;
	void handleEvent();
};

class StartIOEvent: public Event {
public:
	using Event::Event;
	void handleEvent();
};

class CompleteIOEvent: public Event {
public:
	using Event::Event;
	void handleEvent();
};

class ExitEvent: public Event {
public:
	using Event::Event;
	void handleEvent(Queue* queue);
	void handleEvent();
};

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
	virtual void handleEvent() = 0;

	// compareTo - used to order Events. 
	int compareTo(ListItem *other);
	Process* getProcess();
	int getProcessNum();
	int geteventTime();
	void setProcess(Process* theProcess);
};// class Event

