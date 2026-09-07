#ifndef EMERGENCYINCIDENT_H
#define EMERGENCYINCIDENT_H

#include "Emergency.h"

class EmergencyIncident : public Emergency
{
    private:
        std::string location, description;
        int requiredResponders;
        std::vector<Capability> baseCapabilities;

    public:
        EmergencyIncident(std::string, std::string, int, std::vector<Capability>);
        ~EmergencyIncident();
        std::string getLocation() override;
        std::string getDescription() override;
        int getRequiredResponders() override;
        std::vector<Capability> getRequiredCapabilities() override;
};

#endif