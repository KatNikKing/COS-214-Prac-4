#ifndef HAZMATCONDITION_H
#define HAZMATCONDITION_H

#include  "EmergencyCondition.h"

class HazmatCondition : public EmergencyCondition
{
    //methods
    public:
        HazmatCondition(Emergency*);
        std::vector<Capability> getRequiredCapabilities();
};

#endif