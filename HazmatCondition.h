#ifndef HAZMATCONDITION_H
#define HAZMATCONDITION_H

#include  "EmergencyCondition.h"

class HazmatCondition : public EmergencyCondition
{
    public:
        HazmatCondition(Emergency*);
        std::vector<Capability> getRequiredCapabilities();
};

#endif