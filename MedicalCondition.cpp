#include "MedicalCondition.h"

MedicalCondition::MedicalCondition(Emergency* emergency): EmergencyCondition(emergency)
{
    
}

std::vector<Capability> MedicalCondition::getRequiredCapabilities() {
    std::vector<Capability> capabilities = emergency->getRequiredCapabilities();
    capabilities.push_back(Capability::FIRST_AID);
    return capabilities;
}