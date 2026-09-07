#ifndef MEDICALCONDITION_H
#define MEDICALCONDITION_H

#include "EmergencyCondition.h"

class MedicalCondition : public EmergencyCondition
{
public:
    MedicalCondition(Emergency*);
    std::vector<Capability> getRequiredCapabilities();
};

#endif