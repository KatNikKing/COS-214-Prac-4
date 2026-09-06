#include "EmergencyIncident.h"

EmergencyIncident::EmergencyIncident(std::string location, std::string description, int requiredResponders, std::vector<Capability> baseCapabilities)
{
    this->location = location;
    this->description = description;
    this->requiredResponders = requiredResponders > 0 ? requiredResponders : 1;
    this->baseCapabilities = baseCapabilities;
}

EmergencyIncident::~EmergencyIncident()
{
    //nothing to cleanup
}

std::string EmergencyIncident::getLocation()
{
    return location;
}

std::string EmergencyIncident::getDescription()
{
    return description;
}

int EmergencyIncident::getRequiredResponders() {
    return requiredResponders;
}

std::vector<Capability> EmergencyIncident::getRequiredCapabilities()
{
    return baseCapabilities;
}