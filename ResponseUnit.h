#ifndef RESPONSE_UNIT_H
#define RESPONSE_UNIT_H

#include <string>
#include <stdexcept>

class ResponseUnit {
protected:
    std::string unitName;

public:
    ResponseUnit(const std::string& name);
    virtual ~ResponseUnit();

    virtual void processIncident() = 0; 

    virtual void addUnit(ResponseUnit* unit);
    virtual void removeUnit(ResponseUnit* unit);

    std::string getName() const;
};

#endif