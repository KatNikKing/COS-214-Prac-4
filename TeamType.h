#ifndef TEAM_TYPE
#define TEAM_TYPE

enum class TeamType {
    MEDICAL, 
    RESCUE, 
    TRANSPORT, 
    HAZMAT
};

std::string teamTypeToString(TeamType teamType) {
    switch (teamType) {
        case TeamType::TRANSPORT: return "Transport";
        case TeamType::MEDICAL: return "Medical";
        case TeamType::HAZMAT: return "Hazmat";
        case TeamType::RESCUE: return "Rescue";
    }

    return "";
}

#endif