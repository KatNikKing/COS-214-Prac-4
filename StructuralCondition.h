#ifndef STRUCTURALCONDITION_H
#define STRUCTURALCONDITION_H

#include  "EmergencyCondition.h"

class StructuralCondition : public EmergencyCondition
{
    public:
        StructuralCondition(Emergency*);
        std::vector<Capability> getRequiredCapabilities();
};

#endif