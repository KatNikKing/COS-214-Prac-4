#ifndef EMERGENCYCONDITION_H
#define EMERGENCYCONDITION_H

#include "Emergency.h"


class EmergencyCondition : public MedicalCondition
{
    //members
    protected:
        Emergency* emergency;

    //methods
    public:
        EmergencyCondition(*Emergency);
        virtual ~EmergencyCondition();

        virtual std::vector<Capability> getRequiredCapabilities() = 0;
        std::string getLocation();
        std::string getDescription();

};

#endif  