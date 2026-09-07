#include "Responder.h"
#include "Emergency.h"
#include "DispatchIterator.h"
#include "RollCallIterator.h"

Responder::Responder(string name) : ResponseUnit(name) {}

void Responder::assignRole(Role role) {
    this->role = role;
}

void Responder::addCapability(Capability capability) {
    capabilities.push_back(capability);
}

vector<Capability> Responder::getCapabilities() {
    return capabilities;
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
    string responder = "Responder Name: " + name + ", Team Role: " + roleToString(role) + ", Capabilities: ";
    for (Capability capability : capabilities) {
        responder += capabilityToString(capability) +  " ";
    }
    if (!responder.empty() && responder.back() == ' ') responder.pop_back();
    return responder;
}

DispatchIterator* Responder::createDispatchIterator(Emergency* emergency) {
    return new DispatchIterator(this, emergency);
}

RollCallIterator* Responder::createRollCallIterator() {
    return new RollCallIterator(this);
}