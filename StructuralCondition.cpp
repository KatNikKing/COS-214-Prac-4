#include "StructuralCondition.h"

StructuralCondition::StructuralCondition(Emergency* emergency): EmergencyCondition(emergency)
{
    
}

std::vector<Capability> StructuralCondition::getRequiredCapabilities() {
    std::vector<Capability> capabilities = emergency->getRequiredCapabilities();
    capabilities.push_back(Capability::RESCUE);
    return capabilities;
}