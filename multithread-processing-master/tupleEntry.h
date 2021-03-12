#pragma once
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