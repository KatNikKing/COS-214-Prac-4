#include "ResponseUnit.h"

ResponseUnit::ResponseUnit(std::string name) : name(name), state(nullptr) {}

ResponseUnit::~ResponseUnit() {
    delete state;
}

std::string ResponseUnit::getName() const {
    return name;
}

void ResponseUnit::setState(State* state) {
    this->state = state;
}

void ResponseUnit::performDuty() {
    if (state != nullptr) {
        cout << name << " ";
        state->performDuty();
    }
}