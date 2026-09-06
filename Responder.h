#ifndef RESPONDER_H
#define RESPONDER_H

#include "ResponseUnit.h"
#include "Role.h"
#include "Capability.h"

#include <vector>

using namespace std;

class Responder : public ResponseUnit {
    private:
        Role role;
        vector<Capability> capabilities;

    public:
        Responder(string name);
        void assignRole(Role role);
        void addCapability(Capability capability);
        bool isAvailable() override;
        bool hasCapability(Capability capability, int requiredResponders) override;
        ResponseUnit* get(string name) override;
        string toString() override;
};

#endif