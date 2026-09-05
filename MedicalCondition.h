#ifndef EMERGENCYCONDITION_H
#define EMERGENCYCONDITION_H

#include  "EmergencyCondition.h"

class MedicalCondition : public EmergencyCondition
{
    //methods
    public:
        MedicalCondition(*Emergency);
        std::vector<Capability> getRequiredCapabilities();
}

#endif