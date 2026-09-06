#include "Emergency.h"
#include <iostream>

Emergency::Emergency(const std::string& name) : ResponseUnit(name) {}

Emergency::~Emergency() {
    for (ResponseUnit* unit : subUnits) {
        delete unit;
    }
    subUnits.clear();
}

void Emergency::processIncident() {

}

void Emergency::addUnit(ResponseUnit* unit){
}

void Emergency::removeUnit(ResponseUnit* unit) {
}