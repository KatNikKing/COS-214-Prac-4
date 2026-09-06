#include "DispatchManager.h"

DispatchManager::DispatchManager(ResponseTeam* organisation, string location) 
                : organisation(organisation), location(location) {}

bool DispatchManager::attemptDispatch(Emergency* emergency, vector<ResponseUnit*>& dispatchedUnits) {
    if (organisation == nullptr) return false;

    DispatchIterator* iterator = organisation->createDispatchIterator(emergency);
    if (!iterator->hasNext()) {
        delete iterator;
        return false;
    }

    cout << "Dispatching emergency responders...\n";

    int count = 0;
    while (iterator->hasNext()) {
        ResponseUnit* unit = iterator->next();
        unit->setState(new Dispatched(emergency->getLocation()));
        unit->performDuty();
        dispatchedUnits.push_back(unit);

        ResponseTeam* team = dynamic_cast<ResponseTeam*>(unit);
        if (team != nullptr) count += team->getHeadCount();
        else count++;
    }

    cout << "\nRequired Responders: " << to_string(emergency->getRequiredResponders())
         << ". Responders Dispatched: " << to_string(count) << endl << endl;

    delete iterator;
    return true;
}

bool DispatchManager::receiveEmergency(Emergency* emergency) {
    if (organisation == nullptr) {
        cout << "The organisation is not currently operational.\n";
        return false;
    }
    cout << "==========EMERGENCY==========\n"
         << "New emergency received by organisation " << organisation->getName() << ".\n"
         << "Location of emergency: " << emergency->getLocation() << endl
         << "Description: " << emergency->getDescription() << endl
         << "Capabilities required: ";

    for (Capability capability : emergency->getRequiredCapabilities()) {
        cout << capabilityToString(capability) << " ";
    }
    cout << endl << endl;

    vector<ResponseUnit*> units;
    if (attemptDispatch(emergency, units)) {
        cout << "Responding to emergency...\n";
        for (ResponseUnit* unit : units) {
            unit->setState(new Operating("Follow assigned instructions."));
            unit->performDuty();
        }

        cout << "\nRecovering from duty...\n";
        for (ResponseUnit* unit : units) {
            unit->setState(new Recovering(10));
            unit->performDuty();
        }

        cout << "Emergency resolved...\n";
        for (ResponseUnit* unit : units) {
            unit->setState(new Available(location));
            unit->performDuty();
        }
        cout << "=============================\n";
    }

    else {
        cout << "Emergency unresolved. Adding to pending emergencies...\n";
        bool exists = false;
        for (Emergency* e : pendingEmergencies) {
            if (e == emergency) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            pendingEmergencies.push_back(emergency);
        }
        cout << "=============================\n";
        return false;
    }
}

void DispatchManager::processPendingEmergencies() {
    for (std::size_t i = 0; i < pendingEmergencies.size(); ) {
        if (receiveEmergency(pendingEmergencies[i])) 
            pendingEmergencies.erase(pendingEmergencies.begin() + i);
        else ++i;
    }
}

void DispatchManager::runRollCall() {
    if (organisation == nullptr) 
        cout << "The organisation is not currently operational.\n";

    cout << "==========Roll Call==========\n";

    RollCallIterator* rci = organisation->createRollCallIterator();
    while (rci->hasNext()) {
        cout << rci->next()->toString() << endl;
    }

    cout << "=============================\n";
    delete rci;
}

void DispatchManager::printOrganisation() {
    if (organisation == nullptr) 
        cout << "The organisation is not currently operational.\n";
        
    cout << "==========" << organisation->getName() << "==========\n";
    organisation->display(0);
    cout << "=============================\n";
}