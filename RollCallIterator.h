#ifndef ROLL_CALL_ITERATOR
#define ROLL_CALL_ITERATOR

#include "Iterator.h"
#include "ResponseUnit.h"

class RollCallIterator : public Iterator {
    public:
        RollCallIterator(ResponseUnit* organisation);
        bool hasNext() override;
        ResponseUnit* next() override;
};

#endif