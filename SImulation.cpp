#include "Simulation.h"

using namespace std;

Simulation::Simulation() {
    this->eventQueue = new Queue();
    this->CPU = new Queue();
    this->IODevice = new Queue();
}

void Simulation::runSimulation(char* filename) {
    ifstream file_data;
    int fd_summary = open("summary.md", O_RDWR | O_TRUNC);
    file_data.open("A2-official-data.txt");

    char buf[1024];
    char time[10];
    if(!file_data.peek()) {
        cout << "File is empty." << endl;
        return;
    }

    file_data.getline(buf, 1);
    int nextArrival = atoi(buf);
    memset(buf, 0, 1024);

    int timeslice = nextArrival, processNum = 0;
    file_data.get();

    for( ; ;timeslice++) {
        if(timeslice == nextArrival) {
            cout << timeslice << endl;
            if(file_data.eof()) return;

            file_data.getline(buf, 1024);

            string line(buf, buf + strlen(buf));
            memset(buf, 0, 1024);
            Process* newProcess = new Process(processNum++, line);
            ArriveEvent* event = new ArriveEvent(timeslice, newProcess, this);
            event->handleEvent();

            file_data >> time;
            nextArrival = atoi(time);
        }
        ListItem* curCPU = this->CPU->getFront();
        ListItem* curIO = this->IODevice->getFront();
        int i = 0;
        if(curCPU) {
            Process* currentCPUProcess = dynamic_cast<Process*>(curCPU);
            if(currentCPUProcess->getlisthead()->getType() == DUM) {
                ExitEvent* exitEvent = new ExitEvent(timeslice, currentCPUProcess, this);
                exitEvent->handleEvent(this->CPU);
            }
            else if(currentCPUProcess->getlisthead()->getCost() == 0) {
                CompleteCPUEvent* completeEvent = new CompleteCPUEvent(timeslice, currentCPUProcess, this);
                completeEvent->handleEvent();
            }
            else {
                StartCPUEvent* startCPUEvent = new StartCPUEvent(timeslice, currentCPUProcess, this);
                startCPUEvent->handleEvent();
                if(i == this->getCPUburst()) {
                    TimeoutEvent* timeoutEvent = new TimeoutEvent(timeslice, currentCPUProcess, this);
                    timeoutEvent->handleEvent();
                }
            }
        }
        if(curIO) {
            Process* currentIOProcess = dynamic_cast<Process*>(curIO);
            if(currentIOProcess->getlisthead()->getType() == DUM) {
                ExitEvent* exitEvent = new ExitEvent(timeslice, currentIOProcess, this);
                exitEvent->handleEvent(this->IODevice);
            }
            else if(currentIOProcess->getlisthead()->getCost() == 0) {
                CompleteIOEvent* completeEvent = new CompleteIOEvent(timeslice, currentIOProcess, this);
                completeEvent->handleEvent();
            }
            else {
                StartIOEvent* startIOEvent = new StartIOEvent(timeslice, currentIOProcess, this);
                startIOEvent->handleEvent();
            }
        }

    }

}

void Simulation::summary() {

}