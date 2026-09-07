#include "Capability.h"

std::string capabilityToString(Capability capability) {
    switch (capability) {
        case Capability::DRIVING: return "Driving";
        case Capability::FIRST_AID: return "First-Aid";
        case Capability::HAZMAT: return "Hazmat";
        case Capability::NAVIGATION: return "Navigation";
        case Capability::RESCUE: return "Rescue";
    }

    return "";
}