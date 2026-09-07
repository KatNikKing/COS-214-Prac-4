#ifndef RESPONSE_UNIT_H
#define RESPONSE_UNIT_H

#include "State.h"
#include "Capability.h"

#include <iostream>
#include <vector>

class Emergency;
class DispatchIterator;
class RollCallIterator;

using namespace std;

class ResponseUnit {
protected:
    std::string name;
    State* state;


public:
    ResponseUnit(std::string name);
    virtual ~ResponseUnit();
    std::string getName() const;
    virtual void setState(State* state);
    void performDuty();
    virtual bool isAvailable() = 0;
    virtual bool hasCapability(Capability capability, int requiredResponders = 1) = 0;
    virtual bool canSatisfy(Emergency* emergency) = 0;
    virtual void add(ResponseUnit* unit) {}
    virtual void remove(string name) {}
    virtual ResponseUnit* remove(ResponseUnit* unit) { return nullptr; }
    ResponseUnit* get(string name);
    virtual void display(int level) = 0;
    virtual string toString() = 0;
    virtual DispatchIterator* createDispatchIterator(Emergency* emergency) = 0;
    virtual RollCallIterator* createRollCallIterator() = 0;
};

#endif