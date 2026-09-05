#ifndef ITERATOR
#define ITERATOR

#include <vector>

using namespace std;

class Iterator {
    protected:
        vector<ResponseUnit*> toVisit;
        int position;

    public:
        virtual ~Iterator() = default;
        virtual bool hasNext() = 0;
        virtual ResponseUnit* next() = 0;
};

#endif