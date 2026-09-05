#include "HazmatCondition.h"

HazmatCondition::HazmatCondition(*Emergency emergency): EmergencyCondition(emergency)
{
    
}

std::vector<Capability> HazmatCondition::getRequiredCapabilities() {
    std::vector<Capability> capabilities = emergency->getRequiredCapabilities();
    capabilities.push_back(Capability::HAZMAT);
    return capabilities;
}