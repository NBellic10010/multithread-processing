#pragma once
#include <string>
#include <string.h>
#include "ListItem.h"
#include "tupleEntry.h"

class Process: public ListItem {
private:
    int processNo;
    tupleEntry* listhead;
    tupleEntry* listtail;
    
    int arrivetime;
    int onCPU_Time = 0;
    int onIO_Time = 0;
    int exit_Time = 0;
public:
    Process(int processNo, std::string line);
    Process();
    int getProcessNo();
    tupleEntry* getlisthead();
    void listheadForward();
    void setarrivetime(int time);
    int getarrivetime();
    int compareTo(ListItem* order);
    
    int addCPUtime();
    int addIOtime();
    int setexittime(int time);
    int setlist(std::string line);
    int getCPUtime();
    int getIOtime();
    int getexittime();
};