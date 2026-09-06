#include "Responder.h"

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

ResponseUnit* Responder::get(string name) {
    if (this->name == name) return this;
    return nullptr;
}

std::string roleToString(Role role) {
    switch (role) {
        case Role::DRIVER: return "Driver";
        case Role::CARRIER: return "Carrier";
        case Role::FIRST_AIDER: return "First-aider";
        case Role::LEADER: return "Leader";
        case Role::NAVIGATOR: return "Navigator";
        case Role::RESPONDER: return "Responder";
    }

    return "";
}


string Responder::toString() {
    return "Responder Name: " + name + ", Team Role: " + roleToString(role);
}