#ifndef EMERGENCY_H
#define EMERGENCY_H

#include "Capability.h"

#include <iostream>
#include <vector>

using namespace std;

class Emergency {
public:
    virtual ~Emergency() = default;
    virtual string getLocation() = 0;
    virtual string getDescription() = 0;
    virtual int getRequiredResponders() = 0;
    virtual vector<Capability> getRequiredCapabilities() = 0;
};

#endif