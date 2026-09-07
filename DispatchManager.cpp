#include "DispatchManager.h"

int DispatchManager::emergencyCount = 0;
DispatchManager::DispatchManager(ResponseTeam* organisation, string location) 
                : organisation(organisation), location(location) {
                    if (organisation) organisation->setState(new Available(location));
                }

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

    cout << "Required Responders: " << to_string(emergency->getRequiredResponders())
         << ". Responders Dispatched: " << to_string(count) << endl << endl;

    if (emergency->getRequiredResponders() > count)
        cout << "With less responders than required, responding to this emergency will not be easy.\n\n";

    delete iterator;
    return true;
}

TeamType determineTeamType(const vector<Capability>&);
vector<Capability> determineCapabilities(vector<ResponseUnit*>);

bool DispatchManager::receiveEmergency(Emergency* emergency) {
    if (organisation == nullptr) {
        cout << "The organisation is not currently operational.\n";
        return false;
    }

    cout << "==========EMERGENCY==========\n"
         << "New emergency received by organisation '" << organisation->getName() << "'.\n\n"
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

        cout << "\nEmergency resolved...\n";
        for (ResponseUnit* unit : units) {
            unit->setState(new Available(location));
            unit->performDuty();
        }

        TeamType teamType = determineTeamType(determineCapabilities(units));
        string teamName = "Emergency " + to_string(++emergencyCount) + " Team";
        ResponseTeam* newTeam = new ResponseTeam(teamName, teamType);

        cout << "\nRestructuring organisation...\n";
        for (ResponseUnit* unit : units) {
            organisation->remove(unit);
            ResponseTeam* team = dynamic_cast<ResponseTeam*>(unit);
            if (team != nullptr) {
                RollCallIterator* rci = team->createRollCallIterator();
                while(rci->hasNext()) {
                    newTeam->add(team->remove(rci->next()));
                }
                delete unit;
                delete rci;
            }
            else newTeam->add(unit);
        }
        organisation->add(newTeam);
        cout << "New team '" << teamName << "', with " << to_string(newTeam->getHeadCount()) << " members, created.\n";

        cout << "=============================\n";
        return true;
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

    cout << "==========ROLL CALL==========\n";

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
        
    cout << "==========DISPLAYING ORGANISATION==========\n";
    organisation->display(0);
    cout << "=============================\n";
}

vector<Capability> determineCapabilities(vector<ResponseUnit*> units) {
    vector<Capability> capabilities;
    for (auto unit : units) {
        ResponseTeam* team = dynamic_cast<ResponseTeam*>(unit);
        if (team != nullptr) {
            int headCount = team->getHeadCount();
            switch(team->getTeamType()) {
                case TeamType::HAZMAT:
                    for (int i = 0; i < headCount; i++)
                        capabilities.push_back(Capability::HAZMAT);
                    break;
                case TeamType::MEDICAL:
                    for (int i = 0; i < headCount; i++)
                        capabilities.push_back(Capability::FIRST_AID);
                    break; 
                case TeamType::RESCUE:
                    for (int i = 0; i < headCount; i++)
                        capabilities.push_back(Capability::RESCUE);
                    break;
                case TeamType::TRANSPORT:
                    for (int i = 0; i < headCount; i++)
                        capabilities.push_back(Capability::DRIVING);
                    break;             
            }
        }
        else {
            Responder* responder = dynamic_cast<Responder*>(unit);
            for (auto capability: responder->getCapabilities()) 
                capabilities.push_back(capability);
        }
    }
    return capabilities;
}

#include <map>

TeamType determineTeamType(const std::vector<Capability>& capabilities) {
    std::map<Capability, int> counts;

    for (Capability capability : capabilities) counts[capability]++;

    Capability mostProminent = capabilities[0];
    for (const auto& entry : counts) {
        if (entry.second > counts[mostProminent])
            mostProminent = entry.first;
    }

    switch (mostProminent) {
        case Capability::FIRST_AID:
            return TeamType::MEDICAL;

        case Capability::RESCUE:
            return TeamType::RESCUE;

        case Capability::DRIVING:
        case Capability::NAVIGATION:
            return TeamType::TRANSPORT;

        case Capability::HAZMAT:
            return TeamType::HAZMAT;
    }

    return TeamType::RESCUE;
}