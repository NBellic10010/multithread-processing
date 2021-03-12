#include "Simulation.h"

using namespace std;

//Constructor of Simulation class
Simulation::Simulation() {
    this->eventQueue = new Queue();
    this->CPU = new Queue();
    this->IODevice = new Queue();
    this->doneProcessQueue = new Queue();
}

//Handle function
void Simulation::runSimulation(char* filename) {
    //file reader
    ifstream file_data;
    int i = 0;
    //int fd_summary = open("summary.md", O_RDWR | O_TRUNC);
    file_data.open(filename);
    //buffer
    char buf[1024];
    char time[10];
    //No character found
    if(!file_data.peek()) {
        cout << "File is empty." << endl;
        return;
    }

    //Read the first line(Maximum CPU burst) to buffer
    file_data.getline(buf, 10);
    this->CPU_burst = atoi(buf);
    memset(buf, 0, 1024);
    file_data.read(buf, 2);
    int nextArrival = atoi(buf);
    int timeslice = nextArrival, processNum = 1;
    //Flags stand for the status when a process is leading the CPU(IO) Queue
    bool CPUflag = true, IOflag = true;

    for( ;;this->timeslice++) {
        if(this->timeslice == nextArrival) { //Next process arrives
            cout << "New process arrived: " << this->timeslice << endl;
            if(file_data.eof()) return;

            file_data.getline(buf, 1024);

            string line(buf, buf + strlen(buf));
            memset(buf, 0, 1024);
            Process* newProcess = new Process(processNum++, line);
            newProcess->setarrivetime(this->timeslice);
            //Arriveevent
            ArriveEvent* event = new ArriveEvent(timeslice, newProcess, this);
            event->handleEvent(this->CPU, this->IODevice);
            
            //Reads the arrival time of next process
            file_data >> time;
            nextArrival = atoi(time);
        }
        ListItem* curCPU = this->CPU->getFront();
        ListItem* curIO = this->IODevice->getFront();
        //if CPU is not empty
        if(curCPU) {
            Process* currentCPUProcess = dynamic_cast<Process*>(curCPU);
            //DUM stands for "end", indicating that no upcoming CPU/IO event of this process exists 
            if(currentCPUProcess->getlisthead()->getType() == DUM) {
                //Exitevent
                ExitEvent* exitEvent = new ExitEvent(timeslice, currentCPUProcess, this);
                exitEvent->handleEvent(this->CPU, this->timeslice);
                this->doneProcessQueue->enqueue((ListItem*)currentCPUProcess);
                cout << "Process " << currentCPUProcess->getProcessNo() << " now enqueue from CPUQueue, at time " << this->timeslice << endl;
            }
            else if(currentCPUProcess->getlisthead()->getCost() == 0) {
                //CPU progress complete, wait for IO or exit processing.
                CompleteCPUEvent* completeEvent = new CompleteCPUEvent(timeslice, currentCPUProcess, this);
                completeEvent->handleEvent(this->CPU, this->IODevice);
                CPUflag = true;
            }
            else {
                if(CPUflag) {
                    cout << "Process " << currentCPUProcess->getProcessNo() << " now using CPU" << endl; 
                    CPUflag = false;
                }
                //CPU start, a startCPUEvent handle causes the cost decreased by 1
                StartCPUEvent* startCPUEvent = new StartCPUEvent(timeslice, currentCPUProcess, this);
                startCPUEvent->handleEvent(this->CPU, this->IODevice);
                ++i;
                //Sevaral cases may happen to complete the whole CPU event within one set of max CPU bursts 
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
                cout << currentIOProcess->getProcessNo() << " now enqueue from IOQueue, at time " << this->timeslice << endl;
            }
            else if(currentIOProcess->getlisthead()->getCost() == 0) {
                CompleteIOEvent* completeEvent = new CompleteIOEvent(timeslice, currentIOProcess, this);
                completeEvent->handleEvent(this->CPU, this->IODevice);
                IOflag = true;
            }
            else {
                if(IOflag)  {
                    cout << "Process " << currentIOProcess->getProcessNo() << " now using IO device" << endl; 
                    IOflag = false;
                }
                StartIOEvent* startIOEvent = new StartIOEvent(timeslice, currentIOProcess, this);
                startIOEvent->handleEvent(this->CPU, this->IODevice);
            }
        }
    }

}

void Simulation::summary() {
    Queue* queue = this->getdoneQueue();
    cout << "************** SUMMARY ***************" << endl;
    while(!queue->isEmpty()) {
        ListItem* processItem = queue->dequeue();
        Process* currentProcess = dynamic_cast<Process*>(processItem);

        cout << "-----------Process " << currentProcess->getProcessNo() << "-----------" << endl;
        cout << "Process arrival time: " << currentProcess->getarrivetime() << endl;
        cout << "on CPU: " << currentProcess->getCPUtime() << endl;
        cout << "on IO device: " << currentProcess->getIOtime() << endl;
        cout << "Exit at " << currentProcess->getexittime() << endl;
    }
    cout << "************** SUMMARY COMPLETE ***************" << endl;
}

int Simulation::getCPUburst() { return this->CPU_burst; }

Queue* Simulation::getCPUQueue() { return this->CPU; }
Queue* Simulation::getIOQueue() { return this->IODevice; }
Queue* Simulation::getdoneQueue() { return this->doneProcessQueue; }

int Simulation::gettimeSlice() { return this->timeslice; }