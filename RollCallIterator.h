#ifndef ROLL_CALL_ITERATOR
#define ROLL_CALL_ITERATOR

#include "Iterator.h"

class RollCallIterator : public Iterator {
    public:
        RollCallIterator(ResponseUnit* organisation);
        bool hasNext() override;
        ResponseUnit* next() override;
};

#endif