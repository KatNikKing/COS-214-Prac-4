#ifndef STRUCTURALCONDITION_H
#define STRUCTURALCONDITION_H

#include  "EmergencyCondition.h"

class StructuralCondition : public EmergencyCondition
{
    //methods
    public:
        StructuralCondition(*Emergency);
        std::vector<Capability> getRequiredCapabilities();
}

#endif