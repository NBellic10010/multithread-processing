#include "Process.h"
#include <string.h>

tupleEntry::tupleEntry(enumType type, int cost) {
    this->type = type;
    this->cost = cost;
}

tupleEntry* tupleEntry::getNext() {
    return this->next;
}

void tupleEntry::setNext(tupleEntry* next) {
    this->next = next;
}

void tupleEntry::resCost() { this->cost--; }

int tupleEntry::getCost() { return this->cost; }

tupleEntry::~tupleEntry() { delete this; }

Process::Process(int processno, std::string line) : processNo(processno) {
    this->listhead = new tupleEntry(DUM, 0);
    setlist(line);
}

int Process::getProcessNo() { return this->processNo; }

tupleEntry* Process::getlisthead() { return this->listhead; }

void Process::setlist(std::string line) {
    //wait for implement
    char* cstr = (char*)line.c_str();
    const char* delim = " ";
    char* p;
    p = strtok(cstr, delim);
    this->setarrivetime(atoi(p));
    p = strtok(NULL, delim);
    while(p) {
        int t = atoi(p);
        tupleEntry* pEntry = this->getlisthead();
        if(t > 0) {
            pEntry->setNext(new tupleEntry(CPU, t));
        } else {
            pEntry->setNext(new tupleEntry(IO, -t));
        }
        this->listtail = pEntry;
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