#ifndef TEAM_TYPE
#define TEAM_TYPE

#include <string>

enum class TeamType {
    MEDICAL, 
    RESCUE, 
    TRANSPORT, 
    HAZMAT
};

std::string teamTypeToString(TeamType teamType);

#endif