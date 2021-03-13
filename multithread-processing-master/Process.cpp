#include "Process.h"
#include <iostream>

using namespace std;

Process::Process(int processno, std::string line) : processNo(processno) {
    cout << "Process construct function." << endl; //checkpoint
    this->listhead = new tupleEntry(DUM, 0);
    if(setlist(line) < 0) exit(-1);
}

Process::Process() {}

int Process::getProcessNo() { return this->processNo; }

tupleEntry* Process::getlisthead() { return this->listhead; }

int Process::setlist(std::string line) {
    char* cstr = (char*)line.c_str();
    const char* delim = " ";
    char* p;
    p = strtok(cstr, delim);
    if(atoi(p) < 0) {
        printf("Invalid input serial");
        return -1;
    }
    tupleEntry* pEntry = this->getlisthead();
    int t;
    int pret = -1;
    while(p) {
        t = atoi(p);
        if(pret > 0 && t > 0 || pret < 0 && t < 0) {
            printf("Invalid input serial.\n");
            return -2;
        }
        if(t > 0) {
            pEntry->setNext(new tupleEntry(CPU, t));
        } else if (t < 0) {
            pEntry->setNext(new tupleEntry(IO, -t));
        } else {
            perror("Value 0 does not mean to exist.");
            return -3;
        }
        pEntry = pEntry->getNext();
        this->listtail = pEntry;
        p = strtok(NULL, delim);
        pret = t;
    }

    tupleEntry* dum = this->listhead;
    this->listheadForward();
    this->listtail->setNext(dum);
    this->listtail = this->listtail->getNext();
    dum->setNext(NULL);
    return 0;
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