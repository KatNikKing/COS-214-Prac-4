#include "Responder.h"
#include "Emergency.h"

Responder::Responder(string name) : ResponseUnit(name) {}

void Responder::assignRole(Role role) {
    this->role = role;
}

void Responder::addCapability(Capability capability) {
    capabilities.push_back(capability);
}

bool Responder::isAvailable() {
    if (dynamic_cast<Available*>(state) == nullptr) 
        return false;
    return true;
}

bool Responder::hasCapability(Capability capability, int requiredResponders) {
    if (requiredResponders > 1) return false;
    for (Capability c : capabilities) {
        if (c == capability)
            return true;
    }
    return false;
}

bool Responder::canSatisfy(Emergency* emergency) {
    if (!isAvailable())
        return false;
    
    for (Capability capability : emergency->getRequiredCapabilities()) {
        if (!hasCapability(capability, 1))
            return false;
    }

    return true;
}

void Responder::display(int level) {
    string tabs = string(level, '\t');
    cout << tabs << toString() << endl;
}

string Responder::toString() {
    return "Responder Name: " + name + ", Team Role: " + roleToString(role);
}