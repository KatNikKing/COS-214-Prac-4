#include "EmergencyIncident.h"

EmergencyIncident::EmergencyIncident(std::string location, std::string description, std::vector<Capability> baseCapabilities)
{
    this->location = location;
    this->description = description;
    this->baseCapabilities = baseCapabilities;
}

EmergencyIncident::~EmergencyIncident()
{
    //nothing to cleanup
}

std::vector<Capability> EmergencyIncident::getRequiredCapabilities()
{
    return baseCapabilities;
}

std::string EmergencyIncident::getLocation()
{
    return location;
}

std::string EmergencyIncident::getDescription()
{
    return description;
}