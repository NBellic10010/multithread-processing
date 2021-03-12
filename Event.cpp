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
void ArriveEvent::handleEvent(Queue* CPUQueue, Queue* IOQueue) {
	hint += "Process ";
	Process* p = this->getProcess();
	hint += to_string(p->getProcessNo());
	hint += " has arrived, ";
	if(CPUQueue->isEmpty()) {
		hint += "CPU is now free.\n";
	} else {
		hint += "CPU occupied.\n";
	}
	CPUQueue->enqueue((ListItem*)this->getProcess());
	cout << hint;
	hint.clear();
	//sleep(1);
}

//startCPU事件，可以驱动timeout事件和completeCPU事件
void StartCPUEvent::handleEvent(Queue* CPUQueue, Queue* IOQueue) {
	if(CPUQueue->isEmpty()) {
		hint += "No process pending for CPU\n";
	} else {
		Process* p = this->getProcess();
		int cost = p->getlisthead()->getCost();
		p->getlisthead()->resCost();
		hint += "Process ";
		hint += to_string(p->getProcessNo());
		hint += " on CPU, ";
		hint += to_string(cost);
		hint += " timeslice(s) remaining.\n";
		this->getProcess()->addCPUtime();
	}
	cout << hint;
	hint.clear();
	//sleep(1);
}

//startIO事件，可以驱动completeIO事件
void StartIOEvent::handleEvent(Queue* CPUQueue, Queue* IOQueue) {
	if(IOQueue->isEmpty()) {
		hint += "No process pending for IO\n";
	} else {
		Process* p = this->getProcess();
		p->getlisthead()->resCost();
		hint += "Process ";
		hint += to_string(p->getProcessNo());
		hint += " on IO, ";
		hint += to_string(p->getlisthead()->getCost());
		hint += " timeslice(s) remaining.\n";
		this->getProcess()->addIOtime();
	}
	cout << hint;
	hint.clear();
	//sleep(1);
}

void CompleteCPUEvent::handleEvent(Queue* CPUQueue, Queue* IOQueue) {
	Process* theProcess = this->getProcess();
	if(theProcess->getlisthead()->getCost() == 0) {
		hint += "CPU progress done, process ";
		hint += to_string(theProcess->getProcessNo());
		hint += " now exiting.\n";
		theProcess->listheadForward();
		CPUQueue->dequeue();
	}
	IOQueue->enqueue((ListItem*)theProcess);
	cout << hint;
	hint.clear();
	//sleep(1);
}

void TimeoutEvent::handleEvent(Queue* CPUQueue, Queue* IOQueue) {
	Process* theProcess = this->getProcess();
	if(theProcess->getlisthead()->getType() == CPU) {
		hint += "Process ";
		hint += to_string(theProcess->getProcessNo());
		hint += " has run out its allocated time quantum and will be suspended.\n";
		CPUQueue->dequeue();
		CPUQueue->enqueue((ListItem*)theProcess);
	} 
	else if(theProcess->getlisthead()->getType() == IO) {
		cout << "There shouldn`t be any timeout during an IO process.\n";
		return;
	}
	cout << hint;
	hint.clear();
	//sleep(1);
}

void CompleteIOEvent::handleEvent(Queue* CPUQueue, Queue* IOQueue) {
	Process* theProcess = this->getProcess();
	if(theProcess->getlisthead()->getCost() == 0) {
		hint += "IO progress done, process ";
		hint += to_string(theProcess->getProcessNo());
		hint += " now releasing IO device for use.\n";
		theProcess->listheadForward();
		IOQueue->dequeue();
	}
	CPUQueue->enqueue((ListItem*)theProcess);
	cout << hint;
	hint.clear();
	//sleep(1);
}

void ExitEvent::handleEvent(Queue* queue, int time) {
	Process* theProcess = this->getProcess();
	if(theProcess->getlisthead()->getType() != DUM) {
		printf("Not finished yet!\n");
		return;
	}
	hint += "Process ";
	hint += to_string(theProcess->getProcessNo());
	hint += " now exiting.\n";
	queue->dequeue();
	cout << hint;
	hint.clear();
	this->getProcess()->setexittime(time);
	//sleep(2);
}

void ExitEvent::handleEvent(Queue* CPUQueue, Queue* IOQueue) {
	
}
