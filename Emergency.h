#ifndef EMERGENCY_H
#define EMERGENCY_H

#include "ResponseUnit.h"
#include <vector>
#include <algorithm>

class Emergency : public ResponseUnit {
private:
    std::vector<ResponseUnit*> subUnits;

public:
    Emergency(const std::string& name);
    
    ~Emergency() override;

    void processIncident() override;
    
    void addUnit(ResponseUnit* unit) override;
    void removeUnit(ResponseUnit* unit) override;
};

#endif