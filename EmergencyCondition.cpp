#include "EmergencyCondition.h"

EmergencyCondition::~EmergencyCondition(*Emergency emergency): emergency(emergency)
{
    
}

EmergencyCondition::~EmergencyCondition()
{
    delete emergency;
}

std::string EmergencyCondition::getLocation()
{
    return emergency->getLocation();
}

std::string EmergencyCondition::getDescription()
{
    return emergency->getDescription();
}