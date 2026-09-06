#ifndef EMERGENCY_H
#define EMERGENCY_H

#include "ResponseUnit.h"
#include <vector>
#include <algorithm>

class EmergencyCondition;

class Emergency : public ResponseUnit {
private:
    std::vector<ResponseUnit*> subUnits;
    EmergencyCondition* currentCondition; 

public:
    Emergency(const std::string& name);
    ~Emergency() override;

    void processIncident() override;
    
    void addUnit(ResponseUnit* unit) override;
    void removeUnit(ResponseUnit* unit) override;

    Iterator* createIterator() override;

    void setCondition(EmergencyCondition* condition);
    EmergencyCondition* getCondition() const;
};

#endif