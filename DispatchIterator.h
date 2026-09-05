#ifndef DISPATCH_ITERATOR
#define DISPATCH_ITERATOR

#include "Iterator.h"
#include "Capability.h"

class DispatchIterator : Iterator {
    private:
        vector<Capability> requirements;

    public:
        DispatchIterator(ResponseUnit* organisation, Emergency* emergency);
        bool hasNext() override;
        ResponseUnit* next() override;
};

#endif