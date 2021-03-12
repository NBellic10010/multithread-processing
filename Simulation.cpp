#include "Simulation.h"

using namespace std;

Simulation::Simulation() {
    this->eventQueue = new Queue();
    this->CPU = new Queue();
    this->IODevice = new Queue();
    this->doneProcessQueue = new Queue();
}

void Simulation::runSimulation(char* filename) {
    ifstream file_data;
    int i = 0;
    //int fd_summary = open("summary.md", O_RDWR | O_TRUNC);
    file_data.open(filename);

    char buf[1024];
    char time[10];
    if(!file_data.peek()) {
        cout << "File is empty." << endl;
        return;
    }

    file_data.getline(buf, 10);
    int nextArrival = atoi(buf);
    memset(buf, 0, 1024);

    int timeslice = nextArrival, processNum = 1;
    file_data.read(buf, 2);

    for( ; ;this->timeslice++) {
        if(this->timeslice == nextArrival) {
            cout << "New process arrived: " << timeslice << endl; //Checkpoint
            if(file_data.eof()) return;

            file_data.getline(buf, 1024);

            string line(buf, buf + strlen(buf));
            memset(buf, 0, 1024);
            Process* newProcess = new Process(processNum++, line);
            ArriveEvent* event = new ArriveEvent(timeslice, newProcess, this);
            event->handleEvent(this->CPU, this->IODevice);

            file_data >> time;
            nextArrival = atoi(time);
        }
        ListItem* curCPU = this->CPU->getFront();
        ListItem* curIO = this->IODevice->getFront();
        if(curCPU) {
            Process* currentCPUProcess = dynamic_cast<Process*>(curCPU);
            //cout << currentCPUProcess->getlisthead()->getType() << endl; //checkpoint
            if(currentCPUProcess->getlisthead()->getType() == DUM) {
                ExitEvent* exitEvent = new ExitEvent(timeslice, currentCPUProcess, this);
                exitEvent->handleEvent(this->CPU, this->timeslice);
                this->doneProcessQueue->enqueue((ListItem*)currentCPUProcess);
            }
            else if(currentCPUProcess->getlisthead()->getCost() == 0) {
                CompleteCPUEvent* completeEvent = new CompleteCPUEvent(timeslice, currentCPUProcess, this);
                completeEvent->handleEvent(this->CPU, this->IODevice);
            }
            else {
                StartCPUEvent* startCPUEvent = new StartCPUEvent(timeslice, currentCPUProcess, this);
                startCPUEvent->handleEvent(this->CPU, this->IODevice);
                ++i;
                if(i == this->getCPUburst()) {
                    if(currentCPUProcess->getlisthead()->getCost() == 0) {
                        CompleteCPUEvent* completeEvent = new CompleteCPUEvent(timeslice, currentCPUProcess, this);
                        completeEvent->handleEvent(this->CPU, this->IODevice);
                        continue;
                    }
                    TimeoutEvent* timeoutEvent = new TimeoutEvent(timeslice, currentCPUProcess, this);
                    timeoutEvent->handleEvent(this->CPU, this->IODevice);
                    i = 0;
                }
                
            }
            //cout << "Checkpoint: end of CPU" << endl; //checkpoint
        }
        if(curIO) {
            Process* currentIOProcess = dynamic_cast<Process*>(curIO);
            if(currentIOProcess->getlisthead()->getType() == DUM) {
                ExitEvent* exitEvent = new ExitEvent(timeslice, currentIOProcess, this);
                exitEvent->handleEvent(this->IODevice, this->timeslice);
                this->doneProcessQueue->enqueue((ListItem*)currentIOProcess);
            }
            else if(currentIOProcess->getlisthead()->getCost() == 0) {
                CompleteIOEvent* completeEvent = new CompleteIOEvent(timeslice, currentIOProcess, this);
                completeEvent->handleEvent(this->CPU, this->IODevice);
            }
            else {
                StartIOEvent* startIOEvent = new StartIOEvent(timeslice, currentIOProcess, this);
                startIOEvent->handleEvent(this->CPU, this->IODevice);
            }
        }

    }

}

void Simulation::summary() {
    Queue* queue = this->getdoneQueue();
    cout << "************** SUMMARY ***************" << endl;
    for(int i = 0; i < queue->getSize(); i++) {
        ListItem* processItem = queue->dequeue();
        Process* currentProcess = dynamic_cast<Process*>(processItem);

        cout << "-----------Process " << currentProcess->getProcessNo() << "-----------" << endl;
        cout << "Process arrival time: " << currentProcess->getarrivetime() << endl;
        cout << "on CPU: " << currentProcess->getCPUtime() << endl;
        cout << "on IO device: " << currentProcess->getIOtime() << endl;
        cout << "Exit at" << currentProcess->getexittime() << endl;
    }
    cout << "************** SUMMARY COMPLETE ***************" << endl;
}

int Simulation::getCPUburst() { return this->CPU_burst; }

Queue* Simulation::getCPUQueue() { return this->CPU; }
Queue* Simulation::getIOQueue() { return this->IODevice; }
Queue* Simulation::getdoneQueue() { return this->doneProcessQueue; }