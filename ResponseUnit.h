#ifndef RESPONSE_UNIT_H
#define RESPONSE_UNIT_H

#include "State.h"
#include "Capability.h"

class Emergency;

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
    ResponseUnit* get(string name);
    virtual void display(int level) = 0;
    virtual string toString() = 0;
};

#endif