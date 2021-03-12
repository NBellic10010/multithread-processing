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
    void setlist(std::string line);
    int arrivetime;
    int onCPU_Time = 0;
    int onIO_Time = 0;
    int exit_Time = 0;
public:
    Process(int processNo, std::string line);
    int getProcessNo();
    tupleEntry* getlisthead();
    void listheadForward();
    void setarrivetime(int time);
    int getarrivetime();
    int compareTo(ListItem* order);

    int addCPUtime();
    int addIOtime();
    int setexittime(int time);

    int getCPUtime();
    int getIOtime();
    int getexittime();
};