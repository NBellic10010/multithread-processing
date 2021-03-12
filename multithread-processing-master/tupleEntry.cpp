#include "tupleEntry.h"

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

enumType tupleEntry::getType() { return this->type; }

tupleEntry::~tupleEntry() { delete this; }