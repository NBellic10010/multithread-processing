#include "Event.h"
#include <iostream>
#include <unistd.h>

using namespace std;
string hint;

/**** Event implementation */
Event::Event(int theTime, Process *theProcess, Simulation *theSim) 
	 :eventTime(theTime), process(theProcess), sim (theSim) {}


int Event::compareTo(ListItem *other){
	 // you should implement this method.
	 Event* ev = (Event*)other;
	 return this->getProcessNum() >= ev->getProcessNum();
}

int Event::geteventTime() {
	return this->eventTime;
}

int Event::getProcessNum() {
	return this->getProcess()->getProcessNo();
}

Process* Event::getProcess() {
	return this->process;
}

//arrive事件，可以驱动startCPU事件
void ArriveEvent::handleEvent() {
	hint += "Process {} has arrived, ";
	Queue* CPUQueue = this->sim->getCPUQueue();
	if(CPUQueue->isEmpty()) {
		CPUQueue->enqueue((ListItem*)this->getProcess());
		hint += "CPU is now free.\n";
	} else {
		hint += "CPU occupied.\n";
	}
	cout << hint;
	hint.clear();
	sleep(5);
}

//startCPU事件，可以驱动timeout事件和completeCPU事件
void StartCPUEvent::handleEvent() {
	Queue* CPUQueue = this->sim->getCPUQueue();
	if(CPUQueue->isEmpty()) {
		hint += "No process pending for CPU\n";
	} else {
		Process* p = this->getProcess();
		p->getlisthead()->resCost();
		hint += "Process {} on CPU, ";
		hint += to_string(p->getlisthead()->getCost());
		hint += " remaining.\n";
	}
	cout << hint;
	hint.clear();
	sleep(5);
}

//startIO事件，可以驱动completeIO事件
void StartIOEvent::handleEvent() {
	Queue* IOQueue = this->sim->getIOQueue();
	if(IOQueue->isEmpty()) {
		hint += "No process pending for IO\n";
	} else {
		Process* p = this->getProcess();
		p->getlisthead()->resCost();
		hint += "Process {} on IO device, ";
		hint += to_string(p->getlisthead()->getCost());
		hint += " remaining.\n";
	}
	cout << hint;
	hint.clear();
	sleep(5);
}

//completeCPU事件，可以驱动startIO事件或exit事件
void CompleteCPUEvent::handleEvent() {
	Process* theProcess = this->getProcess();
	if(theProcess->getlisthead()->getCost() == 0) {
		hint += "CPU progress done, process ";
		hint += to_string(theProcess->getProcessNo());
		hint += " now exiting.\n";
		theProcess->listheadForward();
		return;
	}
	Queue* IOQueue = this->sim->getIOQueue();
	IOQueue->enqueue((ListItem*)theProcess);
	cout << hint;
	hint.clear();
	sleep(5);
}

//timeout事件
void TimeoutEvent::handleEvent() {
	Process* theProcess = this->getProcess();
	if(theProcess->getlisthead()->getType() == CPU) {
		hint += "Process ";
		hint += to_string(theProcess->getProcessNo());
		hint += "has run out its allocated time quantum and will be suspended.";
		Queue* CPUQueue = this->sim->getCPUQueue();
		CPUQueue->dequeue();
		CPUQueue->enqueue((ListItem*)theProcess);
	} 
	else if(theProcess->getlisthead()->getType() == IO) {
		perror("There shouldn`t be any timeout during an IO process.\n");
		return;
	}
	cout << hint;
	hint.clear();
	sleep(5);
}

//completeio事件，可以驱动startCPU事件或exit事件
void CompleteIOEvent::handleEvent() {
	Process* theProcess = this->getProcess();
	if(theProcess->getlisthead()->getCost() == 0) {
		hint += "IO progress done, process ";
		hint += to_string(theProcess->getProcessNo());
		hint += " now releasing IO device for use.\n";
		theProcess->listheadForward();
		return;
	}
	Queue* CPUQueue = this->sim->getCPUQueue();
	CPUQueue->enqueue((ListItem*)theProcess);
	cout << hint;
	hint.clear();
	sleep(5);
}

//exit事件
void ExitEvent::handleEvent(Queue* queue) {
	Process* theProcess = this->getProcess();
	if(theProcess->getlisthead()) {
		perror("Not finished yet!");
		return;
	}
	hint += "Process ";
	hint += to_string(theProcess->getProcessNo());
	hint += "now exiting.\n";
	queue->dequeue();
	cout << hint;
	hint.clear();
	sleep(5);
}
