#ifndef RESPONDER_H
#define RESPONDER_H

#include "ResponseUnit.h"
#include "Role.h"

class DispatchIterator;
class RollCallIterator;

class Responder : public ResponseUnit {
    private:
        Role role;
        vector<Capability> capabilities;

    public:
        Responder(string name);
        void assignRole(Role role);
        void addCapability(Capability capability);
        vector<Capability> getCapabilities();
        bool isAvailable() override;
        bool hasCapability(Capability capability, int requiredResponders = 1) override;
        bool canSatisfy(Emergency* emergency) override;
        void display(int level) override;
        string toString() override;
        DispatchIterator* createDispatchIterator(Emergency* emergency);
        RollCallIterator* createRollCallIterator();
};

#endif