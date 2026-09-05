#ifndef EMERGENCYINCIDENT_H
#define EMERGENCYINCIDENT_H

#include "Emergency.h"
#include <string>
#include <vector>


class EmergencyIncident : public EmergencyIncident
{
    //members
    private:
        std::string location;
        std:string description;
        std::vector<Capability> baseCapabilities;

    //methods
    public:
        EmergencyIncident(std::string, std::string, std::vector<Capability>);
        ~EmergencyIncident();
        std::vector<Capability> getRequiredCapabilities() override;
        std::string getLocation() override;
        std::string getDescription() override;


};

#endif