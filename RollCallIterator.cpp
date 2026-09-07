#include "RollCallIterator.h"
#include "ResponseTeam.h"
#include "Responder.h"

RollCallIterator::RollCallIterator(ResponseUnit* organisation) {
    this->position = 0;
    ResponseTeam* team = dynamic_cast<ResponseTeam*>(organisation);

    if (team != nullptr) {
        for (ResponseUnit* member : team->members) {
            RollCallIterator childIterator(member);

            while (childIterator.hasNext()) {
                toVisit.push_back(childIterator.next());
            }
        }
    }

    else {
        toVisit.push_back(organisation);
    }
}

bool RollCallIterator::hasNext() {
    return position < toVisit.size();
}

ResponseUnit* RollCallIterator::next() {
    if (!hasNext())
        return nullptr;

    return toVisit[position++];
}