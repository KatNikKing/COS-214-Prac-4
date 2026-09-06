#include "ResponseUnit.h"

ResponseUnit::ResponseUnit(const std::string& name) : unitName(name) {}

ResponseUnit::~ResponseUnit() {}

void ResponseUnit::addUnit(ResponseUnit* unit) {
    throw std::logic_error("can't add to leaf unit.");
}

void ResponseUnit::removeUnit(ResponseUnit* unit) {
    throw std::logic_error("can't remove from leaf unit.");
}

std::string ResponseUnit::getName() const {
    return unitName;
}