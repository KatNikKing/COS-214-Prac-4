#include "ResponseTeam.h"
#include "Responder.h"
#include "Emergency.h"

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
        member->setState(state->clone());
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
    if (dynamic_cast<Available*>(state) == nullptr) setState(new Available("Unknown Location"));
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
        case Capability::NAVIGATION:
            if (teamType == TeamType::TRANSPORT && headCount >= requiredResponders) return true;
            break;
    }
    return countCapability(capability) >= requiredResponders;
}

bool ResponseTeam::canSatisfy(Emergency* emergency) {
    if (!isAvailable())
        return false;

    if (getHeadCount() < emergency->getRequiredResponders())
        return false;

    for (Capability capability : emergency->getRequiredCapabilities()) {
        if (!hasCapability(capability))
            return false;
    }

    return true;
}

void ResponseTeam::add(ResponseUnit* unit) {
    if (unit != nullptr) {
        members.push_back(unit);
    }
}

ResponseUnit* ResponseTeam::remove(ResponseUnit* unit) {
    for (auto it = members.begin(); it != members.end(); ++it) {
        if (*it == unit) {
            ResponseUnit* pop = *it;
            members.erase(it);
            return pop;
        }

        ResponseTeam* team = dynamic_cast<ResponseTeam*>(*it);
        if (team != nullptr) {
            team->remove(unit);
        }
    }
    return nullptr;
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

void ResponseTeam::display(int level) {
    string tabs = string(level, '\t');
    cout << tabs << toString() << endl;
    for (ResponseUnit* member : members) {
        member->display(level + 1);
    }
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