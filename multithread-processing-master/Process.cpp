#include "Process.h"
#include <iostream>

using namespace std;

Process::Process(int processno, std::string line) : processNo(processno) {
    cout << "Process construct function." << endl; //checkpoint
    this->listhead = new tupleEntry(DUM, 0);
    setlist(line);
}

int Process::getProcessNo() { return this->processNo; }

tupleEntry* Process::getlisthead() { return this->listhead; }

void Process::setlist(std::string line) {
    char* cstr = (char*)line.c_str();
    const char* delim = " ";
    char* p;
    p = strtok(cstr, delim);
    tupleEntry* pEntry = this->getlisthead();
    while(p) {
        int t = atoi(p);
        if(t > 0) {
            pEntry->setNext(new tupleEntry(CPU, t));
        } else if (t < 0) {
            pEntry->setNext(new tupleEntry(IO, -t));
        } else {
            perror("Value 0 does not mean to exist.");
            exit(1);
        }
        pEntry = pEntry->getNext();
        this->listtail = pEntry;
        p = strtok(NULL, delim);
    }

    tupleEntry* dum = this->listhead;
    this->listheadForward();
    this->listtail->setNext(dum);
    this->listtail = this->listtail->getNext();
    dum->setNext(NULL);
}

void Process::listheadForward() { this->listhead = this->listhead->getNext(); }

void Process::setarrivetime(int time) {
    this->arrivetime = time;
}

int Process::getarrivetime() {
    return this->arrivetime;
}

int Process::compareTo(ListItem* order) {
    return 0;
}

int Process::addCPUtime() {
    this->onCPU_Time++;
    return this->onCPU_Time;
}

int Process::addIOtime() {
    this->onIO_Time++;
    return this->onIO_Time;
}

int Process::setexittime(int time) { 
    this->exit_Time = time; 
    return this->exit_Time;
}

int Process::getCPUtime() {
   return this->onCPU_Time;
}

int Process::getIOtime() {
    return this->onIO_Time;
}

int Process::getexittime() {
    return this->exit_Time;
}