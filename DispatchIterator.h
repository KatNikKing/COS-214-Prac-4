#ifndef DISPATCH_ITERATOR
#define DISPATCH_ITERATOR

#include "Iterator.h"
#include "ResponseUnit.h"
#include "Emergency.h"
#include "Capability.h"

class DispatchIterator : Iterator {
    private:
        vector<Capability> requirements;
        void collectTeams(ResponseUnit* unit, Emergency* emergency);
        void collectCapabilities(ResponseUnit* unit, Emergency* emergency,
                                std::vector<Capability>& missingCapabilities,
                                int& remaining);
        void collectRemaining(ResponseUnit* unit, Emergency* emergency,
                            int& remaining);

    public:
        DispatchIterator(ResponseUnit* organisation, Emergency* emergency);
        bool hasNext() override;
        ResponseUnit* next() override;
};

#endif