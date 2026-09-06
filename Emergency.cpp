#include "Emergency.h"
#include "EmergencyCondition.h"
#include <iostream>

Emergency::Emergency(const std::string& name) : ResponseUnit(name), currentCondition(nullptr) {}

Emergency::~Emergency() {
    for (ResponseUnit* unit : subUnits) {
        delete unit;
    }
    subUnits.clear();
    
    if (currentCondition != nullptr) {
        delete currentCondition;
    }
}


void Emergency::setCondition(EmergencyCondition* condition) {
    if (currentCondition != nullptr) {
        delete currentCondition; 
    }
    currentCondition = condition;
}

EmergencyCondition* Emergency::getCondition() const {
    return currentCondition;
}

Iterator* Emergency::createIterator() {
    return nullptr; 
}