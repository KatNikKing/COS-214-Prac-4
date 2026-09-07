#ifndef ITERATOR
#define ITERATOR

#include "ResponseUnit.h"

class Iterator {
    protected:
        vector<ResponseUnit*> toVisit;
        size_t position;

    public:
        virtual ~Iterator() = default;
        virtual bool hasNext() = 0;
        virtual ResponseUnit* next() = 0;
};

#endif