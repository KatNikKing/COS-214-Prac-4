#ifndef DISPATCH_MANAGER
#define DISPATCH_MANAGER

#include "Emergency.h"
#include "ResponseTeam.h"
#include "Responder.h"

class DispatchManager {
    private:
        ResponseTeam* organisation;
        string location;
        vector<Emergency*> pendingEmergencies;
        static int emergencyCount;
        bool attemptDispatch(Emergency* emergency, vector<ResponseUnit*>& dispatchedUnits);
    public:
        DispatchManager(ResponseTeam* organisation, string location);
        bool receiveEmergency(Emergency* emergency);
        void processPendingEmergencies();
        void runRollCall();
        void printOrganisation();
};

#endif