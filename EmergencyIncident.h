#ifndef EMERGENCYINCIDENT_H
#define EMERGENCYINCIDENT_H

#include "Emergency.h"
#include <string>
#include <vector>


class EmergencyIncident : public Emergency
{
    //members
    private:
        std::string location, description;
        int requiredResponders;
        std::vector<Capability> baseCapabilities;

    //methods
    public:
        EmergencyIncident(std::string, std::string, int, std::vector<Capability>);
        ~EmergencyIncident();
        std::string getLocation() override;
        std::string getDescription() override;
        int getRequiredResponders();
        std::vector<Capability> getRequiredCapabilities() override;
};

#endif