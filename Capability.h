#ifndef CAPABILITY_H
#define CAPABILITY_H

#include <string>

enum class Capability {
    DRIVING,
    FIRST_AID,
    NAVIGATION,
    RESCUE,
    HAZMAT
};

std::string capabilityToString(Capability capability);

#endif