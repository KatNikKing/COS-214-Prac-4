#ifndef RESPONSE_TEAM
#define RESPINSE_TEAM

#include "ResponseUnit.h"
#include "DispatchIterator.h"
#include "RollCallIterator.h"
#include "TeamType.h"
#include "Capability.h"

#include <vector>

using namespace std;

class ResponseTeam : public ResponseUnit {
    private:
        vector<ResponseUnit*> members;
        TeamType teamType;

    public:
        ResponseTeam(string name, TeamType teamType);
        ~ResponseTeam();
        void setState(State* state) override;
        void setTeamType(TeamType teamtype);
        TeamType getTeamType();
        int getHeadCount();
        bool isAvailable() override;
        int countCapability(Capability capability);
        bool hasCapability(Capability capability, int requiredResponders) override;
        void add(ResponseUnit* unit) override;
        void remove(string name) override;
        ResponseUnit* get(string name) override;
        string toString() override;
        DispatchIterator* createDispatchIterator(Emergency* emergency);
        RollCallIterator* createRollCallIterator();
};

#endif