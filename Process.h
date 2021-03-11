#pragma once
#include <string>
#include <string.h>
#include "ListItem.h"
enum enumType{
    CPU, IO, DUM
};

class tupleEntry {
private:
    enumType type;
    int cost;
    tupleEntry* next;
    
public:
    tupleEntry(enumType type, int cost);
    void setNext(tupleEntry* next);
    tupleEntry* getNext();
    enumType getType();
    void resCost();
    int getCost();
    ~tupleEntry();
};

class Process: public ListItem {
private:
    int processNo;
    tupleEntry* listhead;
    tupleEntry* listtail;
    void setlist(std::string line);
    int arrivetime;
public:
    Process(int processNo, std::string line);
    int getProcessNo();
    tupleEntry* getlisthead();
    void listheadForward();
    void setarrivetime(int time);
    int getarrivetime();
    int compareTo(ListItem* order);
};