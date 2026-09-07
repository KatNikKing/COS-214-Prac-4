#include "ResponseUnit.h"
#include "ResponseTeam.h"
#include "Responder.h"
#include "RollCallIterator.h"
#include "DispatchIterator.h"

ResponseUnit::ResponseUnit(std::string name) : name(name), state(nullptr) {}

ResponseUnit::~ResponseUnit() {
    delete state;
}

std::string ResponseUnit::getName() const {
    return name;
}

void ResponseUnit::setState(State* state) {
    delete this->state;
    this->state = state;
}

ResponseUnit* ResponseUnit::get(string name) {
    if (this->name == name) return this;

    ResponseTeam* team = dynamic_cast<ResponseTeam*>(this);
    if (team != nullptr) {
        RollCallIterator* rci = team->createRollCallIterator();
        while (rci->hasNext()) {
            ResponseUnit* unit = rci->next();
            if(unit->name == name) return unit;
        }
        delete rci;
    }
    return nullptr; 
}

void ResponseUnit::performDuty() {
    if (state != nullptr) {
        cout << ((dynamic_cast<ResponseTeam*>(this) == nullptr) ? "Responder '" : "Team '") << name << "' ";
        state->performDuty();
    }
}