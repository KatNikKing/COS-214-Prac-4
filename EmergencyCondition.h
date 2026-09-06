#ifndef EMERGENCYCONDITION_H
#define EMERGENCYCONDITION_H

#include "Emergency.h"


class EmergencyCondition : public Emergency
{
    //members
    protected:
        Emergency* emergency;

    //methods
    public:
        EmergencyCondition(Emergency*);
        virtual ~EmergencyCondition();
        std::string getLocation();
        std::string getDescription();
        int getRequiredResponders();
        virtual std::vector<Capability> getRequiredCapabilities() = 0;
};

#endif  