#include <iostream>
#include <vector>

#include "DispatchManager.h"
#include "EmergencyIncident.h"
#include "MedicalCondition.h"
#include "HazmatCondition.h"
#include "StructuralCondition.h"

ResponseTeam* buildOrganisation();
vector<Emergency*> buildEmergencies();

int main() {
    ResponseTeam* organisation = buildOrganisation();
    vector<Emergency*> emergencies = buildEmergencies();

    DispatchManager manager(organisation, "Bryedon, Eastern Quartus");

    manager.runRollCall();
    cout << endl;
    manager.printOrganisation();
   
    cout << "\nPROCESSING EMERGENCIES...\n\n";
    for (Emergency* emergency : emergencies) {
        manager.receiveEmergency(emergency);
        cout << "\nORGANISATION AFTER EMERGENCY:\n";
        manager.printOrganisation();
        cout << endl;
    }

    cout << "ORGANISATION ENTERING RECOVERY...\n";
    organisation->setState(new Recovering(10));

    cout << "RETRYING EMERGENCIES...\n";
    for (Emergency* emergency : emergencies) {
        manager.receiveEmergency(emergency);
    }
    
    cout << "\nPROCESSING PENDING EMERGENCIES...\n";
    manager.processPendingEmergencies();

    cout << "\nNULL MANAGER TEST...\n";
    DispatchManager emptyManager(nullptr, "");
    emptyManager.receiveEmergency(emergencies[0]);

    delete organisation;

    for (Emergency* emergency : emergencies) {
        delete emergency;
    }

    return 0;
}

ResponseTeam* buildOrganisation() {
    ResponseTeam* organisation = new ResponseTeam("Emergency Organisation", TeamType::RESCUE);

    //

    // Team A - Medical

    ResponseTeam* teamA = new ResponseTeam("Team A", TeamType::MEDICAL);

    Responder* a1 = new Responder("Alice");
    a1->assignRole(Role::FIRST_AIDER);
    a1->addCapability(Capability::FIRST_AID);

    Responder* a2 = new Responder("Aaron");
    a2->assignRole(Role::FIRST_AIDER);
    a2->addCapability(Capability::FIRST_AID);

    Responder* a3 = new Responder("Amy");
    a3->assignRole(Role::FIRST_AIDER);
    a3->addCapability(Capability::FIRST_AID);

    Responder* a4 = new Responder("Adam");
    a4->assignRole(Role::DRIVER);
    a4->addCapability(Capability::DRIVING);

    Responder* a5 = new Responder("Andrew");
    a5->assignRole(Role::LEADER);
    a5->addCapability(Capability::NAVIGATION);

    teamA->add(a1);
    teamA->add(a2);
    teamA->add(a3);
    teamA->add(a4);
    teamA->add(a5);
    
    // Team B - Rescue

    ResponseTeam* teamB = new ResponseTeam("Team B", TeamType::RESCUE);

    Responder* b1 = new Responder("Ben");
    b1->assignRole(Role::DRIVER);
    b1->addCapability(Capability::DRIVING);

    Responder* b2 = new Responder("Bella");
    b2->assignRole(Role::NAVIGATOR);
    b2->addCapability(Capability::NAVIGATION);

    Responder* b3 = new Responder("Brad");
    b3->assignRole(Role::CARRIER);
    b3->addCapability(Capability::RESCUE);

    Responder* b4 = new Responder("Beth");
    b4->assignRole(Role::LEADER);
    b4->addCapability(Capability::RESCUE);

    Responder* b5 = new Responder("Blake");
    b5->assignRole(Role::FIRST_AIDER);
    b5->addCapability(Capability::FIRST_AID);

    teamB->add(b1);
    teamB->add(b2);
    teamB->add(b3);
    teamB->add(b4);
    teamB->add(b5);

    // Team C - Hazmat

    ResponseTeam* teamC = new ResponseTeam("Team C", TeamType::HAZMAT);

    Responder* c1 = new Responder("Chris");
    c1->assignRole(Role::DRIVER);
    c1->addCapability(Capability::DRIVING);

    Responder* c2 = new Responder("Cara");
    c2->assignRole(Role::NAVIGATOR);
    c2->addCapability(Capability::NAVIGATION);

    Responder* c3 = new Responder("Craig");
    c3->assignRole(Role::CARRIER);
    c3->addCapability(Capability::HAZMAT);

    Responder* c4 = new Responder("Chloe");
    c4->assignRole(Role::LEADER);
    c4->addCapability(Capability::HAZMAT);

    Responder* c5 = new Responder("Caleb");
    c5->assignRole(Role::FIRST_AIDER);
    c5->addCapability(Capability::FIRST_AID);

    teamC->add(c1);
    teamC->add(c2);
    teamC->add(c3);
    teamC->add(c4);
    teamC->add(c5);

    // 

    organisation->add(teamA);
    organisation->add(teamB);
    organisation->add(teamC);

    return organisation;
}

vector<Emergency*> buildEmergencies()
{
    vector<Emergency*> emergencies;

    // Emergency 1
    vector<Capability> medicalCapabilities;
    medicalCapabilities.push_back(Capability::FIRST_AID);
    medicalCapabilities.push_back(Capability::DRIVING);
    medicalCapabilities.push_back(Capability::NAVIGATION);

    Emergency* medicalEmergency =
        new EmergencyIncident("Central Hospital", "Large medical incident", 5, medicalCapabilities);
    emergencies.push_back(medicalEmergency);


    // Emergency 2
    vector<Capability> structuralCapabilities;
    structuralCapabilities.push_back(Capability::RESCUE);
    structuralCapabilities.push_back(Capability::DRIVING);

    Emergency* structuralEmergency =
        new StructuralCondition(
            new EmergencyIncident(
                "Downtown Building",
                "Building collapse",
                3,
                structuralCapabilities));
    emergencies.push_back(structuralEmergency);


    // Emergency 3
    vector<Capability> hazmatCapabilities;
    hazmatCapabilities.push_back(Capability::HAZMAT);
    hazmatCapabilities.push_back(Capability::DRIVING);

    Emergency* hazmatEmergency =
        new HazmatCondition(
            new EmergencyIncident(
                "Industrial Area",
                "Chemical spill",
                3,
                hazmatCapabilities));
    emergencies.push_back(hazmatEmergency);


    // Emergency 4
    vector<Capability> complexCapabilities;
    complexCapabilities.push_back(Capability::RESCUE);
    complexCapabilities.push_back(Capability::FIRST_AID);

    Emergency* complexEmergency =
        new MedicalCondition(
            new StructuralCondition(
                new EmergencyIncident(
                    "Residential Area",
                    "Collapsed structure with injured civilians",
                    4,
                    complexCapabilities)));
    emergencies.push_back(complexEmergency);

    return emergencies;
}
