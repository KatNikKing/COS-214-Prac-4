#include "DispatchIterator.h"
#include "ResponseTeam.h"
#include "Responder.h"

DispatchIterator::DispatchIterator(ResponseUnit* organisation, Emergency* emergency) {
    int required = emergency->getRequiredResponders();
    collectTeams(organisation, emergency);
    if (!toVisit.empty())
        return;

    int remaining = required;
    vector<Capability> missingCapabilities = emergency->getRequiredCapabilities();
    collectCapabilities(organisation, emergency, missingCapabilities, remaining);

    if (remaining > 0)
        collectRemaining(organisation, emergency, remaining);
}

void DispatchIterator::collectTeams(ResponseUnit* unit, Emergency* emergency) {
    ResponseTeam* team = dynamic_cast<ResponseTeam*>(unit);
    if (team == nullptr)
        return;

    if (team->getHeadCount() == emergency->getRequiredResponders() && team->canSatisfy(emergency)) {
        toVisit.push_back(team);
        return;
    }

    for (ResponseUnit* member : team->members) {
        if (!toVisit.empty())
            return;
        collectTeams(member, emergency);
    }
}

void DispatchIterator::collectCapabilities(
    ResponseUnit* unit,
    Emergency* emergency,
    vector<Capability>& missingCapabilities,
    int& remaining)
{
    if (remaining <= 0 || missingCapabilities.empty())
        return;

    ResponseTeam* team = dynamic_cast<ResponseTeam*>(unit);

    if (team != nullptr) {
        for (ResponseUnit* member : team->members) {
            collectCapabilities(member, emergency, missingCapabilities, remaining);
            if (remaining <= 0 || missingCapabilities.empty())
                return;
        }
        return;
    }

    Responder* responder = dynamic_cast<Responder*>(unit);
    if (responder == nullptr || !responder->isAvailable())
        return;

    for (std::size_t i = 0; i < missingCapabilities.size(); ++i) {
        if (responder->hasCapability(missingCapabilities[i])) {
            toVisit.push_back(responder);
            --remaining;
            missingCapabilities.erase(missingCapabilities.begin() + i);
            return;
        }
    }
}

void DispatchIterator::collectRemaining(ResponseUnit* unit, Emergency* emergency, int& remaining) {
    if (remaining <= 0) return;

    ResponseTeam* team = dynamic_cast<ResponseTeam*>(unit);
    if (team != nullptr) {
        for (ResponseUnit* member : team->members) {
            collectRemaining(member, emergency, remaining);
            if (remaining <= 0) return;
        }
        return;
    }

    if (!unit->isAvailable())
        return;

    for (ResponseUnit* selected : toVisit) {
        if (selected == unit) return;
    }

    Responder* responder = dynamic_cast<Responder*>(unit);
    if (responder != nullptr) {
        toVisit.push_back(responder);
        --remaining;
    }
}

bool DispatchIterator::hasNext() {
    return position < toVisit.size();
}

ResponseUnit* DispatchIterator::next() {
    if (!hasNext())
        return nullptr;

    return toVisit[position++];
}