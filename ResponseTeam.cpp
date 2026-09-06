#include "ResponseTeam.h"
#include "Responder.h"

ResponseTeam::ResponseTeam(string name, TeamType teamType) : ResponseUnit(name), teamType(teamType) {}

ResponseTeam::~ResponseTeam() {
    for (ResponseUnit* member : members) {
        delete member;
    }
}

void ResponseTeam::setState(State* state) {
    if (state == nullptr) return;

    delete this->state;
    this->state = state;
    for (ResponseUnit* member : members) {
        member->setState(state);
    }
}

void ResponseTeam::setTeamType(TeamType teamtype) {
    this->teamType = teamtype;
}

TeamType ResponseTeam::getTeamType() {
    return teamType;
}

int ResponseTeam::getHeadCount() {
    int count = 0;
    for (ResponseUnit* member : members) {
        ResponseTeam* responseTeam = dynamic_cast<ResponseTeam*>(member);
        if (responseTeam == nullptr) count++;
        else count += responseTeam->getHeadCount();
    }
    return count;
}

bool ResponseTeam::isAvailable() {
    for (ResponseUnit* member : members) {
        if (!member->isAvailable()) return false;
    }
    if (dynamic_cast<Available*>(state) == nullptr) setState(new Available("unknown location"));
    return true;
}

int ResponseTeam::countCapability(Capability capability) {
    int count = 0;
    for (ResponseUnit* member : members) {
        ResponseTeam* responseTeam = dynamic_cast<ResponseTeam*>(member);
        if (responseTeam == nullptr) {
            if (member->hasCapability(capability))
                count++;
        }
        else {
            count += responseTeam->countCapability(capability);
        }
    }
    return count;
}

bool ResponseTeam::hasCapability(Capability capability, int requiredResponders) {
    int headCount = getHeadCount();
    switch (capability) {
        case Capability::DRIVING:
            if (teamType == TeamType::TRANSPORT && headCount >= requiredResponders) return true;
            break;
        case Capability::FIRST_AID:
            if (teamType == TeamType::MEDICAL && headCount >= requiredResponders) return true;
            break;
        case Capability::HAZMAT:
            if (teamType == TeamType::HAZMAT && headCount >= requiredResponders) return true;
            break;
        case Capability::RESCUE:
            if (teamType == TeamType::RESCUE && headCount >= requiredResponders) return true;
            break;
    }
    return countCapability(capability) >= requiredResponders;
}

void ResponseTeam::add(ResponseUnit* unit) {
    if (unit != nullptr) {
        members.push_back(unit);
    }
}

void ResponseTeam::remove(string name) {
    for (auto it = members.begin(); it != members.end(); ++it) {
        if ((*it)->getName() == name) {
            delete *it;
            members.erase(it);
            return;
        }

        ResponseTeam* team = dynamic_cast<ResponseTeam*>(*it);
        if (team != nullptr) {
            team->remove(name);
        }
    }
}

ResponseUnit* ResponseTeam::get(string name) {
    if (this->name == name) return this;
    for (ResponseUnit* member : members) {
        ResponseUnit* unit = member->get(name);
        if (unit != nullptr) return unit;
    }
    return nullptr;
}

std::string teamTypeToString(TeamType teamType) {
    switch (teamType) {
        case TeamType::TRANSPORT: return "Transport";
        case TeamType::MEDICAL: return "Medical";
        case TeamType::HAZMAT: return "Hazmat";
        case TeamType::RESCUE: return "Rescue";
    }

    return "";
}


string ResponseTeam::toString() {
    return "Team Name: " + name + ", Team Type: " + teamTypeToString(teamType);
}

DispatchIterator* ResponseTeam::createDispatchIterator(Emergency* emergency) {
    return new DispatchIterator(this, emergency);
}

RollCallIterator* ResponseTeam::createRollCallIterator() {
    return new RollCallIterator(this);
}